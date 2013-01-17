#ifndef Include_RobotConfiguration_H
#define Include_RobotConfiguration_H
class RobotConfiguration
{
public:
	// CAN bus IDs for Jaguars
	static const UINT8 FR_CAN_ID = 6;
	static const UINT8 FL_CAN_ID = 2;
	static const UINT8 RR_CAN_ID = 4;
	static const UINT8 RL_CAN_ID = 3;
	
	// Analog inputs
	static const UINT8 YAW_GYRO = 8; // This is not certain yet
	
	// Measurements
	static const double WHEEL_CIRCUMFERENCE = 5.0 * 3.1415; // Maybe define PI later
};
#endif

