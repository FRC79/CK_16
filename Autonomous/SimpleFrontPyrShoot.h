#ifndef SIMPLEFRONTPYRSHOOT_H
#define SIMPLEFRONTPYRSHOOT_H

#include "../CommandBase.h"

/* Description */

class SimpleFrontPyrShoot : public CommandBase 
{
public:
	SimpleFrontPyrShoot();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool isFinished;
};

#endif
