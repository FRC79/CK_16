#include "RobotMap.h"

// Initialize a single  instance of all of our CSVReaders to NULL
CSVReader* RobotMap::AnalogInputs_CSV = NULL;
CSVReader* RobotMap::CAN_IDS_CSV = NULL;
CSVReader* RobotMap::DigitalIO_CSV = NULL;
CSVReader* RobotMap::Solenoid_CSV = NULL;
CSVReader* RobotMap::PWM_CSV = NULL;
CSVReader* RobotMap::RobotConfig_CSV = NULL;

// Speed Controllers
CANJaguar* RobotMap::frontLeftWheel = NULL;
CANJaguar* RobotMap::frontRightWheel = NULL;
CANJaguar* RobotMap::rearLeftWheel = NULL;
CANJaguar* RobotMap::rearRightWheel = NULL;
CANJaguar* RobotMap::shooterFrontWheel = NULL;
CANJaguar* RobotMap::shooterBackWheel = NULL;
CANJaguar* RobotMap::rollerMotor = NULL;

// Robotdrive
RobotDrive* RobotMap::robotDrive = NULL;

// Solenoids
DoubleSolenoid* RobotMap::hangPistonA = NULL;
DoubleSolenoid* RobotMap::hangPistonB = NULL;
DoubleSolenoid* RobotMap::tiltPiston = NULL;
Solenoid* RobotMap::firePiston = NULL;
Solenoid* RobotMap::loadPiston = NULL;

// Digital Inputs
DigitalInput* RobotMap::pressureSwitch = NULL;
DigitalInput* RobotMap::rollerBeam = NULL;
DigitalInput* RobotMap::loadBeam = NULL;
DigitalInput* RobotMap::fireBeam = NULL;

// Relays
Relay* RobotMap::compressor = NULL;

// Analog Inputs
Gyro* RobotMap::turnGyro = NULL;

// PWMs

// RobotConfig
double RobotMap::PISTON_DELAY = 0.0;
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

void RobotMap::initCSVReaders()
{
	// Init CSVReaders
	AnalogInputs_CSV = new CSVReader("AnalogInputs.csv");
	CAN_IDS_CSV = new CSVReader("CAN_IDs.csv");
	DigitalIO_CSV = new CSVReader("DigitalIO.csv");
	Solenoid_CSV = new CSVReader("Solenoid.csv");
	PWM_CSV = new CSVReader("PWM.csv");
	RobotConfig_CSV = new CSVReader("RobotConfig.csv");
}

void RobotMap::init(){
	loadValues(true);
}

void RobotMap::loadValues(bool initCSVs)
{
	// Initialize CSVs if specified
	if(initCSVs){
		initCSVReaders();
	}
	
	// Speed Controllers
	frontRightWheel = new CANJaguar((UINT8)CAN_IDS_CSV->GetValue("FR_CAN_ID"));
	frontLeftWheel = new CANJaguar((UINT8)CAN_IDS_CSV->GetValue("FL_CAN_ID"));
	rearRightWheel = new CANJaguar((UINT8)CAN_IDS_CSV->GetValue("RR_CAN_ID"));
	rearLeftWheel = new CANJaguar((UINT8)CAN_IDS_CSV->GetValue("RL_CAN_ID"));
	rollerMotor = new CANJaguar((UINT8)CAN_IDS_CSV->GetValue("ROLLER_MOTOR_CAN_ID"));
	shooterFrontWheel = new CANJaguar((UINT8)CAN_IDS_CSV->GetValue("FEED_CAN_ID"));
	shooterBackWheel = new CANJaguar((UINT8)CAN_IDS_CSV->GetValue("FIRE_CAN_ID"));
	
	// RobotDrive
	robotDrive = new RobotDrive(frontLeftWheel, rearLeftWheel, frontRightWheel, rearRightWheel);
	robotDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
	robotDrive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	robotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	robotDrive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	
	// Solenoids
	loadPiston = new Solenoid((UINT8)Solenoid_CSV->GetValue("DISC_LOAD_ID"));
	firePiston = new Solenoid((UINT8)Solenoid_CSV->GetValue("DISC_FIRE_ID"));
	tiltPiston = new DoubleSolenoid((UINT8)Solenoid_CSV->GetValue("SHOOTER_TILT_IN_ID"), 
			(UINT8)Solenoid_CSV->GetValue("SHOOTER_TILT_OUT_ID"));
	hangPistonA = new DoubleSolenoid((UINT8)Solenoid_CSV->GetValue("HANG_A_IN_ID"),
			(UINT8)Solenoid_CSV->GetValue("HANG_A_OUT_ID"));
	hangPistonB = new DoubleSolenoid((UINT8)Solenoid_CSV->GetValue("HANG_B_IN_ID"),
			(UINT8)Solenoid_CSV->GetValue("HANG_B_OUT_ID"));
	
	// Digital Inputs
	loadBeam = new DigitalInput((UINT8)DigitalIO_CSV->GetValue("LOAD_BEAM_ID"));
	fireBeam = new DigitalInput((UINT8)DigitalIO_CSV->GetValue("FIRE_BEAM_ID"));
	rollerBeam = new DigitalInput((UINT8)DigitalIO_CSV->GetValue("ROLLER_BEAM_ID"));
	pressureSwitch = new DigitalInput(1);
	
	// Relays
	compressor = new Relay(1);
	
	// Analog Inputs
	turnGyro = new Gyro((UINT8)AnalogInputs_CSV->GetValue("YAW_GYRO_ID"));
		
	// PWMs
	
	//RobotConfig
	PISTON_DELAY = RobotConfig_CSV->GetValue("PISTON_DELAY_TIME");
	SHOOTER_SPEED = RobotConfig_CSV->GetValue("SHOOTER_SPEED");
	SHOOTER_POWER = RobotConfig_CSV->GetValue("SHOOTER_POWER");
	ROLLER_POWER = RobotConfig_CSV->GetValue("ROLLER_POWER");
	DRIVE_DISTANCE_TO_GOAL = RobotConfig_CSV->GetValue("DRIVE_DISTANCE_TO_GOAL");
	DRIVE_DISTANCE_TO_HALFCOURT = RobotConfig_CSV->GetValue("DRIVE_DISTANCE_TO_HALFCOURT");
		 
	// SmartDashboard Keys
	FOUND_KEY = "found";
	AZIMUTH_KEY = "azimuth";
	RANGE_KEY = "range";
	SHOOTER_TILTED_KEY = "shooter tilted";
}














