#ifndef BACKPYRSHOOT_H
#define BACKPYRSHOOT_H

#include "../../CommandBase.h"

/* Description */

class BackPyrShoot : public CommandBase 
{
public:
	BackPyrShoot();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	bool is_finished;
	float shooter_power;
	float roller_power;
};

#endif
