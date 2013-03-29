#ifndef SETLEFTANDRIGHTMOTOROUTPUTS_H
#define SETLEFTANDRIGHTMOTOROUTPUTS_H

#include "../CommandBase.h"

/* Description */

class SetLeftAndRightMotorOutputs : public CommandBase 
{
public:
	SetLeftAndRightMotorOutputs(float left_power, float right_power);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool is_finished;
	float m_left_power, m_right_power;
};

#endif
