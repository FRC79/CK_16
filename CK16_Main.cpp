#include "WPILib.h"
#include "CANJaguar.h"
#include "Joystick.h"
#include "CAN_PID_Controller.h"
#include "Gyro.h"
#include "RobotTurnPIDOutput.h"
#include "PIDController.h"
#include "CAN_VPID_Controller.h"
#include "RobotConfiguration.h"
#include "TeleopHelper.h"
#include "DualSolenoid.h"
#include "DiscAutoLoader.h"
#include "ButtonHelper.h"
#include "SmartDashboard/SmartDashboard.h"
#include <string>
#include <math.h>
#include "CSVReader.h"

class CK16_Main: public IterativeRobot {
	void UpdatePreviousButtonStateVariables();

	// Declare CSV readers
	CSVReader *PWM_CSV, *AnalogInputs_CSV, *DigitalIO_CSV, *Solenoid_CSV, *CAN_IDS_CSV;

	// SmartDashboard Keys
	std::string FOUND_KEY, AZIMUTH_KEY, RANGE_KEY, SHOOTER_TILTED_KEY, SHOOTER_POWER_KEY,
		SHOOTER_SPEED_KEY;
	
	// Declare variable for the robot drive system
	RobotDrive *m_robotDrive; // robot will use PWM 1-4 for drive motors	

	// Robot will use CAN bus for motor control
	CANJaguar *Front_R, *Front_L, *Rear_R, *Rear_L;
	CANJaguar *ShooterFeed,/* watman strikes again*/*ShooterFire;
	CANJaguar *Roller;
	
	// Shooter Velocity controller
//	CAN_VPID_Controller *ShooterFeedSpeed, *ShooterFireSpeed;
	
	// Shooter Power setting
	float shooterSpeed, shooterPower;
	
	// Roller Power setting
	float rollerPower;
	
    // Declare the IR sensors that facilitate the disc loading and firing process(es)															//wat
    DigitalInput *Top_Beam, *Bottom_Beam, *Front_Beam;
    
	// Digital Input pin for the pressure switch
	DigitalInput *Pressure_SW;

	// Building the Trojan horse.
	Relay *Compressor;

	// Pulling out Excalibers (2x)
	Solenoid *Hang_A_In, *Hang_A_Out, *Hang_B_In, *Hang_B_Out, *Shooter_Tilt_In, *Disc_Load,
			*Shooter_Tilt_Out, *Disc_Fire;
	
	// Declaring DualSolenoids
	DualSolenoid *Shooter_Tilt, *Hang_A, *Hang_B;

	// Declare left and right encoder drive PIDControllers
	CAN_PID_Controller *Left_Drive_PID, *Right_Drive_PID;

	// Declare Gyro that will be used to determine left and right robot rotation
	Gyro *Yaw_Gyro;

	// Declare RobotTurnPIDOutput that will control the robot turning aspect of the goal alignment
//	RobotTurnPIDOutput *Robot_Turn;

	// Declare PID Controller that will handle robot robot turning with gyro
//	PIDController *Turn_PID;
	
	// State boolean that represents if robot is driving with joystick input or using auto align
	bool autoPilot;
	
	// Declare a DiscAutoLoader for use in teleop mode
//	DiscAutoLoader *Auto_Loader;
	
	// State booleans for auto loading and manual loading
	bool hangClawsOut;
	bool autoLoadEnabled, loadWasHalted;
	bool shooterWheelsSpinning;
	bool autonEnabled;
	
	// State boolean for shooter tilt funcitonality
	bool shooterTiltedUp;

	// Beam Constants
	static const unsigned int BROKEN = 0;
	static const unsigned int SOLID = 1;
	
	// Declare a variable to use to access the driver station object
	DriverStation *m_ds; // driver station object
	DriverStationLCD *m_ds_lcd;
	UINT32 /* wat */m_priorPacketNumber; // keep track of the most recent packet number from the DS
	UINT8 m_dsPacketsReceivedInCurrentSecond; // keep track of the ds packets received in the current second

	Joystick *operatorGamepad1;			// joystick 1 (arcade stick or right tank stick)
	Joystick *operatorGamepad2;			// joystick 2 (manipulator joystick/misc. functions)
	
