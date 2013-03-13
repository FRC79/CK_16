#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) 
{
	
}

CommandBase::CommandBase() : Command() 
{
	
}

// Initialize a single static instance of all of our subsystems to NULL
DiscShooter* CommandBase::shooter = NULL;
Drivetrain* CommandBase::drive = NULL;
Hanger* CommandBase::hanger = NULL;
Hopper* CommandBase::hopper = NULL;
Tilt* CommandBase::tilt = NULL;
OI* CommandBase::oi = NULL;

void CommandBase::init() {
    // Init single static instance of all of our subsystems.
	shooter = new DiscShooter();
	drive = new Drivetrain();
	hanger = new Hanger();
	hopper = new Hopper();
	tilt = new Tilt();
	oi = new OI();
}
