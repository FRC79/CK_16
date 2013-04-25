#ifndef FRONTPYRSHOOT_H
#define FRONTPYRSHOOT_H

#include "../../CommandBase.h"

/* This command handles the autonomous mode for shooting
 * on either front corner of the pyramid into the 3 point
 * goal with 2 discs. */

class FrontPyrShoot : public CommandBase 
{
public:
	FrontPyrShoot();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	bool is_finished;
	float shooter_power;
};

#endif
