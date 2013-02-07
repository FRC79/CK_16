#include "WPILib.h"
#include "CANJaguar.h"
#include "Joystick.h"
#include "CAN_PID_Controller.h"
#include "Gyro.h"
#include "RobotTurnPIDOutput.h"
#include "PIDController.h"
#include "RobotConfiguration.h"
#include "SmartDashboard/SmartDashboard.h"
#include <string>
#include <math.h>
#include "CSVReader.h"

class CK16_Main : public IterativeRobot
{
    // Declare CSV readers
    CSVReader *PWM_CSV, *AnalogInputs_CSV, *DigitalIO_CSV, *CAN_IDS_CSV;
    
	// SmartDashboard Keys
	std::string FOUND_KEY, AZIMUTH_KEY, RANGE_KEY, EXP_KEY;
	
	// Declare variable for the robot drive system
	RobotDrive *m_robotDrive;		// robot will use PWM 1-4 for drive motors	
    
	// Robot will use CAN bus for motor control
	CANJaguar *Front_R, *Front_L, *Rear_R, *Rear_L;
	CANJaguar *ShooterFeed,/* watman strikes again*/ *ShooterFire;
	
	// Digital Input pin for the pressure switch
	DigitalInput *Pressure_SW;
	
	// Building the Trojan horse.
    Relay *Compressor;
    
    // Pulling out Excalibers (2x)
    Solenoid *Disc_Load_In, *Disc_Load_Out, *Disc_Fire_In, *Disc_Fire_Out;
	
	// Declare left and right encoder drive PIDControllers
	CAN_PID_Controller *Left_Drive_PID, *Right_Drive_PID;
	
	
	// Declare Gyro that will be used to determine left and right robot rotation
	Gyro *Yaw_Gyro;
	
	// Declare RobotTurnPIDOutput that will control the robot turning aspect of the goal alignment
//	RobotTurnPIDOutput *Robot_Turn;
	
	// Declare PID Controller that will handle aligning the robot with the goal
//	PIDController *Goal_Align_PID;
	
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
		EXP_KEY = "exp";
		
		// Initialize the CAN Jaguars
		Front_R = new CANJaguar((int)CAN_IDS_CSV->GetValue("FR_CAN_ID"));
		Front_L = new CANJaguar((int)CAN_IDS_CSV->GetValue("FL_CAN_ID"));
		Rear_R = new CANJaguar((int)CAN_IDS_CSV->GetValue("RR_CAN_ID"));
		Rear_L = new CANJaguar((int)CAN_IDS_CSV->GetValue("RL_CAN_ID"));
		ShooterFeed = new CANJaguar((int)CAN_IDS_CSV->GetValue("FEED_CAN_ID"));
		ShooterFire = new CANJaguar((int)CAN_IDS_CSV->GetValue("FIRE_CAN_ID"));
		printf("TEAM 79 FOR THE WIN!\n");
		
		// Initialize Robot Drive System Using Jaguars
		m_robotDrive = new RobotDrive(Front_L, Rear_L, Front_R, Rear_R);

		// Initialize left and right encoder drive PIDControllers
		Left_Drive_PID = new CAN_PID_Controller(1.0, 1.0, 1.0, Front_L, Front_L, Rear_L, false, 0.05 ); // Input: Jag Encoder, Output: Jags
		Right_Drive_PID = new CAN_PID_Controller(1.0, 1.0, 1.0, Front_R, Front_R, Rear_R, false, 0.05);
		
		// Initialize Gyro
//		Yaw_Gyro = new Gyro(1);

		m_ds = DriverStation::GetInstance();
		m_ds_lcd = DriverStationLCD::GetInstance();
		
		m_ds_lcd->PrintfLine(DriverStationLCD::kUser_Line1,"Gyro Done Initializing\n");
		m_ds_lcd->UpdateLCD();
		// Initialize the RobotTurnPIDOutput
//		Robot_Turn = new RobotTurnPIDOutput(m_robotDrive);
		
		// Initialize Goal Alignment PID Controller
//		Goal_Align_PID = new PIDController(1.0, 0.0, 1.0, Yaw_Gyro, Robot_Turn);
		
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
        Compressor = new Relay(COMPRESSOR_RELAY_CHANNEL);
        
        // Sharpening Excalibur on the ye old grindstone in the centre of town.
        Disc_Load_In = new Solenoid((int)DigitalIO_CSV->GetValue("DISC_LOAD_IN_ID"));
        Disc_Load_Out = new Solenoid((int)DigitalIO_CSV->GetValue("DISC_LOAD_OUT_ID"));
        Disc_Fire_In = new Solenoid((int)DigitalIO_CSV->GetValue("DISC_FIRE_IN_ID"));
        Disc_Fire_Out = new Solenoid((int)DigitalIO_CSV->GetValue("DISC_FIRE_OUT_ID"));

