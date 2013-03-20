#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "Data/CSVReader.h"

/*
 * This file contains all of the software mappings for
 * the robot hardware along with some constants and
 * configuration. This class handles all of the loading
 * from CSV files.
 */

// Compiler Definitions
#define PI 3.1415
#define TICS_PER_REV 250
#define TICS_PER_SHOOTER_REV 250
#define WHEEL_CIRCUMFERENCE (6.0 * PI)
#define INCHES_PER_TIC (-WHEEL_CIRCUMFERENCE)
#define TURN_RADIUS 20.0							// THIS IS A DUMMIE VAL. NEEDS TO BE UPDATED.
#define TURN_CIRCUMFERENCE (TURN_RADIUS * 2 * PI)

class RobotMap
{	
public:
	static const int PRESSURE_SWITCH_CHANNEL = 1;
	static const int COMPRESSOR_RELAY_CHANNEL = 1;
	
	// Speed Controllers
	static UINT8 FRONT_RIGHT_DRIVE_ID;
	static UINT8 FRONT_LEFT_DRIVE_ID;
	static UINT8 REAR_RIGHT_DRIVE_ID;
	static UINT8 REAR_LEFT_DRIVE_ID;
	static UINT8 ROLLER_MOTOR_ID;
	static UINT8 FRONT_SHOOTER_WHEEL_ID;
	static UINT8 BACK_SHOOTER_WHEEL_ID;
	
	// Solenoids
	static UINT8 HOPPER_LOAD_PISTON_ID;
	static UINT8 SHOOTER_FIRE_PISTON_ID;
	static UINT8 TILT_PISTON_IN_ID;
	static UINT8 TILT_PISTON_OUT_ID;
	static UINT8 HANG_PISTON_A_IN_ID;
	static UINT8 HANG_PISTON_A_OUT_ID;
	static UINT8 HANG_PISTON_B_IN_ID;
	static UINT8 HANG_PISTON_B_OUT_ID;
//
//	// Digital Inputs
	static UINT8 LOAD_BEAM_SENSOR_ID;
	static UINT8 FIRE_BEAM_SENSOR_ID;
	static UINT8 ROLLER_BEAM_SENSOR_ID;
		
	// Analog Inputs
		
	// PWMs
	
	// SmartDashboard Keys
	static std::string FOUND_KEY; 
	static std::string AZIMUTH_KEY; 
	static std::string RANGE_KEY; 
	static std::string SHOOTER_TILTED_KEY;
	
	static void init();
	
private:
	static CSVReader *PWM_CSV, *AnalogInputs_CSV, 
		*DigitalIO_CSV, *Solenoid_CSV, *CAN_IDS_CSV;
};

#endif
