#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include "Commands/Command.h"
#include "DriverStation.h"
#include "DriverStationLCD.h"

#include "Subsystems/DiscShooter.h"
#include "Subsystems/Drivetrain.h"
#include "Subsystems/Hopper.h"
#include "Subsystems/Hanger.h"
#include "Subsystems/Tilt.h"
#include "OI.h"

/**
 * The base for all commands. All [atomic] commands should subclass CommandBase.
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
	
	//SHOOTER TILTED UP TO SMARTDASHBOARD
	
	// Static DriverStation objects and variables
	static DriverStation *ds; // driver station object
	static DriverStationLCD *ds_lcd;
	static UINT32 priorPacketNumber; // keep track of the most recent packet number from the DS
	static UINT8 dsPacketsReceivedInCurrentSecond; // keep track of the ds packets received in the current second
	
	// Variables to count the number of periodic loops performed
	static UINT32 autoPeriodicLoops;
	static UINT32 disabledPeriodicLoops;
	static UINT32 telePeriodicLoops;
	static UINT32 testPeriodicLoops;
};

#endif
