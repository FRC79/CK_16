#ifndef LOADDISC_H
#define LOADDISC_H

#include "../CommandBase.h"
#include "../RobotState.h"

/* Description */

class LoadDisc : public CommandBase 
{
public:
	LoadDisc();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool is_finished;
};

#endif
