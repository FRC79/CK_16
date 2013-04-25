#ifndef STOPSHOOTERWHEELS_H
#define STOPSHOOTERWHEELS_H

#include "../CommandBase.h"

/* This command stops the shooter wheels from spinning. */

class StopShooterWheels : public CommandBase 
{
public:
	StopShooterWheels();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	bool is_finished;
};

#endif
