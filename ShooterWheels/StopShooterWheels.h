#ifndef STOPSHOOTERWHEELS_H
#define STOPSHOOTERWHEELS_H

#include "Commands/Command.h"

/* Description */

class StopShooterWheels : public Command 
{
public:
	StopShooterWheels();
	StopShooterWheels(bool runContinuously);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool isFinished;
	bool runsForever;
};

#endif
