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

class RobotMap
{	
	static const int PRESSURE_SWITCH_CHANNEL = 1;
	static const int COMPRESSOR_RELAY_CHANNEL = 1;
	
public:
	// Speed Controllers
	static UINT8 FRONT_RIGHT_DRIVE_ID;
	static UINT8 FRONT_LEFT_DRIVE_ID;
	static UINT8 REAR_RIGHT_DRIVE_ID;
	static UINT8 REAR_LEFT_DRIVE_ID;
	static UINT8 ROLLER_MOTOR_ID;
	static UINT8 FRONT_SHOOTER_WHEEL_ID;
	static UINT8 BACK_SHOOTER_WHEEL_ID;
	
	// Solenoids
//	static UINT8 HOPPER_LOAD_PISTON_ID;
//	static UINT8 SHOOTER_FIRE_PISTON_ID;
//	static UINT8 TILT_PISTON_IN_ID;
//	static UINT8 TILT_PISTON_OUT_ID;
//	static UINT8 HANG_PISTON_A_IN_ID;
//	static UINT8 HANG_PISTON_A_OUT_ID;
//	static UINT8 HANG_PISTON_B_IN_ID;
//	static UINT8 HANG_PISTON_B_OUT_ID;
//
//	// Digital Inputs
//	static UINT8 LOAD_BEAM_SENSOR_ID;
//	static UINT8 FIRE_BEAM_SENSOR_ID;
//	static UINT8 CHECKER_BEAM_SENSOR_ID;
		
	// Analog Inputs
		
	// PWMs
	
	static void init();
	
private:
	static CSVReader *PWM_CSV, *AnalogInputs_CSV, 
		*DigitalIO_CSV, *Solenoid_CSV, *CAN_IDS_CSV;
};

#endif
