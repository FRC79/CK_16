#ifndef SPINSHOOTERWHEELS_H
#define SPINSHOOTERWHEELS_H

#include "../CommandBase.h"
#include "../RobotMap.h"

/* Description */

class SpinShooterWheels : public CommandBase 
{
public:
	SpinShooterWheels();
	SpinShooterWheels(bool runContinuously);
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
