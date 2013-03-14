#ifndef OPERATORTOGGLETILT_H
#define OPERATORTOGGLETILT_H

#include "../CommandBase.h"

/*
 * This command allows for toggling of the tilt piston
 * in the teleop period in order to lower and raise (tilt) 
 * the manipulator.
 */

class OperatorToggleTilt : public CommandBase 
{
public:
	OperatorToggleTilt();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
