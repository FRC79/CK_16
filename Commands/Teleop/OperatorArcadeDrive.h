#ifndef OPERATORARCADEDRIVE_H
#define OPERATORARCADEDRIVE_H

#include "../../CommandBase.h"

/*
 * This command allows for Arcade Driving with the joystick.
 */

class OperatorArcadeDrive : public CommandBase 
{
public:
	OperatorArcadeDrive();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	Joystick *driveJoystick;
};

#endif
