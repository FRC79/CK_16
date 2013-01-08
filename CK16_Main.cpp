#include "WPILib.h"
#include "Joystick.h"
#include "CANJaguar.h"
#include "RobotConfiguration.h"
#include "DigitalInput.h"
#include "Relay.h"
#include "Solenoid.h"
#include "CAN_VPID_Controller.h"
#include "CK16_Auton.h"
#include "Timer.h"
#include "CSVReader.h"
/**
 * Disabled Mode:
 * - Once per second, print (on the console) the number of seconds the robot has been disabled.
 *
 * Autonomous Mode:
 * - When enabled in autonomous mode, check the compressor
 *
 * Teleop Mode:
 * - Do stuff
 * 
 * This code assumes the following connections:
 * - Driver Station:
 *   - USB 1 - The "right" joystick.  Used for arcade drive
 *   - USB 3 - The "shooter" joystick. Used for shooter control
 */
class CK16_Main : public IterativeRobot
{
	// Declare variable for the robot drive system
	RobotDrive *m_robotDrive;
	
	// robot will use CAN bus for motor control
	CANJaguar *Front_R, *Front_L, *Rear_R, *Rear_L;

	// Declare a variable to use to access the driver station object
	DriverStation *m_ds;						// driver station object
	UINT32 m_priorPacketNumber;					// keep track of the most recent packet number from the DS
	UINT8 m_dsPacketsReceivedInCurrentSecond;	// keep track of the ds packets received in the current second

	// Declare variables for the two joysticks being used
	Joystick *Drive_Stick;			// joystick 1 (arcade stick)

	// Local variables to count the number of periodic loops performed
	UINT32 m_autoPeriodicLoops;
	UINT32 m_disabledPeriodicLoops;
	UINT32 m_telePeriodicLoops;
	

	CSVReader *m_config; // Ask what this is, and if it matters or not.

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

		printf("Loading configuration file...");
		m_config = new CSVReader("RobotConfig.csv");
		
		// Initialize the Jaguars as using CAN bus
		Front_R = new CANJaguar(RobotConfiguration::FR_CAN_ID);
		Front_L = new CANJaguar(RobotConfiguration::FL_CAN_ID);
		Rear_R  = new CANJaguar(RobotConfiguration::RR_CAN_ID);
		Rear_L  = new CANJaguar(RobotConfiguration::RL_CAN_ID);
	
		// Initialize the robot drive system using the Jaguars
		m_robotDrive = new RobotDrive(Front_L, Rear_L, Front_R, Rear_R);
	
		// Acquire the Driver Station object
		m_ds = DriverStation::GetInstance();
		m_priorPacketNumber = 0;
		m_dsPacketsReceivedInCurrentSecond = 0;

		// Define joysticks being used at USB port #1 on the Drivers Station
		Drive_Stick = new Joystick(1);
	
		// Initialize counters to record the number of loops completed in autonomous and teleop modes
		m_autoPeriodicLoops = 0;
		m_disabledPeriodicLoops = 0;
		m_telePeriodicLoops = 0;
		//
		auton = new CK16_Auton(Front_R,Front_L,Rear_R,Rear_L,m_config);
		
		printf("CK16_Main Constructor Completed -- Jess\n");
	}


	/********************************** Init Routines *************************************/

	void RobotInit(void) {
		// Actions which would be performed once (and only once) upon initialization of the
		// robot would be put here.		printf("Initializing drive wheel encoders...\n");

		// Set each front drive motor to have a quadrature encoder attached
		Front_R->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
		Front_L->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);

		// Set the encoders to 360 counts per revolution
		Front_R->ConfigEncoderCodesPerRev(360);
		Front_L->ConfigEncoderCodesPerRev(360);
	
		printf("RobotInit() completed.\n");
	}

	void DisabledInit(void) {
		m_disabledPeriodicLoops = 0;			// Reset the loop counter for disabled mode
		// Move the cursor down a few, since we'll move it back up in periodic.
		printf("\x1b[2B");
	}

	void AutonomousInit(void) {
		m_autoPeriodicLoops = 0;				// Reset the loop counter for autonomous mode
		auton->initialize();
	}

	void TeleopInit(void) {
		m_telePeriodicLoops = 0;				// Reset the loop counter for teleop mode
		m_dsPacketsReceivedInCurrentSecond = 0;	// Reset the number of dsPackets in current second
		// If we are in debug mode we want to reload these values every time we enable
		// Otherwise we don't reload them. The default is to hopefully load some numbers in when 
		// we didn't get data.
		if((int)m_config->GetValueWithDefault("Debug_Mode",1.0))
		{
			m_config->ReloadValues(); // Refreshes the config values
		}
	
	}

	/********************************** Periodic Routines *************************************/

	void DisabledPeriodic(void)  {
		static INT32 printSec = (INT32)GetClock() + 1;
		static const INT32 startSec = (INT32)GetClock();


		// increment the number of disabled periodic loops completed
		m_disabledPeriodicLoops++;
		auton->autonStartClock();
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
		//Reset();
		GetWatchdog().Feed();
		auton->step(m_autoPeriodicLoops);
		
		// Check the pressure switch and drive the compressor accordingly
		Compressor->Set((!Pressure_SW->Get() ? Relay::kForward : Relay::kOff));
	}


	void TeleopPeriodic(void) {

		// increment the number of teleop periodic loops completed
		m_telePeriodicLoops++;

		GetWatchdog().Feed();

		/*
		 * Code placed in here will be called only when a new packet of information
		 * has been received by the Driver Station.  Any code which needs new information
		 * from the DS should go in here
		 */

		m_dsPacketsReceivedInCurrentSecond++;					// increment DS packets received

		// put Driver Station-dependent code here

		m_robotDrive->ArcadeDrive(Drive_Stick);			// drive with arcade style (use right stick)
		
	} // TeleopPeriodic(void)

}; // end of class CK16_Main

START_ROBOT_CLASS(CK16_Main);
