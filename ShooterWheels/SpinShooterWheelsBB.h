#ifndef SPINSHOOTERWHEELSBB_H
#define SPINSHOOTERWHEELSBB_H

#include "../CommandBase.h"

/* Description */

class SpinShooterWheelsBB : public CommandBase 
{
public:
	SpinShooterWheelsBB();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool isFinished;
};

#endif
