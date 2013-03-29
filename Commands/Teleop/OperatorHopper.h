#ifndef OPERATORHOPPER_H
#define OPERATORHOPPER_H

#include "../../CommandBase.h"
#include "../../Hopper/AutoLoad.h"

/* Description */

class OperatorHopper : public CommandBase 
{
public:
	OperatorHopper();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	Command *autoLoad;
	bool auto_loading;
};

#endif
