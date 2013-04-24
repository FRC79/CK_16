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
