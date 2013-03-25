#include "RobotMap.h"

// Initialize a single  instance of all of our CSVReaders to NULL
CSVReader* RobotMap::AnalogInputs_CSV = NULL;
CSVReader* RobotMap::CAN_IDS_CSV = NULL;
CSVReader* RobotMap::DigitalIO_CSV = NULL;
CSVReader* RobotMap::Solenoid_CSV = NULL;
CSVReader* RobotMap::PWM_CSV = NULL;
CSVReader* RobotMap::RobotConfig_CSV = NULL;

// Initialize ids to 0. (Take note of this when you are debugging.)
// Speed Controllers
 UINT8 RobotMap::FRONT_RIGHT_DRIVE_ID = 0;
 UINT8 RobotMap::FRONT_LEFT_DRIVE_ID = 0;
 UINT8 RobotMap::REAR_RIGHT_DRIVE_ID = 0;
 UINT8 RobotMap::REAR_LEFT_DRIVE_ID = 0;
 UINT8 RobotMap::ROLLER_MOTOR_ID = 0;
 UINT8 RobotMap::FRONT_SHOOTER_WHEEL_ID = 0;
 UINT8 RobotMap::BACK_SHOOTER_WHEEL_ID = 0;

// Solenoids
 UINT8 RobotMap::HOPPER_LOAD_PISTON_ID = 0;
 UINT8 RobotMap::SHOOTER_FIRE_PISTON_ID = 0;
 UINT8 RobotMap::TILT_PISTON_IN_ID = 0;
 UINT8 RobotMap::TILT_PISTON_OUT_ID = 0;
 UINT8 RobotMap::HANG_PISTON_A_IN_ID = 0;
 UINT8 RobotMap::HANG_PISTON_A_OUT_ID = 0;
 UINT8 RobotMap::HANG_PISTON_B_IN_ID = 0;
 UINT8 RobotMap::HANG_PISTON_B_OUT_ID = 0;
//
//// Digital Inputs
 UINT8 RobotMap::LOAD_BEAM_SENSOR_ID = 0;
 UINT8 RobotMap::FIRE_BEAM_SENSOR_ID = 0;
 UINT8 RobotMap::ROLLER_BEAM_SENSOR_ID = 0;
	
// Analog Inputs
 UINT8 RobotMap::TURN_GYRO_ID = 0;
	
// PWMs

// RobotConfig
double RobotMap::PISTON_DELAY_TIME = 0.0;
double RobotMap::SHOOTER_SPEED = 0.0;
double RobotMap::SHOOTER_POWER = 0.0;
double RobotMap::ROLLER_POWER = 0.0;
double RobotMap::DRIVE_DISTANCE_TO_GOAL = 0.0;
double RobotMap::DRIVE_DISTANCE_TO_HALFCOURT = 0.0;

 
// SmartDashboard Keys
 std::string RobotMap::FOUND_KEY = ""; 
 std::string RobotMap::AZIMUTH_KEY = ""; 
 std::string RobotMap::RANGE_KEY = ""; 
 std::string RobotMap::SHOOTER_TILTED_KEY = "";
 

