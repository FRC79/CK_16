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
OI* CommandBase::oi = NULL;

// Initialize DriverStation variables
DriverStation* CommandBase::ds = NULL;
DriverStationLCD* CommandBase::ds_lcd = NULL;
UINT32 CommandBase::priorPacketNumber = 0;
UINT8 CommandBase::dsPacketsReceivedInCurrentSecond = 0;

// Initialize periodic loop variables
UINT32 CommandBase::autoPeriodicLoops = 0;
UINT32 CommandBase::disabledPeriodicLoops = 0;
UINT32 CommandBase::telePeriodicLoops = 0;
UINT32 CommandBase::testPeriodicLoops = 0;

void CommandBase::init() {
    // Init single static instance of all of our subsystems.
	shooter = new DiscShooter();
	drive = new Drivetrain();
	hanger = new Hanger();
	hopper = new Hopper();
	oi = new OI();
	
	// Init static instances of our Driverstation variables.
	ds = DriverStation::GetInstance();
	ds_lcd = DriverStationLCD::GetInstance();
	
//	ds_lcd->PrintfLine(DriverStationLCD::kUser_Line1, "Gyro Done Initializing");
//	ds_lcd->UpdateLCD();
}
