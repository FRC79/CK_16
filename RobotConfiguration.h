<<<<<<< HEAD
#ifndef Include_RobotConfiguration_H
#define Include_RobotConfiguration_H
class RobotConfiguration
{
public:
	
	static const int PRESSURE_SWITCH_CHANNEL = 1;
	static const int COMPRESSOR_RELAY_CHANNEL = 1;
};

#define TICS_PER_REV 250
#define WHEEL_CIRCUMFERENCE (6.0 * 3.1415)
#define INCHES_PER_TIC (-WHEEL_CIRCUMFERENCE)
#define COMPRESSOR_RELAY_CHANNEL 1 //watman strikes again

#endif

=======
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

>>>>>>> a5389be88d521c0167592e6ad43021f843287c83
