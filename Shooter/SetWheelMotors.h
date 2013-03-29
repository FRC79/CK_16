#ifndef SETWHEELMOTORS_H
#define SETWHEELMOTORS_H

#include "../CommandBase.h"

/* Description */

class SetWheelMotors : public CommandBase 
{
public:
	SetWheelMotors(float power);
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
