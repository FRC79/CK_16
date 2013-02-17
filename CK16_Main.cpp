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
#include "Timer.h"
#include <string>
#include <math.h>
#include "CSVReader.h"

#include "DiscAutoLoader.h"
#include "Shooter.h"

class CK16_Main: public IterativeRobot {
	void UpdatePreviousButtonStateVariables();

	// Declare CSV readers
	CSVReader *PWM_CSV, *AnalogInputs_CSV, *DigitalIO_CSV, *CAN_IDS_CSV;

	// SmartDashboard Keys

	std::string FOUND_KEY, AZIMUTH_KEY, RANGE_KEY, SHOOTER_TILTED_KEY;
	
	// Declare variable for the robot drive system
	RobotDrive *m_robotDrive; // robot will use PWM 1-4 for drive motors	

	// Robot will use CAN bus for motor control
	CANJaguar *Front_R, *Front_L, *Rear_R, *Rear_L;
	CANJaguar *ShooterFeed,/* watman strikes again*/*ShooterFire;
	CANJaguar *Roller;

    // Declare the IR sensors that facilitate the disc loading and firing process(es)															//wat
    DigitalInput *Front_Beam, *Top_Beam, *Bottom_Beam;
	
    // Declare the BangBang Controller
    
    
	// Digital Input pin for the pressure switch
	DigitalInput *Pressure_SW;

	// Building the Trojan horse.
	Relay *Compressor;

	// Pulling out Excalibers (2x)
	Solenoid *Disc_Load_In, *Disc_Load_Out, *Shooter_Tilt_In,
			*Shooter_Tilt_Out, *Disc_Fire;

	// Declare left and right encoder drive PIDControllers
	CAN_PID_Controller *Left_Drive_PID, *Right_Drive_PID;

	// Declare Gyro that will be used to determine left and right robot rotation
	Gyro *Yaw_Gyro;

	// Declare RobotTurnPIDOutput that will control the robot turning aspect of the goal alignment
	RobotTurnPIDOutput *Robot_Turn;

	// Declare PID Controller that will handle aligning the robot with the goal

	PIDController *Turn_PID;
	
	// State boolean that represents if robot is driving with joystick input or using auto align
	bool autoPilot;
	
	// State boolean to enable and disable manual roller load
	bool autoLoadEnabled, autoLoadWasEnabled, manualRollersEnabled;
	bool discInPosition, discLoaded, discShot;
	unsigned int topBeamPrevState, bottomBeamPrevState;
	
	static const unsigned int BROKEN = 0;
	static const unsigned int SOLID = 1;
	
	bool shooterTiltedUp;

	// Declare a variable to use to access the driver station object
	DriverStation *m_ds; // driver station object
	DriverStationLCD *m_ds_lcd;
	UINT32 /* wat */m_priorPacketNumber; // keep track of the most recent packet number from the DS
	UINT8 m_dsPacketsReceivedInCurrentSecond; // keep track of the ds packets received in the current second

	Joystick *operatorGamepad1;			// joystick 1 (arcade stick or right tank stick)
	Joystick *operatorGamepad2;			// joystick 2 (manipulator joystick/misc. functions)
	
	// Declare variables for previous joystick button states
	bool shooterTiltButtonWasDown, autoLoadToggleButtonWasDown;
	
	// Local variables to count the number of periodic loops performed
	UINT32 m_autoPeriodicLoops;
	UINT32 m_disabledPeriodicLoops;
	UINT32 m_telePeriodicLoops;


	DualSolenoid *m_disc_loader;

