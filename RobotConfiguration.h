#ifndef Include_RobotConfiguration_H
#define Include_RobotConfiguration_H
class RobotConfiguration
{
public:
	
	// Measurements
	static const int PRESSURE_SWITCH_CHANNEL = 1;
	static const int COMPRESSOR_RELAY_CHANNEL = 1;
};

#define TICS_PER_REV 250
#define WHEEL_CIRCUMFERENCE (6.0 * 3.1415)
#define INCHES_PER_TIC (-WHEEL_CIRCUMFERENCE)

#endif

