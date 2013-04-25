#ifndef SPINSHOOTERWHEELSBB_H
#define SPINSHOOTERWHEELSBB_H

#include "../CommandBase.h"
#include "../Controllers/BangBang_Controller.h"

/* This command handles continuously spinning the shooter
 * wheels at a certain angular velocity using motor encoders
 * as input for a BangBang Controller. */

class SpinShooterWheelsBB : public CommandBase 
{
public:
	SpinShooterWheelsBB(float shooter_rpms);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	BangBang_Controller *frontSpeed, *backSpeed;
	float rpms;
};

#endif
