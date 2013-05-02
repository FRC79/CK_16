#include "WPILib.h"
#include "Commands/Command.h"
#include "SmartDashboard/SmartDashboard.h"
#include "SmartDashboard/SendableChooser.h"

#include "Hopper/AutoLoad.h"
#include "Drivetrain/ArcadeDrive.h"
#include "Compressor/RunCompressor.h"
#include "TiltPiston/InvertTiltState.h"
#include "ShooterWheels/InvertWheelState.h"
#include "ShooterWheels/UpdateShooterWheels.h"
#include "Misc/WaitCommand.h"
#include "Misc/DoNothing.h"
#include "Misc/CancelCommand.h"
#include "Hanger/InvertHangerState.h"
#include "Rollers/RollDiscIn.h"
#include "Rollers/RollDiscOut.h"
#include "LoadPiston/ExtendLoadPiston.h"
#include "LoadPiston/RetractLoadPiston.h"
#include "Commands/Subsystem.h"
#include "Drivetrain/ArcadeDrive.h"
#include "Autonomous/SimpleFrontPyrShoot.h"
#include "Autonomous/SimpleBackPyrShoot.h"
#include "FirePiston/ExtendFirePistonAndWait.h"

#include "RobotMap.h"
#include "CommandBase.h"

class CK16_Main : public IterativeRobot {
private:
	Command *compressorCommand, *autoLoadCommand, *tiltCommand, 
		*updateShooterWheelsCommand, *invertShooterWheelsCommand,
		*arcadeDriveCommand, *autonCommand;
	Command *tilt, *hang;
	SendableChooser *autonChooser;
	LiveWindow *lw;
	
	virtual void RobotInit() {
		RobotMap::init(); // Load CSV values into RobotMap
		CommandBase::init(); // Init subsystems and values in CommandBase
		
		// Init Chooser to pick autonomous mode
		autonCommand = new SimpleBackPyrShoot();
		autonChooser = new SendableChooser();
		autonChooser->AddObject("From Front Shoot 2", new SimpleFrontPyrShoot());
		autonChooser->AddDefault("From Back Shoot 3", new SimpleBackPyrShoot());
		SmartDashboard::PutData("Autonomous Mode Chooser", autonChooser);
		
		// Init Commands
		compressorCommand = new RunCompressor();
		autoLoadCommand = new AutoLoad();
		tiltCommand = new InvertTiltState();
		invertShooterWheelsCommand = new InvertWheelState();
		updateShooterWheelsCommand = new UpdateShooterWheels();
		arcadeDriveCommand = new ArcadeDrive();
		
		CommandBase::oi->buttonStartAutoLoad->WhenPressed(autoLoadCommand);
		
		CommandBase::oi->buttonInvertTiltJoy1->WhenPressed(!tiltCommand->IsRunning() ? tiltCommand : new DoNothing());
        CommandBase::oi->buttonInvertTiltJoy2->WhenPressed(!tiltCommand->IsRunning() ? tiltCommand : new DoNothing());
        
        CommandBase::oi->buttonInvertHangPiston->WhenPressed(new InvertHangerState());
        
        CommandBase::oi->buttonExtendFirePiston->WhileHeld(new ExtendFirePistonAndWait());
        
        CommandBase::oi->buttonForwardRollers->WhileHeld(new RollDiscIn(true));
        CommandBase::oi->buttonReverseRollers->WhileHeld(new RollDiscOut(true));
        CommandBase::oi->buttonManualLoadPiston->WhileHeld(new ExtendLoadPiston(true));
        CommandBase::oi->buttonManualLoadPiston->WhenPressed(new CancelCommand(autoLoadCommand));
        CommandBase::oi->buttonForwardRollers->WhenPressed(new CancelCommand(autoLoadCommand));
        CommandBase::oi->buttonForwardRollers->WhenPressed(new CancelCommand(autoLoadCommand));
        
        CommandBase::oi->buttonToggleShooterWheels->WhenPressed(invertShooterWheelsCommand);
		
//		lw = LiveWindow::GetInstance();
		
		printf("RobotInit() completed.\n");
		printf("TEAM 79 FOR THE WIN!\n");
		printf("ST. LOUIS EXP\n");
	}
	
	void CancelCommands(){
		compressorCommand->Cancel();
		arcadeDriveCommand->Cancel();
		autoLoadCommand->Cancel();
		tiltCommand->Cancel();
		invertShooterWheelsCommand->Cancel();
		updateShooterWheelsCommand->Cancel();
	}
	
	virtual void DisabledInit(){
		CommandBase::disabledPeriodicLoops = 0; // Reset loop counter for disabled periodic.
		
		CancelCommands();
		
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
//		CancelAllCommands();	// Cancel all previously running commmands.
		compressorCommand->Start();
		autonCommand = (Command*)autonChooser->GetSelected(); // Dynamically load chosen auton
		autonCommand->Start();
		
		printf("Auton Init Completed\n");
	}
	
	virtual void AutonomousPeriodic() {
		Scheduler::GetInstance()->Run(); // Periodically runs auton command group
	}
	
	virtual void TeleopInit() {
//		CancelAllCommands();	// Cancel all previously running commmands.
		compressorCommand->Start();
		arcadeDriveCommand->Start();
		updateShooterWheelsCommand->Start();
		
		printf("Teleop Init Completed\n");
	}
	
	virtual void TeleopPeriodic() 
	{
		Scheduler::GetInstance()->Run(); // Periodically runs teleop command group
	}
	
	virtual void TestInit(){
//		CancelAllCommands();	// Cancel all previously running commmands.
		
		printf("Test Init Completed\n");
	}
	
	virtual void TestPeriodic() {
//		lw->Run();
	}
};

START_ROBOT_CLASS(CK16_Main);