		printf("CK16_Main Constructor Completed\n");
	}
	
	
	/********************************** Init Routines *************************************/

	void RobotInit(void) {
		// Actions which would be performed once (and only once) upon initialization of the
		// robot would be put here.
		
		// Initialize settings for encoder drive PIDControllers
		Left_Drive_PID->SetOutputRange(-0.2, 0.2);
		Right_Drive_PID->SetOutputRange(-0.2, 0.2);
		Left_Drive_PID->SetTolerance(0.1);
		Right_Drive_PID->SetTolerance(0.1);
		
		// Initialize settings for RobotTurn
//		Goal_Align_PID->SetOutputRange(-0.2, 0.2);
//		Goal_Align_PID->SetTolerance(0.1);
        
        // Set each drive motor to have an encoder to be its friend
        Front_R->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
        Front_L->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
        
        
        // Set encoders
        Front_R->ConfigEncoderCodesPerRev(TICS_PER_REV); 
        Front_L->ConfigEncoderCodesPerRev(TICS_PER_REV);
        
        // Excalibur is sheathed
        Disc_Load_In->Set(false);
        Disc_Load_Out->Set(true);
        Disc_Fire_In->Set(false);
        Disc_Fire_Out->Set(true);
        
        		
		printf("RobotInit() completed.\n");
	}
	
	void DisabledInit(void) {
		m_disabledPeriodicLoops = 0;			// Reset the loop counter for disabled mode
		// Move the cursor down a few, since we'll move it back up in periodic.
		printf("\x1b[2B");
	}

	void AutonomousInit(void) {
		m_autoPeriodicLoops = 0;				// Reset the loop counter for autonomous mode
		
		// Enable left and right encoder PID
//		Left_Drive_PID->Enable();
//		Right_Drive_PID->Enable();
//		Left_Drive_PID->SetSetpoint(0.0);
//		Right_Drive_PID->SetSetpoint(0.0);
		
		// Enable Goal Align PID
//		Goal_Align_PID->Enable();
//		Goal_Align_PID->SetSetpoint(0.0);
		
	}

	void TeleopInit(void) {
		m_telePeriodicLoops = 0;				// Reset the loop counter for teleop mode
		m_dsPacketsReceivedInCurrentSecond = 0;	// Reset the number of dsPackets in current second
		
		// Default autoPilot to off
		autoPilot = false;
		
		// Enable Goal Align PID
//		Goal_Align_PID->Enable();
//		Goal_Align_PID->SetSetpoint(0.0);
		printf("Teleop Init Completed\n");
	}

	/********************************** Periodic Routines *************************************/
	
	void DisabledPeriodic(void)  {
		static INT32 printSec = (INT32)GetClock() + 1;
		static const INT32 startSec = (INT32)GetClock();

		
//		Yaw_Gyro->Reset();

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
//			Left_Drive_PID->SetSetpoint(encoderCounts);
//			Right_Drive_PID->SetSetpoint(encoderCounts);
//			Front_L->ChangeControlMode(CANJaguar::kPosition);
//			Front_R->ChangeControlMode(CANJaguar::kPosition);
//			Front_L->Set(24.0);
//			Front_R->Set(24.0);
			break;
		default:
			break;
		}
	}

	double calculateDriveOutputForTeleop(double input)
	{

		if(fabs(input) < 0.05)
		{
			// Stop if stick is near zero
			return 0.0;
		}
		else
		{
			double mapping;

			if(fabs(input) <= 0.7)
			{
				mapping = 0.33 * pow(fabs(input), 2) + 0.2;
				mapping = (input >= 0) ? mapping : -mapping; // Change to negative if the input was negative
				return mapping;
			}
			else
			{
				mapping = 3.57 * fabs(input) - 2.14;
				mapping = (input >= 0) ? mapping : -mapping; // Change to negative if the input was negative
				return mapping;
			}
		}
	}
	
	void TeleopPeriodic(void) {
		// increment the number of teleop periodic loops completed
		m_telePeriodicLoops++;
		GetWatchdog().Feed();
        
        // Trojan horse has entered Troy
        Compressor->Set((!Pressure_SW->Get() ? Relay::kForward : Relay::kOff));

//		
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
			// Calculate jaguar output based on exponent we pass from SmartDashboard
			double leftOutput, rightOutput;
			leftOutput = -calculateDriveOutputForTeleop(operatorGamepad->GetRawAxis(2));
			rightOutput = -calculateDriveOutputForTeleop(operatorGamepad->GetRawAxis(5));
			
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
			
            // Excalibur was actually a horse and now its running away into the wild blue yonder.
            Disc_Load_In->Set(operatorGamepad->GetRawButton(3));
            Disc_Load_Out->Set(!operatorGamepad->GetRawButton(3));
        
            // Exaclibur's brother is a little sluggish, but has also escaped. This one was a goat.
            Disc_Fire_In->Set(operatorGamepad->GetRawButton(4));
            Disc_Fire_Out->Set(!operatorGamepad->GetRawButton(4));
            
            
			// Auto Align Button
//			if(operatorGamepad->GetButton(Joystick::kTopButton) == 1)
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
START_ROBOT_CLASS(CK16_Main);