	// Declare ButtonHelper for each gamepads
	ButtonHelper *buttonHelper1, *buttonHelper2;
	
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
	CK16_Main(void) {
		printf("CK16_Main Constructor Started\n");

		// Configuration files
		printf("Loading the configuration files.\n");
		AnalogInputs_CSV = new CSVReader("AnalogInputs.csv");
		CAN_IDS_CSV = new CSVReader("CAN_IDs.csv");
		DigitalIO_CSV = new CSVReader("DigitalIO.csv");
		Solenoid_CSV = new CSVReader("Solenoid.csv");
		PWM_CSV = new CSVReader("PWM.csv");

		// Initialize SmartDashboard Keys
		FOUND_KEY = "found";
		AZIMUTH_KEY = "azimuth";
		RANGE_KEY = "range";
		SHOOTER_POWER_KEY = "shooter power";
		SHOOTER_SPEED_KEY = "shooter speed";
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
		
		// Shooter Power
		shooterSpeed = 4.0;
		shooterPower = 0.6;
		
		// Shooter Velocity Controller
//		ShooterFeedSpeed = new CAN_VPID_Controller(0.5, 1.0, 0.0, ShooterFeed, ShooterFeed);
//		ShooterFireSpeed = new CAN_VPID_Controller(0.5, 1.0, 0.0, ShooterFire, ShooterFire);

		// Initialize Robot Drive System Using Jaguars
		m_robotDrive = new RobotDrive(Front_L, Rear_L, Front_R, Rear_R);

		// Initialize Gyro
//		Yaw_Gyro = new Gyro((int)AnalogInputs_CSV->GetValue("YAW_GYRO_ID"));

		m_ds = DriverStation::GetInstance();
		m_ds_lcd = DriverStationLCD::GetInstance();

		m_ds_lcd->PrintfLine(DriverStationLCD::kUser_Line1,
				"Gyro Done Initializing\n");
		m_ds_lcd->UpdateLCD();

		// Initialize the RobotTurnPIDOutput
//		Robot_Turn = new RobotTurnPIDOutput(m_robotDrive);

		// Initialize Goal Alignment PID Controller

		// Acquire the Driver Station object
		m_priorPacketNumber = 0;
		m_dsPacketsReceivedInCurrentSecond = 0;

		// Define joysticks being used at USB port #1 on the Drivers Station
		operatorGamepad1 = new Joystick(1);
		operatorGamepad2 = new Joystick(2);
		
		// Initialize joystick button helpers
		buttonHelper1 = new ButtonHelper(operatorGamepad1);
		buttonHelper2 = new ButtonHelper(operatorGamepad2);

		// Initialize counters to record the number of loops completed in autonomous and teleop modes
		m_autoPeriodicLoops = 0;
		m_disabledPeriodicLoops = 0;
		m_telePeriodicLoops = 0;

		// Filling the Trojan horse with people, then shipping it off to Troy.
		Compressor = new Relay(RobotConfiguration::COMPRESSOR_RELAY_CHANNEL);
		
		// Initialize pressure switch input channel
		Pressure_SW = new DigitalInput(RobotConfiguration::PRESSURE_SWITCH_CHANNEL);
		
		// Sharpening Excalibur on the ye old grindstone in the centre of town.
        Disc_Load = new Solenoid((int)Solenoid_CSV->GetValue("DISC_LOAD_ID"));
        Disc_Fire = new Solenoid((int)Solenoid_CSV->GetValue("DISC_FIRE_ID"));
        Shooter_Tilt_In = new Solenoid((int)Solenoid_CSV->GetValue("SHOOTER_TILT_IN_ID"));
        Shooter_Tilt_Out = new Solenoid((int)Solenoid_CSV->GetValue("SHOOTER_TILT_OUT_ID"));
        Hang_A_In = new Solenoid((int)Solenoid_CSV->GetValue("HANG_A_IN_ID"));
        Hang_A_Out = new Solenoid((int)Solenoid_CSV->GetValue("HANG_A_OUT_ID"));
        Hang_B_In = new Solenoid((int)Solenoid_CSV->GetValue("HANG_B_IN_ID"));
        Hang_B_Out = new Solenoid((int)Solenoid_CSV->GetValue("HANG_B_OUT_ID"));
        
        // Initialize DualSolenoids
        Shooter_Tilt = new DualSolenoid(Shooter_Tilt_In, Shooter_Tilt_Out, false, false);
        Hang_A = new DualSolenoid(Hang_A_In, Hang_A_Out, false, false);
        Hang_B = new DualSolenoid(Hang_B_In, Hang_B_Out, false, false);
        
        // Initialize IR beams for loading and firing discs
		Top_Beam = new DigitalInput((int)DigitalIO_CSV->GetValue("TOP_BEAM_ID"));
		Bottom_Beam = new DigitalInput((int)DigitalIO_CSV->GetValue("BOTTOM_BEAM_ID"));
		Front_Beam = new DigitalInput((int)DigitalIO_CSV->GetValue("FRONT_BEAM_ID"));
        
		// Initialize DiscAutoLoader
//		Auto_Loader = new DiscAutoLoader(Roller, Disc_Load, Top_Beam, Bottom_Beam);
		
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
		ShooterFeed->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
		ShooterFire->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
		ShooterFeed->ConfigEncoderCodesPerRev(TICS_PER_SHOOTER_REV);
		ShooterFire->ConfigEncoderCodesPerRev(TICS_PER_SHOOTER_REV);
		
		// Init shooter power on NetworkTable
		SmartDashboard::PutNumber(SHOOTER_POWER_KEY, shooterSpeed);
		
		// Shooter Velocity Controller
//		ShooterFeedSpeed->SetOutputRange(0.0, 1.0);
//		ShooterFireSpeed->SetOutputRange(0.0, 1.0);
		
        // Set each drive motor to have an encoder to be its friend
        Front_R->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
        Front_L->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
        Front_R->ConfigEncoderCodesPerRev(TICS_PER_REV); 
        Front_L->ConfigEncoderCodesPerRev(TICS_PER_REV);
        
        // Inverting RobotDrive motors
        m_robotDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
        m_robotDrive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
        m_robotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
        m_robotDrive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
        
        // Set shooter tilted to false
        shooterTiltedUp = true;
        
        		
		printf("RobotInit() completed.\n");
	}

