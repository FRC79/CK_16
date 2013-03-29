#include "WPILib.h"
#include "Commands/Command.h"
#include "SmartDashboard/SmartDashboard.h"
#include "SmartDashboard/SendableChooser.h"

#include "Commands/Auto/DriveToFrontAndShoot.h"
#include "Commands/Auto/FrontPyrShoot.h"
#include "Commands/Auto/BackPyrShoot.h"
#include "Commands/Teleop/OperatorControl.h"
#include "Commands/FillAirTanks.h"

#include "RobotMap.h"
#include "CommandBase.h"

class CK16_Main : public IterativeRobot {
private:
	Command *autonCommand, *teleopCommand, *compressorCommand;
	SendableChooser *autonChooser;
	LiveWindow *lw;
	
	virtual void RobotInit() {
		RobotMap::init(); // Load CSV values into RobotMap
		CommandBase::init(); // Init subsystems and values in CommandBase
		
		// Init Chooser to pick autonomous mode
		autonCommand = new FrontPyrShoot();
		autonChooser = new SendableChooser();
		autonChooser->AddObject("Drive to Front Shoot 3 (right)", 
				new DriveToFrontAndShoot(DriveToFrontAndShoot::kRight));
		autonChooser->AddObject("Drive to Front Shoot 3 (left)", 
				new DriveToFrontAndShoot(DriveToFrontAndShoot::kLeft));
		autonChooser->AddObject("From Front Shoot 2", new FrontPyrShoot());
		autonChooser->AddDefault("From Back Shoot 3", new BackPyrShoot());
		SmartDashboard::PutData("Autonomous Mode Chooser", autonChooser);
		
		// Init Commands
		teleopCommand = new OperatorControl();
		compressorCommand = new FillAirTanks();
//		lw = LiveWindow::GetInstance();
		
		printf("RobotInit() completed.\n");
		printf("TEAM 79 FOR THE WIN!\n");
	}
	
	void CancelAllCommands(){
		autonCommand->Cancel();
		teleopCommand->Cancel();
		compressorCommand->Cancel();  // I don't think we need to cancel this.
	}
	
	virtual void DisabledInit(){
		CommandBase::disabledPeriodicLoops = 0; // Reset loop counter for disabled periodic.
		
		CancelAllCommands();	// Cancel all previously running commmands.
		
		// Move the cursor down a few, since we'll move it back up in periodic.
		printf("\x1b[2B");
	}
	
	virtual void DisabledPeriodic(){
		static INT32 printSec = (INT32) GetClock() + 1;
		static const INT32 startSec = (INT32) GetClock();
		
		// increment the number of disabled periodic loops completed
		CommandBase::disabledPeriodicLoops++;

		// while disabled, printout the duration of current disabled mode in seconds
		if (GetClock() > printSec) {
			// Move the cursor back to the previous line and clear it.
			printf("\x1b[1A\x1b[2K");
			printf("Disabled seconds: %d\r\n", printSec - startSec);
			printSec++;
		}
	}
	
	virtual void AutonomousInit() {
		CancelAllCommands();	// Cancel all previously running commmands.
		compressorCommand->Start();
		autonCommand = (Command*)autonChooser->GetSelected(); // Dynamically load chosen auton
		autonCommand->Start();
		
		printf("Auton Init Completed\n");
	}
	
	virtual void AutonomousPeriodic() {
		Scheduler::GetInstance()->Run(); // Periodically runs auton command group
	}
	
	virtual void TeleopInit() {
		CancelAllCommands();	// Cancel all previously running commmands.
		compressorCommand->Start();
		teleopCommand->Start();
		
		printf("Teleop Init Completed\n");
	}
	
	virtual void TeleopPeriodic() 
	{
		// Update ButtonHelpers
		CommandBase::oi->GetButtonHelper1()->Update();
		CommandBase::oi->GetButtonHelper2()->Update();
		
		Scheduler::GetInstance()->Run(); // Periodically runs teleop command group
	}
	
	virtual void TestInit(){
		CancelAllCommands();	// Cancel all previously running commmands.
		
		printf("Test Init Completed\n");
	}
	
	virtual void TestPeriodic() {
//		lw->Run();
	}
};

START_ROBOT_CLASS(CK16_Main);

