#ifndef STOPSHOOTERWHEELS_H
#define STOPSHOOTERWHEELS_H

#include "../CommandBase.h"

/* Description */

class StopShooterWheels : public CommandBase 
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
