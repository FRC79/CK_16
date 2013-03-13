#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/AlignWithGoal.h"
#include "RobotMap.h"
#include "CommandBase.h"

class CK16_Main : public IterativeRobot {
private:
	Command *autonomousCommand, *teleopCommand;
	LiveWindow *lw;
	
	virtual void RobotInit() {
		RobotMap::init(); // Load CSV values into RobotMap
		CommandBase::init();
//		autonomousCommand = new ExampleCommand();
//		lw = LiveWindow::GetInstance();
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
	}
	
	virtual void TeleopPeriodic() {
//		Scheduler::GetInstance()->Run();
	}
	
	virtual void TestPeriodic() {
//		lw->Run();
	}
};

START_ROBOT_CLASS(CK16_Main);

