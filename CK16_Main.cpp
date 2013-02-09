
#include "WPILib.h"
#include "CANJaguar.h"
#include "Joystick.h"
#include "CAN_PID_Controller.h"
#include "Gyro.h"
#include "RobotTurnPIDOutput.h"
#include "PIDController.h"
#include "RobotConfiguration.h"
#include "TeleopHelper.h"
#include "SmartDashboard/SmartDashboard.h"
#include <string>
#include <math.h>
#include "CSVReader.h"

class CK16_Main : public IterativeRobot
{
    // Declare CSV readers
    CSVReader *PWM_CSV, *AnalogInputs_CSV, *DigitalIO_CSV, *CAN_IDS_CSV;
    
	// SmartDashboard Keys
	std::string FOUND_KEY, AZIMUTH_KEY, RANGE_KEY, SHOOTER_ANGLE_KEY;
	
	// Declare variable for the robot drive system
	RobotDrive *m_robotDrive;		// robot will use PWM 1-4 for drive motors	
    
	// Robot will use CAN bus for motor control
	CANJaguar *Front_R, *Front_L, *Rear_R, *Rear_L;
	CANJaguar *ShooterFeed,/* watman strikes again*/ *ShooterFire;
    CANJaguar *Roller;

	
	// Digital Input pin for the pressure switch
	DigitalInput *Pressure_SW;
	
	// Building the Trojan horse.
    Relay *Compressor;
    
    // Pulling out Excalibers (2x)
    Solenoid *Disc_Load_In, *Disc_Load_Out, *Shooter_Tilt_In, *Shooter_Tilt_Out, *Disc_Fire;
	
	// Declare left and right encoder drive PIDControllers
	CAN_PID_Controller *Left_Drive_PID, *Right_Drive_PID;
	
	
	// Declare Gyro that will be used to determine left and right robot rotation
	Gyro *Yaw_Gyro;
	
	// Declare RobotTurnPIDOutput that will control the robot turning aspect of the goal alignment
	RobotTurnPIDOutput *Robot_Turn;
	
	// Declare PID Controller that will handle aligning the robot with the goal
	PIDController *Goal_Align_PID;
	
	// State boolean that represents if robot is driving with joystick input or using auto align
	bool autoPilot;
	
	// Declare a variable to use to access the driver station object
	DriverStation *m_ds;						// driver station object
	DriverStationLCD *m_ds_lcd;
	UINT32 /* wat */ m_priorPacketNumber;					// keep track of the most recent packet number from the DS
	UINT8 m_dsPacketsReceivedInCurrentSecond;	// keep track of the ds packets received in the current second
	
	// Declare variables for the two joysticks being used on port 1
	Joystick *operatorGamepad;			// joystick 1 (arcade stick or right tank stick)
	

