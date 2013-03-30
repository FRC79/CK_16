#ifndef FORWARDROLLERS_H
#define FORWARDROLLERS_H

#include "../CommandBase.h"

/* Description */

class ForwardRollers : public CommandBase 
{
public:
	ForwardRollers(float power);
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