	Shooter *m_shooter;
	DiscAutoLoader *m_loader;

public:
	/**
	 * Constructor for this "CK16_Main" Class.
	 * 
	 * The constructor creates all of the objects used for the different inputs and outputs of
	 * the robot.  Essentially, the constructor defines the input/output mapping for the robot,
	 * providing named objects for each of the robot interfaces. 
	 */
	CK16_Main(void) {
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

		SHOOTER_TILTED_KEY = "shooter tilted";

		// Initialize the CAN Jaguars
		Front_R = new CANJaguar((int) CAN_IDS_CSV->GetValue("FR_CAN_ID"));
		Front_L = new CANJaguar((int) CAN_IDS_CSV->GetValue("FL_CAN_ID"));
		Rear_R = new CANJaguar((int) CAN_IDS_CSV->GetValue("RR_CAN_ID"));
		Rear_L = new CANJaguar((int) CAN_IDS_CSV->GetValue("RL_CAN_ID"));
		Roller = new CANJaguar((int) CAN_IDS_CSV->GetValue("ROLLER_MOTOR_CAN_ID"));
		ShooterFeed = new CANJaguar((int) CAN_IDS_CSV->GetValue("FEED_CAN_ID"));
		ShooterFire = new CANJaguar((int) CAN_IDS_CSV->GetValue("FIRE_CAN_ID"));
		printf("TEAM 79 FOR THE WIN!\n");

		// Initialize Robot Drive System Using Jaguars
		m_robotDrive = new RobotDrive(Front_L, Rear_L, Front_R, Rear_R);

		// Initialize Gyro

		Yaw_Gyro = new Gyro((int)AnalogInputs_CSV->GetValue("YAW_GYRO_ID"));

		m_ds = DriverStation::GetInstance();
		m_ds_lcd = DriverStationLCD::GetInstance();

		m_ds_lcd->PrintfLine(DriverStationLCD::kUser_Line1,
				"Gyro Done Initializing\n");
		m_ds_lcd->UpdateLCD();

		// Initialize the RobotTurnPIDOutput
		Robot_Turn = new RobotTurnPIDOutput(m_robotDrive);

		// Initialize Goal Alignment PID Controller

		// Acquire the Driver Station object
		m_priorPacketNumber = 0;
		m_dsPacketsReceivedInCurrentSecond = 0;

		// Define joysticks being used at USB port #1 on the Drivers Station
		operatorGamepad1 = new Joystick(1);
		operatorGamepad2 = new Joystick(2);

		// Initialize counters to record the number of loops completed in autonomous and teleop modes
		m_autoPeriodicLoops = 0;
		m_disabledPeriodicLoops = 0;
		m_telePeriodicLoops = 0;

		// Initialize pressure switch input channel

		Pressure_SW = new DigitalInput(RobotConfiguration::PRESSURE_SWITCH_CHANNEL);
		
		// Initialize IR beams for loading and firing discs
		Front_Beam = new DigitalInput(4);
		Top_Beam = new DigitalInput(3);
		Bottom_Beam = new DigitalInput(2);
		
        // Filling the Trojan horse with people, then shipping it off to Troy.
        Compressor = new Relay(RobotConfiguration::COMPRESSOR_RELAY_CHANNEL);
        
        // Sharpening Excalibur on the ye old grindstone in the centre of town.
        Disc_Load_In = new Solenoid((int)DigitalIO_CSV->GetValue("DISC_LOAD_IN_ID"));
        Disc_Load_Out = new Solenoid((int)DigitalIO_CSV->GetValue("DISC_LOAD_OUT_ID"));
        Disc_Fire = new Solenoid((int)DigitalIO_CSV->GetValue("DISC_FIRE_ID"));
        Shooter_Tilt_In = new Solenoid((int)DigitalIO_CSV->GetValue("SHOOTER_TILT_IN_ID"));
        Shooter_Tilt_Out = new Solenoid((int)DigitalIO_CSV->GetValue("SHOOTER_TILT_OUT_ID"));
       

        m_disc_loader = new DualSolenoid(Disc_Load_In, Disc_Load_Out, false, false);

        m_loader = new DiscAutoLoader(Roller, m_disc_loader, Top_Beam, Bottom_Beam);
        m_shooter = new Shooter(ShooterFeed,ShooterFire,Disc_Fire, m_loader;

		printf("CK16_Main Constructor Completed\n");
	}

	/********************************** Init Routines *************************************/

	void RobotInit(void) {
		// Actions which would be performed once (and only once) upon initialization of the
		// robot would be put here.

		// Initialize settings for RobotTurn

//		Turn_PID->SetOutputRange(-0.2, 0.2);
//		Turn_PID->SetTolerance(0.05);
        
		// Shooter wheel encoders (fire is front, feed is back)
//		ShooterFeed->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
//		ShooterFire->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
//		ShooterFeed->ConfigEncoderCodesPerRev(TICS_PER_REV);
//		ShooterFire->ConfigEncoderCodesPerRev(TICS_PER_REV);
		
		
        // Set each drive motor to have an encoder to be its friend
        Front_R->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
        Front_L->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
        Front_R->ConfigEncoderCodesPerRev(TICS_PER_REV); 
        Front_L->ConfigEncoderCodesPerRev(TICS_PER_REV);
        
        // Excalibur is sheathed
        Disc_Load_In->Set(false);
        Disc_Load_Out->Set(true);
        Disc_Fire->Set(false);
        Shooter_Tilt_In->Set(false);
        Shooter_Tilt_Out->Set(true);
        
        // Set shooter tilted to false
        shooterTiltedUp = false;
        
        // Init Button Previous States
        shooterTiltButtonWasDown = false;
        autoLoadToggleButtonWasDown = false;
        		
		printf("RobotInit() completed.\n");
	}

	void DisabledInit(void) {
		m_disabledPeriodicLoops = 0; // Reset the loop counter for disabled mode

		// Reset and Disable Goal Alignment PID Controller

//		Turn_PID->Reset(); // The Disable method will not reset Integral term nor the error
		autoPilot = false;

		// Move the cursor down a few, since we'll move it back up in periodic.
		printf("\x1b[2B");
	}

	void AutonomousInit(void) {
		m_autoPeriodicLoops = 0; // Reset the loop counter for autonomous mode

		// Enable Goal Align PID
		//		Goal_Align_PID->Enable();
		//		Goal_Align_PID->SetSetpoint(0.0);
		
		
		printf("Auton Init Completed\n");
	}

	void TeleopInit(void) {
		m_telePeriodicLoops = 0;				// Reset the loop counter for teleop mode
		m_dsPacketsReceivedInCurrentSecond = 0;	// Reset the number of dsPackets in current second
		
		autoLoadEnabled = false;
		autoLoadWasEnabled = false;
		manualRollersEnabled = true;
		topBeamPrevState = SOLID;
		bottomBeamPrevState = SOLID;
		
		discInPosition = false;
		discLoaded = false;
		
		printf("Teleop Init Completed\n");
	}

	/********************************** Periodic Routines *************************************/

	void DisabledPeriodic(void) {
		static INT32 printSec = (INT32) GetClock() + 1;
		static const INT32 startSec = (INT32) GetClock();

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
		
		Compressor->Set((!Pressure_SW->Get() ? Relay::kForward : Relay::kOff));
		
		if(m_autoPeriodicLoops % 100 == 0)
		{
			SmartDashboard::PutNumber("BACK ENCODER POS", ShooterFeed->GetPosition());
			SmartDashboard::PutNumber("FRONT ENCODER POS", ShooterFire->GetPosition());
		}
	}

	void TeleopPeriodic(void) {
		// increment the number of teleop periodic loops completed
		m_telePeriodicLoops++;
		GetWatchdog().Feed();

		// Print Pressure Switch for testing

        // Trojan horse has entered Troy
        Compressor->Set((!Pressure_SW->Get() ? Relay::kForward : Relay::kOff));
        
		if(autoPilot == true)
		{
			// Auto Align Disable Button
//			if(operatorGamepad1->GetRawButton(8))
//			{
//				Turn_PID->Disable(); // Stop outputs
//				autoPilot = false;
//			}
		}
		else
		{
			// Map joystick position to speed value through a special equation
			double leftOutput, rightOutput;
			leftOutput = -TeleopHelper::mapJoystickToSpeedOutput(operatorGamepad1->GetRawAxis(2));
			rightOutput = -TeleopHelper::mapJoystickToSpeedOutput(operatorGamepad1->GetRawAxis(5));
			
			// Joystick Driving
			m_robotDrive->SetLeftRightMotorOutputs(leftOutput, rightOutput);
			
//			printf("Left Encoder Distance: %f\nRight Encoder Distance: %f\n", Front_L->GetPosition()*INCHES_PER_TIC, Front_R->GetPosition()*INCHES_PER_TIC);
			
//			m_ds_lcd->PrintfLine(DriverStationLCD::kUser_Line2, "Gyro: %f", Yaw_Gyro->GetAngle());			
			m_ds_lcd->UpdateLCD();
            
            // Excalibur was actually a horse and now its running away into the wild blue yonder.
            
        
            // Exaclibur's brother is a little sluggish, but has also escaped. This one was a goat.
            Disc_Fire->Set(operatorGamepad2->GetRawButton(4));
            
            // Excalibur has a cousin
            if(operatorGamepad1->GetRawButton(1) && !shooterTiltButtonWasDown) // Only accept a button press (not hold)
            {
            	shooterTiltedUp = !shooterTiltedUp; // Toggle tilt solenoid
            } 
            Shooter_Tilt_In->Set(!shooterTiltedUp);
            Shooter_Tilt_Out->Set(shooterTiltedUp);
            shooterTiltButtonWasDown = operatorGamepad1->GetRawButton(1); // Update previous button value to current
            SmartDashboard::PutBoolean(SHOOTER_TILTED_KEY, shooterTiltedUp); // Output current state to SmartDashboard
            
			// Auto Align Button
//			if(operatorGamepad1->GetRawButton(7))
//			{
				// Turn Auto Align on if we see a goal and we know the azimuth
//				if(SmartDashboard::GetBoolean(FOUND_KEY) == true)
//				{
//					Goal_Align_PID->Enable();
//					Goal_Align_PID->SetSetpoint(0.0);
//					autoPilot = true;
//				}
//			}
            
			// Enable and disable autoLoad
			if(operatorGamepad2->GetRawButton(1) && !autoLoadToggleButtonWasDown) // Only accept a button press (not hold)
            {
            	autoLoadEnabled = !autoLoadEnabled; // Toggle autoLoad
            	autoLoadWasEnabled = !autoLoadWasEnabled;
            	autoLoadToggleButtonWasDown = true;
            }
			else if(!operatorGamepad2->GetRawButton(1) && autoLoadToggleButtonWasDown)
			{
				autoLoadToggleButtonWasDown = false;
			}
			
			// Shooter code
			if(operatorGamepad2->GetRawButton(2))
			{
				ShooterFeed->Set(-0.57); // was 57
				ShooterFire->Set(-0.57);
			}
			else
			{
				ShooterFeed->Set(0.0);
				ShooterFire->Set(0.0);
			}
			
			if(operatorGamepad2->GetRawButton(3))
			{
				m_shooter->Fire();
			}
		}
	}
};

START_ROBOT_CLASS(CK16_Main);
