#include "WPILib.h"
#include "Commands/Command.h"
#include "SmartDashboard/SmartDashboard.h"
#include "SmartDashboard/SendableChooser.h"

#include "Hopper/AutoLoad.h"
#include "Drivetrain/ArcadeDrive.h"
#include "Compressor/RunCompressor.h"
#include "TiltPiston/InvertTiltState.h"
#include "ShooterWheels/SpinShooterWheels.h"
#include "Misc/WaitCommand.h"
#include "Misc/DoNothing.h"
#include "Misc/CancelCommand.h"
#include "Hanger/InvertHangerState.h"
#include "FirePiston/ExtendFirePiston.h"
#include "Rollers/RollDiscIn.h"
#include "Rollers/RollDiscOut.h"
#include "LoadPiston/ExtendLoadPiston.h"
#include "LoadPiston/RetractLoadPiston.h"
#include "Commands/Subsystem.h"
#include "Drivetrain/ArcadeDrive.h"
#include "Autonomous/SimpleFrontPyrShoot.h"
#include "Autonomous/SimpleBackPyrShoot.h"
#include "Hanger/OperatorToggleHanger.h"

#include "RobotMap.h"
#include "CommandBase.h"

class CK16_Main : public IterativeRobot {
private:
	Command *compressorCommand, *autoLoadCommand, *tiltCommand, *shooterWheelsCommand,
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
//		autoLoadCommand = new AutoLoad();
		tiltCommand = new InvertTiltState();
//		shooterWheelsCommand = new SpinShooterWheels(true);
		arcadeDriveCommand = new ArcadeDrive();
		
		CommandBase::oi->buttonInvertTiltJoy1->WhenPressed(!tiltCommand->IsRunning() ? tiltCommand : new DoNothing());
        CommandBase::oi->buttonInvertTiltJoy2->WhenPressed(!tiltCommand->IsRunning() ? tiltCommand : new DoNothing());
//        CommandBase::oi->buttonInvertHangPiston->WhenPressed(new InvertHangerState());
//        CommandBase::oi->buttonToggleAutoLoad->WhenPressed(!autoLoadCommand->IsRunning() ? 
//                autoLoadCommand : new CancelCommand(autoLoadCommand));
//        CommandBase::oi->buttonExtendFirePiston->WhileHeld(new ExtendFirePiston(true));
//        CommandBase::oi->buttonExtendFirePiston->WhenReleased(new WaitC(RobotMap::AUTOLOAD_RESUME_DELAY, 
//                (Subsystem*)CommandBase::firePiston));
//        CommandBase::oi->buttonForwardRollers->WhileHeld(new RollDiscIn(true));
//        CommandBase::oi->buttonReverseRollers->WhileHeld(new RollDiscOut(true));
//        CommandBase::oi->buttonManualLoadPiston->WhenPressed(new CancelCommand(autoLoadCommand));
//        CommandBase::oi->buttonManualLoadPiston->WhileHeld(new ExtendLoadPiston(true));
//        CommandBase::oi->buttonManualLoadPiston->WhenReleased(new RetractLoadPiston());
//        CommandBase::oi->buttonToggleShooterWheels->WhenPressed(!shooterWheelsCommand->IsRunning() ? 
//                shooterWheelsCommand : new CancelCommand(shooterWheelsCommand));
		
//		lw = LiveWindow::GetInstance();
		
		printf("RobotInit() completed.\n");
		printf("TEAM 79 FOR THE WIN!\n");
		printf("ST. LOUIS\n");
	}
	
	void CancelAllCommands(){
//		autonCommand->Cancel();
//		compressorCommand->Cancel();  // I don't think we need to cancel this.
	}
	
	virtual void DisabledInit(){
		CommandBase::disabledPeriodicLoops = 0; // Reset loop counter for disabled periodic.
		
		
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
		(new OperatorToggleHanger())->Start();
//		autoLoadCommand->Start();
		
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

