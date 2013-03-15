#include "WPILib.h"
#include "Commands/Command.h"

#include "Commands/OperatorArcadeDrive.h"
#include "Commands/OperatorShooterControl.h"
#include "Commands/OperatorToggleTilt.h"
#include "Commands/OperatorToggleHanger.h"

#include "RobotMap.h"
#include "CommandBase.h"

class CK16_Main : public IterativeRobot {
private:
	Command *autonomousCommand, *operatorArcadeDriving, *operatorToggleHanger,
		*operatorToggleTilt, *operatorShooterControl;
	LiveWindow *lw;
	
	virtual void RobotInit() {
		RobotMap::init(); // Load CSV values into RobotMap
		CommandBase::init(); // Init subsystems and values in CommandBase
		
		// Init Commands
		operatorArcadeDriving = new OperatorArcadeDrive();
		operatorToggleHanger = new OperatorToggleHanger();
		operatorToggleTilt = new OperatorToggleTilt();
		operatorShooterControl = new OperatorShooterControl();
//		autonomousCommand = new ExampleCommand();
//		lw = LiveWindow::GetInstance();
	}
	
	virtual void DisabledInit()
	{
		
	}
	
	virtual void AutonomousInit() {
//		autonomousCommand->Start();
	}
	
	virtual void AutonomousPeriodic() {
//		Scheduler::GetInstance()->Run();
	}
	
	virtual void TeleopInit() {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
//		autonomousCommand->Cancel();
		Scheduler::GetInstance()->AddCommand(operatorArcadeDriving);
		Scheduler::GetInstance()->AddCommand(operatorShooterControl);
		Scheduler::GetInstance()->AddCommand(operatorToggleTilt);
		Scheduler::GetInstance()->AddCommand(operatorToggleHanger);
	}
	
	virtual void TeleopPeriodic() 
	{
		// Update ButtonHelpers
		CommandBase::oi->GetButtonHelper1()->Update();
		CommandBase::oi->GetButtonHelper2()->Update();
		
		Scheduler::GetInstance()->Run(); // Periodically run the Scheduler
		
	}
	
	virtual void TestPeriodic() {
//		lw->Run();
	}
};

START_ROBOT_CLASS(CK16_Main);

