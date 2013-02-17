#ifndef DISCAUTOLOADER_H
#define DISCAUTOLOADER_H

#include "CANJaguar.h"
#include "DigitalInput.h"
#include "DualSolenoid.h"
#include "Task.h"

/*
 * This class handles the autoloading features of
 * the disc loader. An autoload should consist of
 * a roller mechanism to pull discs in, sensors
 * to detect where discs are located in the mechanism,
 * and a piston to load discs from the top layer to the
 * bottom shooting layer. The system can at any time be
 * manually overriden by a driver, and the system that
 * implements this class will be able to call a function
 * to determine if the system is ready to shoot.
 */

class DiscAutoLoader
{
public:
	/* 
	 * The roller pulls discs in. The load piston pushes discs
	 * in the farthest back position on the top layer to the 
	 * bottom layer. The front sensor is the frontmost sensor
	 * on the top layer to sense if more discs need to be pulled
	 * in. The top sensor determines if a disc is in the backmost
	 * position in the top layer to be loaded by the load piston.
	 * The bottom sensor is the only sensor on the bottom layer
	 * that detects to see if a disc is in shooting position.
	 */
	DiscAutoLoader(CANJaguar *roller, DualSolenoid *load_piston, 
			DigitalInput *top_disc_sensor, DigitalInput *bottom_disc_sensor);
	~DiscAutoLoader();
	
	/* Reset after a disable */
	void Reset();
	
	/* Disable */
	void Disable();
	
	/* Returns current enabled state */
	bool IsEnabled();
	
	bool IsDiscInPosition();
	bool IsDiscLoaded();
	bool IsDiscReadyToShoot();
	
	/* Handles the processes of automatic disc loading 
	 * (should be called continuously in a loop) */
	void AutoLoad();
	
private:
	static const unsigned int BROKEN = 0;
	static const unsigned int SOLID = 1;
	bool ready_to_shoot;
	bool disc_in_position;
	bool disc_loaded;
	bool enabled;
	CANJaguar *m_roller;
	DualSolenoid *m_load_piston;
	DigitalInput *m_top_disc_sensor;
	DigitalInput *m_bottom_disc_sensor;
	Task *m_task
	
	void ResetVariables();
};

#endif
