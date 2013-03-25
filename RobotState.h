#ifndef ROBOTSTATE_H
#define ROBOTSTATE_H

/* This class holds all of the static state variables
 * that can be used among commands and different parts
 * of the robot to interact with other parts indirectly.
 */

class RobotState
{
public:
	// Shooting States
	static bool shooter_wheels_spinning;
	static bool auto_load_piston_locked;
	static bool auto_loading;
	
	// Vision Tracking Variables
	static bool target_found;
	static double azimuth;
	static double range;
};

#endif
