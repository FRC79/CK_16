#ifndef OPERATORHOPPERCONTROL_H
#define OPERATORHOPPERCONTROL_H

#include "../CommandBase.h"

class OperatorHopperControl : public CommandBase
{
public:
	OperatorHopperControl();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	
};

#endif
