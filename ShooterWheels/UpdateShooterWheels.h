#ifndef UPDATESHOOTERWHEELS_H
#define UPDATESHOOTERWHEELS_H

#include "../CommandBase.h"

/* Description */

class UpdateShooterWheels : public CommandBase 
{
public:
	UpdateShooterWheels();
	UpdateShooterWheels(bool runContinuously);
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
