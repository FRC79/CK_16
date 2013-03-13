#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include "Commands/Command.h"


#include "Subsystems/DiscShooter.h"
#include "Subsystems/Drivetrain.h"
#include "Subsystems/Hopper.h"
#include "Subsystems/Hanger.h"
#include "Subsystems/Tilt.h"
#include "OI.h"


/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores, creates, and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.subsystem
 */

class CommandBase: public Command {
public:
	CommandBase(const char *name);
	CommandBase();
	static void init();
	
	// Static instances of our subsystems
	static DiscShooter *shooter;
	static Drivetrain *drive;
	static Hopper *hopper;
	static Hanger *hanger;
	static Tilt *tilt;
	static OI *oi;
};

#endif