	// Local variables to count the number of periodic loops performed
	UINT32 m_autoPeriodicLoops;
	UINT32 m_disabledPeriodicLoops;
	UINT32 m_telePeriodicLoops;
    
		
public:
/**
 * Constructor for this "CK16_Main" Class.
 * 
 * The constructor creates all of the objects used for the different inputs and outputs of
 * the robot.  Essentially, the constructor defines the input/output mapping for the robot,
 * providing named objects for each of the robot interfaces. 
 */
	CK16_Main(void)	{
		printf("CK16_Main Constructor Started\n");
        
        // Configuration files
		printf("Loading the configuration files.\n");
		AnalogInputs_CSV = new CSVReader("AnalogInputs.csv");
		CAN_IDS_CSV = new CSVReader("CAN_IDs.csv");
		DigitalIO_CSV = new CSVReader("DigitalIO.csv");
		PWM_CSV = new CSVReader("PWM.csv");           
		
		// Initialize SmartDashboard Keys
		FOUND_KEY = "found";
		AZIMUTH_KEY = "azimuth";
		RANGE_KEY = "range";
		SHOOTER_ANGLE_KEY = "shooter angle";
		
		// Initialize the CAN Jaguars
		Front_R = new CANJaguar((int)CAN_IDS_CSV->GetValue("FR_CAN_ID"));
		Front_L = new CANJaguar((int)CAN_IDS_CSV->GetValue("FL_CAN_ID"));
		Rear_R = new CANJaguar((int)CAN_IDS_CSV->GetValue("RR_CAN_ID"));
		Rear_L = new CANJaguar((int)CAN_IDS_CSV->GetValue("RL_CAN_ID"));
        Roller = new CANJaguar((int)CAN_IDS_CSV->GetValue("ROLLER_MOTOR_CAN_ID"));
		ShooterFeed = new CANJaguar((int)CAN_IDS_CSV->GetValue("FEED_CAN_ID"));
		ShooterFire = new CANJaguar((int)CAN_IDS_CSV->GetValue("FIRE_CAN_ID"));
		printf("TEAM 79 FOR THE WIN!\n");
		
		// Initialize Robot Drive System Using Jaguars
		m_robotDrive = new RobotDrive(Front_L, Rear_L, Front_R, Rear_R);
		
		// Initialize Gyro
//		Yaw_Gyro = new Gyro((int)AnalogInputs_CSV->GetValue("YAW_GYRO_ID"));

		m_ds = DriverStation::GetInstance();
		m_ds_lcd = DriverStationLCD::GetInstance();
		
		m_ds_lcd->PrintfLine(DriverStationLCD::kUser_Line1,"Gyro Done Initializing\n");
		m_ds_lcd->UpdateLCD();
		
		// Initialize the RobotTurnPIDOutput
		Robot_Turn = new RobotTurnPIDOutput(m_robotDrive);
		
		// Initialize Goal Alignment PID Controller
//		Goal_Align_PID = new PIDController(1.0, 1.0, 1.0, Yaw_Gyro, Robot_Turn);
		
		// Acquire the Driver Station object
		m_priorPacketNumber = 0;
		m_dsPacketsReceivedInCurrentSecond = 0;

		// Define joysticks being used at USB port #1 on the Drivers Station
		operatorGamepad = new Joystick(1);

		// Initialize counters to record the number of loops completed in autonomous and teleop modes
		m_autoPeriodicLoops = 0;
		m_disabledPeriodicLoops = 0;
		m_telePeriodicLoops = 0;
        
		// Initialize pressure switch input channel
		Pressure_SW = new DigitalInput((int)DigitalIO_CSV->GetValue("PRESSURE_SWITCH_ID"));
		
        // Filling the Trojan horse with people, then shipping it off to Troy.
        Compressor = new Relay(RobotConfiguration::COMPRESSOR_RELAY_CHANNEL);
        
        // Sharpening Excalibur on the ye old grindstone in the centre of town.
        Disc_Load_In = new Solenoid((int)DigitalIO_CSV->GetValue("DISC_LOAD_IN_ID"));
        Disc_Load_Out = new Solenoid((int)DigitalIO_CSV->GetValue("DISC_LOAD_OUT_ID"));
        Disc_Fire = new Solenoid((int)DigitalIO_CSV->GetValue("DISC_FIRE_ID"));
        Shooter_Tilt_In = new Solenoid((int)DigitalIO_CSV->GetValue("SHOOTER_TILT_IN_ID"));
        Shooter_Tilt_Out = new Solenoid((int)DigitalIO_CSV->GetValue("SHOOTER_TILT_OUT_ID"));
        

		printf("CK16_Main Constructor Completed\n");
	}
	
	
	/********************************** Init Routines *************************************/

	void RobotInit(void) {
		// Actions which would be performed once (and only once) upon initialization of the
		// robot would be put here.
		
		// Initialize settings for RobotTurn
//		Goal_Align_PID->SetOutputRange(-0.2, 0.2);
//		Goal_Align_PID->SetTolerance(0.05);
        
        // Set each drive motor to have an encoder to be its friend
        Front_R->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
        Front_L->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
        
        // Set encoders
        Front_R->ConfigEncoderCodesPerRev(TICS_PER_REV); 
        Front_L->ConfigEncoderCodesPerRev(TICS_PER_REV);
        
        // Excalibur is sheathed
        Disc_Load_In->Set(false);
        Disc_Load_Out->Set(true);
        Disc_Fire->Set(false);
        Shooter_Tilt_In->Set(false);
        Shooter_Tilt_Out->Set(true);
        
        		
		printf("RobotInit() completed.\n");
	}
	
	void DisabledInit(void) {
		m_disabledPeriodicLoops = 0;			// Reset the loop counter for disabled mode
		
		// Reset and Disable Goal Alignment PID Controller
//		Goal_Align_PID->Reset(); // The Disable method will not reset Integral term nor the error
		autoPilot = false;
		
		// Move the cursor down a few, since we'll move it back up in periodic.
		printf("\x1b[2B");
	}

	void AutonomousInit(void) {
		m_autoPeriodicLoops = 0;				// Reset the loop counter for autonomous mode
		
		// Enable Goal Align PID
//		Goal_Align_PID->Enable();
//		Goal_Align_PID->SetSetpoint(0.0);
		printf("Auton Init Completed\n");
	}

