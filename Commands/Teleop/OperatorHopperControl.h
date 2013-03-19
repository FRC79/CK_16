#ifndef OPERATORHOPPERCONTROL_H
#define OPERATORHOPPERCONTROL_H

#include "../../CommandBase.h"

/* 
 * This class allows for hopper conrol during teleop
 * including the use of the roller motor, the load piston,
 * and the beam sensors to let us know if our hopper is full.
 */

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
	float roller_power;
};

#endif