	void DisabledInit(void) {
		m_disabledPeriodicLoops = 0; // Reset the loop counter for disabled mode

		// Reset and Disable Turn PID
//		Turn_PID->Reset(); // The Disable method will not reset Integral term nor the error
		autoPilot = false;
		
		// Disable AutoLoader
//		Auto_Loader->Disable();
		
		// Disable Shooter speed controller
//		ShooterFeedSpeed->Disable();
//		ShooterFireSpeed->Disable();

		// Move the cursor down a few, since we'll move it back up in periodic.
		printf("\x1b[2B");
	}

	void AutonomousInit(void) {
		m_autoPeriodicLoops = 0; // Reset the loop counter for autonomous mode

		// Enable Goal Align PID
//		Goal_Align_PID->Enable();
//		Goal_Align_PID->SetSetpoint(0.0);
		
		// Excalibur is sheathed
        Disc_Load->Set(false);
        Disc_Fire->Set(false);
        Shooter_Tilt->Set(true);
        Hang_A->Set(false);
        Hang_B->Set(true);
        
        // Set shooter tilted to false
        shooterTiltedUp = true;
        
        
        //MAKE SURE TO KEEP THIS
        autonEnabled = true;
		
		printf("Auton Init Completed\n");
	}

	void TeleopInit(void) {
		m_telePeriodicLoops = 0;				// Reset the loop counter for teleop mode
		m_dsPacketsReceivedInCurrentSecond = 0;	// Reset the number of dsPackets in current second
		
		// Excalibur is sheathed
        Disc_Load->Set(false);
        Disc_Fire->Set(false);
        Shooter_Tilt->Set(true);
        Hang_A->Set(false);
        Hang_B->Set(true);
        
        // Set shooter tilted to false
        shooterTiltedUp = true;
		
		// Initialize all state variables
		autoLoadEnabled = false;
		loadWasHalted = false;
		shooterWheelsSpinning = false;
		hangClawsOut = false;
		
		// Shooter Velocity Controller
//		ShooterFeedSpeed->Enable();
//		ShooterFeedSpeed->SetSetpoint(0.0);
//		ShooterFireSpeed->Enable();
//		ShooterFireSpeed->SetSetpoint(0.0);
		
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
		
		if(autonEnabled)
		{
			Wait(0.25);
						
			ShooterFeed->Set(-0.6);
			ShooterFire->Set(-0.6);
			
			Wait(4.0); // Wait 4 secs
			
			Disc_Fire->Set(true); // fire
			
			Wait(1.0); // Hold it out
			
			Disc_Fire->Set(false); // close
			
			Wait(1.0); // Wait to avoid clashing of pistons
			
			Disc_Load->Set(true);
			
			Wait(1.0); // Load it
			
			Disc_Load->Set(false);
			
			Wait(1.0); // Wait for it to come up
			
			Disc_Fire->Set(true); // fire
					
			Wait(1.0); // Hold it out
			
			Disc_Fire->Set(false); // close
			
			Wait(1.0);
			
			ShooterFeed->Set(0.0);
			ShooterFire->Set(0.0);
			
			autonEnabled = false;
		}
	}

