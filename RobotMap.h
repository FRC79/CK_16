#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "CSV/CSVReader.h"
#include "CANJaguar.h"
#include "RobotDrive.h"
#include "DoubleSolenoid.h"
#include "Solenoid.h"
#include "DigitalInput.h"
#include "Relay.h"
#include "Gyro.h"

/*
 * This file contains all of the software mappings for
 * the robot hardware along with some constants and
 * configuration. This class handles all of the loading
 * from CSV files.
 */

// Compiler Definitions
#define PI 3.1415
#define TICS_PER_REV 250
#define WHEEL_CIRCUMFERENCE (6.0 * PI)
#define INCHES_PER_TIC (-WHEEL_CIRCUMFERENCE)

class RobotMap
{	
public:
	// Speed Controllers
	static CANJaguar *rollerMotor;
	static CANJaguar *shooterFrontWheel, *shooterBackWheel;
	static CANJaguar *frontLeftWheel, *frontRightWheel, 
		*rearLeftWheel, *rearRightWheel;
	
	// RobotDrive
	static RobotDrive *robotDrive;
	
	// Solenoids
	static DoubleSolenoid *hangPistonA, *hangPistonB;
	static DoubleSolenoid *tiltPiston;
	static Solenoid *firePiston;
	static Solenoid *loadPiston;

	// Digital Inputs
	static DigitalInput *pressureSwitch;
	static DigitalInput *rollerBeam, *loadBeam, *fireBeam;
	
	// Relays
	static Relay *compressor;
		
	// Analog Inputs
	static Gyro *turnGyro;
		
	// PWMs
	
	// RobotConfig
	static double PISTON_DELAY;
	static double FIRE_PISTON_DELAY;
	static double LOAD_PISTON_DELAY;
	static double SHOOTER_SPEED;
	static double SHOOTER_POWER;
	static double ROLLER_POWER;
	static double DRIVE_DISTANCE_TO_GOAL;
	static double DRIVE_DISTANCE_TO_HALFCOURT;
	static double ROLLER_TO_PUNCH_ZONE_DELAY;
	static double AUTOLOAD_RESUME_DELAY;
		
	// SmartDashboard Keys
	static std::string FOUND_KEY; 
	static std::string AZIMUTH_KEY; 
	static std::string RANGE_KEY; 
	static std::string SHOOTER_TILTED_KEY;
	
	static void init();
	
	static void loadValues(bool initCSVs);
	
	static void initCSVReaders();
	
private:
	static CSVReader *PWM_CSV, *AnalogInputs_CSV, 
		*DigitalIO_CSV, *Solenoid_CSV, *CAN_IDS_CSV, *RobotConfig_CSV;
};

#endif
