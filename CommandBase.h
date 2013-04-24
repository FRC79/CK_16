#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include "Commands/Command.h"
#include "DriverStation.h"
#include "DriverStationLCD.h"

#include "ShooterWheels/ShooterWheels.h"
#include "ShooterPistons/ShooterPistons.h"
#include "Drivetrain/Drivetrain.h"
#include "Hopper/Hopper.h"
#include "Hanger/Hanger.h"
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
	static ShooterWheels *shooterWheels;
	static ShooterPistons *shooterPistons;
	static Drivetrain *drivetrain;
	static Hopper *hopper;
	static Hanger *hanger;
	static OI *oi;
	
	// Static DriverStation objects and variables
	static DriverStation *ds; // driver station object
	static DriverStationLCD *ds_lcd;
	static UINT32 priorPacketNumber; // keep track of the most recent packet number from the DS
	static UINT8 dsPacketsReceivedInCurrentSecond; // keep track of the ds packets received in the current second
	
	// Variables to count the number of periodic loops performed
	static UINT32 disabledPeriodicLoops;
};

#endif