	void TeleopInit(void) {
		m_telePeriodicLoops = 0;				// Reset the loop counter for teleop mode
		m_dsPacketsReceivedInCurrentSecond = 0;	// Reset the number of dsPackets in current second
		
		// Enable Goal Align PID
//		Goal_Align_PID->Enable();
//		Goal_Align_PID->SetSetpoint(0.0);
		printf("Teleop Init Completed\n");
	}

	/********************************** Periodic Routines *************************************/
	
	void DisabledPeriodic(void)  {
		static INT32 printSec = (INT32)GetClock() + 1;
		static const INT32 startSec = (INT32)GetClock();

		// increment the number of disabled periodic loops completed
		m_disabledPeriodicLoops++;
		
		// while disabled, printout the duration of current disabled mode in seconds
		if (GetClock() > printSec) {
			// Move the cursor back to the previous line and clear it.
			printf("\x1b[1A\x1b[2K");
			printf("Disabled seconds: %d\r\n", printSec - startSec);			
			printSec++;
		}
	}

	void AutonomousPeriodic(void) {
		m_autoPeriodicLoops++;
		printf("Auton Loops:%d\n", m_autoPeriodicLoops);

		switch(m_autoPeriodicLoops)
		{
		case 1:
			// Drive 2 feet
			double encoderCounts;
			encoderCounts = (2 * 12.0) * TICS_PER_REV / WHEEL_CIRCUMFERENCE;
			break;
		default:
			break;
		}
	}
	
	void TeleopPeriodic(void) {
		// increment the number of teleop periodic loops completed
		m_telePeriodicLoops++;
		GetWatchdog().Feed();
        
        // Trojan horse has entered Troy
        Compressor->Set((!Pressure_SW->Get() ? Relay::kForward : Relay::kOff));

		// Reset Gyro
//        Yaw_Gyro->Reset();
        
//		if(autoPilot == true)
//		{
//			// Auto Align Disable Button
//			if(operatorGamepad->GetButton(Joystick::kTopButton) == 2)
//			{
//				Goal_Align_PID->Disable(); // Stop outputs
//				Goal_Align_PID->Enable(); // Start PIDContoller up again
//				Goal_Align_PID->SetSetpoint(0.0);
//				autoPilot = false;
//			}
//		}
//		else
//		{
			// Map joystick position to speed value through a special equation
			double leftOutput, rightOutput;
			leftOutput = -TeleopHelper::mapJoystickToSpeedOutput(operatorGamepad->GetRawAxis(2));
			rightOutput = -TeleopHelper::mapJoystickToSpeedOutput(operatorGamepad->GetRawAxis(5));
			
			// Joystick Driving
			m_robotDrive->SetLeftRightMotorOutputs(leftOutput, rightOutput);
			
//			printf("Left Encoder Distance: %f\nRight Encoder Distance: %f\n", Front_L->GetPosition()*INCHES_PER_TIC, Front_R->GetPosition()*INCHES_PER_TIC);
			
//			m_ds_lcd->PrintfLine(DriverStationLCD::kUser_Line2, "Gyro: %f", Yaw_Gyro->GetAngle());			
			m_ds_lcd->UpdateLCD();
			if(operatorGamepad->GetRawButton(2))
			{
				ShooterFeed->Set(-0.75);
				ShooterFire->Set(-0.75);
			}
			else
			{
				ShooterFeed->Set(0.0);
				ShooterFire->Set(0.0);
			}
        
            // Roller
            if(operatorGamepad->GetRawButton(8)){
                Roller->Set(0.8);
            }
            else{
                Roller->Set(0.0);
            }
			
            // Excalibur was actually a horse and now its running away into the wild blue yonder.
            Disc_Load_In->Set(operatorGamepad->GetRawButton(3));
            Disc_Load_Out->Set(!operatorGamepad->GetRawButton(3));
        
            // Exaclibur's brother is a little sluggish, but has also escaped. This one was a goat.
            Disc_Fire->Set(operatorGamepad->GetRawButton(4));
            
            // Excalibur has a cousin
            Shooter_Tilt_In->Set(operatorGamepad->GetRawButton(1));
            Shooter_Tilt_Out->Set(!operatorGamepad->GetRawButton(1));
            
            
			// Auto Align Button
//			if(operatorGamepad->GetRawButton(1))
//			{
//				// Turn Auto Align on if we see a goal and we know the azimuth
//				if(SmartDashboard::GetBoolean(FOUND_KEY) == true)
//				{
//					Goal_Align_PID->SetSetpoint(SmartDashboard::GetNumber(AZIMUTH_KEY));
//					autoPilot = true;
//				}
//			}
//		}
		
	} 
	
	//TeleopPeriodic(void)
			
};
