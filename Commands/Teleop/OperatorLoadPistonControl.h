#ifndef OPERATORLOADPISTONCONTROL_H
#define OPERATORLOADPISTONCONTROL_H

#include "../../CommandBase.h"

/* 
 * This class allows for hopper conrol during teleop
 * including the use of the roller motor, the load piston,
 * and the beam sensors to let us know if our LoadPiston is full.
 */

class OperatorLoadPistonControl : public CommandBase
{
public:
	OperatorLoadPistonControl();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	float roller_power;
};

#endif
