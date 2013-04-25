#ifndef OPERATORTOGGLEHANGER_H
#define OPERATORTOGGLEHANGER_H

#include "Commands/Command.h"
#include "../CommandBase.h"

/*
 * This command is allows for toggling of the hanging
 * hooks to be retracted and extended in the teleop
 * period.
 */

class OperatorToggleHanger : public Command 
{
public:
	OperatorToggleHanger();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
