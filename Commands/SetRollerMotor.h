#ifndef SETROLLERMOTOR_H
#define SETROLLERMOTOR_H

#include "../CommandBase.h"

/* Description */

class SetRollerMotor : public CommandBase 
{
public:
	SetRollerMotor(float power);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	bool is_finished;
	float roller_power;
};

#endif
