#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) 
{
	
}

CommandBase::CommandBase() : Command() 
{
	
}

ShooterWheels* CommandBase::shooterWheels = NULL;
FirePiston* CommandBase::firePiston = NULL;
Rollers* CommandBase::rollers = NULL;
Drivetrain* CommandBase::drivetrain = NULL;
LoadPiston* CommandBase::loadPiston = NULL;
TiltPiston* CommandBase::tiltPiston = NULL;
Hanger* CommandBase::hanger = NULL;
HopperState* CommandBase::hopperState = NULL;
OI* CommandBase::oi = NULL;

// Static DriverStation objects and variables
DriverStation* CommandBase::ds = NULL;
DriverStationLCD* CommandBase::ds_lcd = NULL;
UINT32 CommandBase::priorPacketNumber = 0;
UINT8 CommandBase::dsPacketsReceivedInCurrentSecond = 0;

// Variables to count the number of periodic loops performed
UINT32 CommandBase::disabledPeriodicLoops = 0;

// Variables to count the number of periodic loops performed
static UINT32 disabledPeriodicLoops;

void CommandBase::init() {
    // Init single static instance of all of our subsystems.
	shooterWheels = new ShooterWheels();
	firePiston = new FirePiston();
	rollers = new Rollers(); 
	drivetrain = new Drivetrain();
	loadPiston = new LoadPiston();
	tiltPiston = new TiltPiston();
	hanger = new Hanger();
	hopperState = new HopperState();
	oi = new OI();
	
	// Init static instances of our Driverstation variables.
	ds = DriverStation::GetInstance();
	ds_lcd = DriverStationLCD::GetInstance();
	
//	ds_lcd->PrintfLine(DriverStationLCD::kUser_Line1, "Gyro Done Initializing");
//	ds_lcd->UpdateLCD();
}
