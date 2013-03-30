#ifndef REVERSEROLLERS_H
#define REVERSEROLLERS_H

#include "../CommandBase.h"

/* Description */

class ReverseRollers : public CommandBase 
{
public:
	ReverseRollers(float power);
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
