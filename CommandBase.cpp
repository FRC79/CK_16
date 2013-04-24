#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) 
{
	
}

CommandBase::CommandBase() : Command() 
{
	
}

void CommandBase::init() {
    // Init single static instance of all of our subsystems.
	shooterPistons = new ShooterPistons();
	shooterWheels = new ShooterWheels();
	hanger = new Hanger();
	hopper = new Hopper();
	oi = new OI();
	
	// Init static instances of our Driverstation variables.
	ds = DriverStation::GetInstance();
	ds_lcd = DriverStationLCD::GetInstance();
	
//	ds_lcd->PrintfLine(DriverStationLCD::kUser_Line1, "Gyro Done Initializing");
//	ds_lcd->UpdateLCD();
}
