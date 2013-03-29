#ifndef SETMOTOROUTPUTS_H
#define SETMOTOROUTPUTS_H

#include "../CommandBase.h"

/* Description */

class SetMotorOutputs : public CommandBase 
{
public:
	SetMotorOutputs(float power);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool is_finished;
	float m_power;
};

#endif
