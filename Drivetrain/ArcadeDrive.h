#ifndef ARCADEDRIVE_H
#define ARCADEDRIVE_H

#include "../CommandBase.h"
#include "../Util/TeleopHelper.h"

/* The teleop control of the drivetrain using a joystick to
 * control rotation and power output using one vertical axis 
 * and one horizontal axis. */

class ArcadeDrive : public CommandBase 
{
public:
	ArcadeDrive();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool isFinished;
};

#endif