	void TeleopPeriodic(void) {
		// increment the number of teleop periodic loops completed
		m_telePeriodicLoops++;
		GetWatchdog().Feed();

		// Update the button helpers
		buttonHelper1->Update();
		buttonHelper2->Update();
		
		// Hang Code
		if(buttonHelper1->WasButtonToggled(1))
		{
			hangClawsOut = !hangClawsOut;
		}
		Hang_A->Set(hangClawsOut);
		Hang_B->Set(!hangClawsOut);
		
		// Keep filling up the compressor until it hits the desired psi
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
			// Auto Align Button
//			if(operatorGamepad1->GetRawButton(CAN'T BE 7))
//			{
				// Turn Auto Align on if we see a goal and we know the azimuth
//				if(SmartDashboard::GetBoolean(FOUND_KEY) == true)
//				{
//					Goal_Align_PID->Enable();
//					Goal_Align_PID->SetSetpoint(0.0);
//					autoPilot = true;
//				}
//			}
			
//			// Map joystick position to speed value through a special equation
//			double leftOutput, rightOutput;
//			leftOutput = TeleopHelper::mapJoystickToSpeedOutput(operatorGamepad1->GetRawAxis(2));
//			rightOutput = TeleopHelper::mapJoystickToSpeedOutput(operatorGamepad1->GetRawAxis(5));
//			
//			// Joystick Driving
//			m_robotDrive->SetLeftRightMotorOutputs(leftOutput, rightOutput);
			
			// Map joystick position to speed value through a special equation
			double transOutput, rotOutput;
			transOutput = TeleopHelper::mapJoystickToSpeedOutput(operatorGamepad1->GetRawAxis(5));
			rotOutput = TeleopHelper::mapJoystickToSpeedOutput(operatorGamepad1->GetRawAxis(4));
			
			// Joystick arcade driving on right joystick
			m_robotDrive->ArcadeDrive(transOutput, rotOutput, false);
			
			// Update value for power to shooter
			if(buttonHelper1->WasButtonToggled(3))
			{
				shooterPower = SmartDashboard::GetNumber(SHOOTER_POWER_KEY);
			}
            
            // Shooter tilt toggle
            if(buttonHelper2->WasButtonToggled(5) || buttonHelper1->WasButtonToggled(5)) // Only accept a button press (not hold)
            {
            	shooterTiltedUp = !shooterTiltedUp; // Toggle tilt solenoid
            } 
            Shooter_Tilt->Set(shooterTiltedUp);
            SmartDashboard::PutBoolean(SHOOTER_TILTED_KEY, shooterTiltedUp); // Output current state to SmartDashboard
            
			// Enable and disable autoLoad (only if the autoload is not halted)
//			if(buttonHelper1->WasButtonToggled(5) && !loadWasHalted && autoLoadEnabled)
//			{
//				Auto_Loader->Disable(); // Disable
//				autoLoadEnabled = false;
//			}
//			else if(buttonHelper1->WasButtonToggled(CAN'T BE 5) && !loadWasHalted && !autoLoadEnabled)
//			{
//				Auto_Loader->Reset(); // Enable
//				autoLoadEnabled = true;
//			}
			
			// Toggle Shooter Wheels on and off
			if(buttonHelper2->WasButtonToggled(2))
			{
				shooterWheelsSpinning = !shooterWheelsSpinning;
			}
			
			// Shooter wheel state changing
			if(shooterWheelsSpinning)
			{
				ShooterFeed->Set(-shooterPower);
				ShooterFire->Set(-shooterPower);
			}
			else
			{
				ShooterFeed->Set(0.0);
				ShooterFire->Set(0.0);
			}
			
			// Fire piston that shoots the disc and halt loading if the piston is fired.
			Disc_Fire->Set(operatorGamepad2->GetRawButton(6));
//			loadWasHalted = operatorGamepad1->GetRawButton(7);
			
			// Punch down (load) piston
			Disc_Load->Set(operatorGamepad2->GetRawButton(1));
			
			// Auto and manual disc loading
			if(autoLoadEnabled && !loadWasHalted)
			{	
				// Autoloading
//				Auto_Loader->AutoLoad();
			}
			else if(!autoLoadEnabled && !loadWasHalted)
			{
				if(operatorGamepad2->GetRawButton(7))
				{
					// Roll out (reverse)
					Roller->Set(-0.5);
				}
				else if(operatorGamepad2->GetRawButton(3))
				{
					if(Top_Beam->Get() == SOLID || Front_Beam->Get() == SOLID)
					{
						// Run rollers
						Roller->Set(0.5);
					}
					else
					{
						// Stop rollers
						Roller->Set(0.0);
					}
				}
				else
				{
					// Stop
					Roller->Set(0.0);
				}
			}
		}
	}
};

START_ROBOT_CLASS(CK16_Main);
