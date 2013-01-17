#include "WPILib.h"
#include "CANJaguar.h"
#include "Joystick.h"
#include "Gyro.h"
#include "RobotTurnPIDOutput.h"
#include "PIDController.h"
#include "RobotConfiguration.h"
#include "SmartDashboard/SmartDashboard.h"
#include <string>

class CK16_Main : public IterativeRobot
{	
	// SmartDashboard Keys
	std::string FOUND_KEY, AZIMUTH_KEY, RANGE_KEY;
	
	// Declare variable for the robot drive system
	RobotDrive *m_robotDrive;		// robot will use PWM 1-4 for drive motors
	
	//Robot will use CAN bus for motor control
	CANJaguar *Front_R, *Front_L, *Rear_R, *Rear_L;
	
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
	UINT32 m_priorPacketNumber;					// keep track of the most recent packet number from the DS
	UINT8 m_dsPacketsReceivedInCurrentSecond;	// keep track of the ds packets received in the current second
	
	// Declare variables for the two joysticks being used
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

		// Initialize SmartDashboard Keys
		FOUND_KEY = "found";
		AZIMUTH_KEY = "azimuth";
		RANGE_KEY = "range";
		
		// Initialize the CAN Jaguars
		Front_R = new CANJaguar(RobotConfiguration::FR_CAN_ID);
		Front_L = new CANJaguar(RobotConfiguration::FL_CAN_ID);
		Rear_R = new CANJaguar(RobotConfiguration::RR_CAN_ID);
		Rear_L = new CANJaguar(RobotConfiguration::RL_CAN_ID);
		printf("TEAM 79 FOR THE WIN!\n");
		
		// Initialize Robot Drive System Using Jaguars
		m_robotDrive = new RobotDrive(Front_L, Rear_L, Front_R, Rear_R);

		// Jags on the right side will show full reverse even when going full forward PLEASE BE AWARE
		
		// Initialize Gyro
		Yaw_Gyro = new Gyro(RobotConfiguration::YAW_GYRO);
		
		// Initialize the RobotTurnPIDOutput
		Robot_Turn = new RobotTurnPIDOutput(m_robotDrive);
		
		// Initialize Goal Alignment PID Controller
		Goal_Align_PID = new PIDController(1.0, 0.0, 0.5, Yaw_Gyro, Robot_Turn);
		
		// Acquire the Driver Station object
		m_ds = DriverStation::GetInstance();
		m_priorPacketNumber = 0;
		m_dsPacketsReceivedInCurrentSecond = 0;

		// Define joysticks being used at USB port #1 on the Drivers Station
		operatorGamepad = new Joystick(1);

		// Initialize counters to record the number of loops completed in autonomous and teleop modes
		m_autoPeriodicLoops = 0;
		m_disabledPeriodicLoops = 0;
		m_telePeriodicLoops = 0;

		printf("CK16_Main Constructor Completed\n");
	}
	
	
	/********************************** Init Routines *************************************/

	void RobotInit(void) {
		// Actions which would be performed once (and only once) upon initialization of the
		// robot would be put here.
		
		// Set Output range for RobotTurn
		Goal_Align_PID->SetOutputRange(-0.2, 0.2);
		Goal_Align_PID->SetTolerance(0.1);
		
		printf("RobotInit() completed.\n");
	}
	
	void DisabledInit(void) {
		m_disabledPeriodicLoops = 0;			// Reset the loop counter for disabled mode
		// Move the cursor down a few, since we'll move it back up in periodic.
		printf("\x1b[2B");
	}

	void AutonomousInit(void) {
		m_autoPeriodicLoops = 0;				// Reset the loop counter for autonomous mode
		
		// Enable Goal Align PID
		Goal_Align_PID->Enable();
		Goal_Align_PID->SetSetpoint(0.0);
		
	}

	void TeleopInit(void) {
		m_telePeriodicLoops = 0;				// Reset the loop counter for teleop mode
		m_dsPacketsReceivedInCurrentSecond = 0;	// Reset the number of dsPackets in current second
		
		// Default autoPilot to off
		autoPilot = false;
		
		// Enable Goal Align PID
		Goal_Align_PID->Enable();
		Goal_Align_PID->SetSetpoint(0.0);
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

		
	}

	
	void TeleopPeriodic(void) {
		// increment the number of teleop periodic loops completed
		m_telePeriodicLoops++;
		GetWatchdog().Feed();

		if(autoPilot == true)
		{
			// Auto Align Disable Button
			if(operatorGamepad->GetButton(Joystick::kTopButton) == 2)
			{
				Goal_Align_PID->Disable();
				Goal_Align_PID->SetSetpoint(0.0);
				autoPilot = false;
			}
		}
		else
		{
			// Joystick Driving
			m_robotDrive->SetLeftRightMotorOutputs(operatorGamepad->GetRawAxis(2), operatorGamepad->GetRawAxis(5));
			
			// Auto Align Button
			if(operatorGamepad->GetButton(Joystick::kTopButton) == 1)
			{
				// Turn Auto Align on if we see a goal and we know the azimuth
				if(SmartDashboard::GetBoolean(FOUND_KEY) == true)
				{
					Goal_Align_PID->SetSetpoint(SmartDashboard::GetNumber(AZIMUTH_KEY));
					autoPilot = true;
				}
			}
		}
		
		
	}  
	
	//TeleopPeriodic(void)
			
};
START_ROBOT_CLASS(CK16_Main);
