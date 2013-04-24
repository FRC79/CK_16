#ifndef SIMPLEBACKPYRSHOOT_H
#define SIMPLEBACKPYRSHOOT_H

#include "../CommandBase.h"

/* Description */

class SimpleBackPyrShoot : public CommandBase 
{
public:
	SimpleBackPyrShoot();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool isFinished;
};

#endif
