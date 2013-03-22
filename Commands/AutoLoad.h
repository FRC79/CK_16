#ifndef AUTOLOAD_H
#define AUTOLOAD_H

#include "../CommandBase.h"

/* This command handles continuous automatic disc
 * loading using the hopper to manipulate discs and
 * push them down to the fire chamber. */

class AutoLoad : public CommandBase 
{
public:
	AutoLoad();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	double roller_power;
};

#endif
