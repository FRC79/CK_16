#ifndef TELEOPHELPER_H
#define TELEOPHELPER_H

/*
 * This class contains functions to help with calculations
 * and references pertaining to the teleop period. This
 * class should be accessed statically.
 */

class TeleopHelper
{
public:
	static double mapJoystickToSpeedOutput(double input);
};

#endif
