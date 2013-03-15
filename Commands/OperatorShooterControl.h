#ifndef OPERATORSHOOTERCONTROL_H
#define OPERATORSHOOTERCONTROL_H

#include "../CommandBase.h"

class OperatorShooterControl : public CommandBase
{
public:
	OperatorShooterControl();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	static float shooter_power;
	bool wheels_spinning;
};

#endif
