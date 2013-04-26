#ifndef OPERATORSHOOTERCONTROL_H
#define OPERATORSHOOTERCONTROL_H

#include "Commands/Command.h"
#include "../CommandBase.h"

/*
 * This command allows for the control of the shooter
 * during teleop mode. The user can control the fire piston
 * and the shooter wheels.
 */

class OperatorShooterControl : public Command
{
public:
	OperatorShooterControl();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	float shooter_power;
	bool wheels_spinning;
	bool wasPressed;
};

#endif