void RobotMap::init()
{
	printf("Loading data from CSV files...\n");
	
	// Init CSVReaders
	AnalogInputs_CSV = new CSVReader("AnalogInputs.csv");
	CAN_IDS_CSV = new CSVReader("CAN_IDs.csv");
	DigitalIO_CSV = new CSVReader("DigitalIO.csv");
	Solenoid_CSV = new CSVReader("Solenoid.csv");
	PWM_CSV = new CSVReader("PWM.csv");
	RobotConfig_CSV = new CSVReader("RobotConfig.csv");
	
	// Init RobotMap ids
	// Speed Controllers
	FRONT_RIGHT_DRIVE_ID = (UINT8)CAN_IDS_CSV->GetValue("FR_CAN_ID");
	FRONT_LEFT_DRIVE_ID = (UINT8)CAN_IDS_CSV->GetValue("FL_CAN_ID");
	REAR_RIGHT_DRIVE_ID = (UINT8)CAN_IDS_CSV->GetValue("RR_CAN_ID");
	REAR_LEFT_DRIVE_ID = (UINT8)CAN_IDS_CSV->GetValue("RL_CAN_ID");
	ROLLER_MOTOR_ID = (UINT8)CAN_IDS_CSV->GetValue("ROLLER_MOTOR_CAN_ID");
	FRONT_SHOOTER_WHEEL_ID = (UINT8)CAN_IDS_CSV->GetValue("FEED_CAN_ID");
	BACK_SHOOTER_WHEEL_ID = (UINT8)CAN_IDS_CSV->GetValue("FIRE_CAN_ID");
	
	printf("CAN IDs done loading.\n");
	
	// Solenoids
	HOPPER_LOAD_PISTON_ID = (UINT8)Solenoid_CSV->GetValue("DISC_LOAD_ID");
	SHOOTER_FIRE_PISTON_ID = (UINT8)Solenoid_CSV->GetValue("DISC_FIRE_ID");
	TILT_PISTON_IN_ID = (UINT8)Solenoid_CSV->GetValue("SHOOTER_TILT_IN_ID");
	TILT_PISTON_OUT_ID = (UINT8)Solenoid_CSV->GetValue("SHOOTER_TILT_OUT_ID");
	HANG_PISTON_A_IN_ID = (UINT8)Solenoid_CSV->GetValue("HANG_A_IN_ID");
	HANG_PISTON_A_OUT_ID = (UINT8)Solenoid_CSV->GetValue("HANG_A_OUT_ID");
	HANG_PISTON_B_IN_ID = (UINT8)Solenoid_CSV->GetValue("HANG_B_IN_ID");
	HANG_PISTON_B_OUT_ID = (UINT8)Solenoid_CSV->GetValue("HANG_B_OUT_ID");
	
	printf("Solenoid IDs done loading.\n");
	
	// Digital Inputs
	LOAD_BEAM_SENSOR_ID = (UINT8)DigitalIO_CSV->GetValue("LOAD_BEAM_ID");
	FIRE_BEAM_SENSOR_ID = (UINT8)DigitalIO_CSV->GetValue("FIRE_BEAM_ID");
	ROLLER_BEAM_SENSOR_ID = (UINT8)DigitalIO_CSV->GetValue("ROLLER_BEAM_ID");
	
	printf("Digital Input IDs done loading.\n");
	
	// Analog Inputs
	TURN_GYRO_ID = (UINT8)AnalogInputs_CSV->GetValue("YAW_GYRO_ID");
		
	printf("Analog Input IDs done loading.\n");
	
	// PWMs
	
	printf("PWM IDs done loading.\n");
	
	//RobotConfig
	PISTON_DELAY_TIME = RobotConfig_CSV->GetValue("PISTON_DELAY_TIME");
	SHOOTER_SPEED = RobotConfig_CSV->GetValue("SHOOTER_SPEED");
	SHOOTER_POWER = RobotConfig_CSV->GetValue("SHOTER_POWER");
	ROLLER_POWER = RobotConfig_CSV->GetValue("ROLLER_POWER");
	DRIVE_DISTANCE_TO_GOAL = RobotConfig_CSV->GetValue("DRIVE_DISTANCE_TO_GOAL");
	DRIVE_DISTANCE_TO_HALFCOURT = RobotConfig_CSV->GetValue("DRIVE_DISTANCE_TO_HALFCOURT");
		 
	printf("RobotConfig preferences done loading.\n");
	
	// SmartDashboard Keys
	FOUND_KEY = "found";
	AZIMUTH_KEY = "azimuth";
	RANGE_KEY = "range";
	SHOOTER_TILTED_KEY = "shooter tilted";
	
	printf("CSV data loading finished.\n");
}














