#ifndef SETFRONTANDBACKWHEELMOTORS_H
#define SETFRONTANDBACKWHEELMOTORS_H

#include "../CommandBase.h"

/* Description */

class SetFrontAndBackWheelMotors : public CommandBase 
{
public:
	SetFrontAndBackWheelMotors(float front_power, float back_power);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool is_finished;
	float m_front_power, m_back_power;
};

#endif
