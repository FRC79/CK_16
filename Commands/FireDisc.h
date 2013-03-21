#ifndef FIREDISC_H
#define FIREDISC_H

#include "../CommandBase.h"

/* This command handles firing the disc by extending
 * the fire piston for a certain period of time and
 * then retracting it after the disc has been shoot by
 * the spinning shooter wheels. Note that this command
 * does not take care of spinning up the shooter wheels. */

class FireDisc : public CommandBase 
{
public:
	FireDisc();
	FireDisc(double start_delay);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	bool is_finished;
	double startDelay;
};

#endif
