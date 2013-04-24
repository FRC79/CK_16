#ifndef PUNCHDISC_H
#define PUNCHDISC_H

#include "../CommandBase.h"

/* Description */

class PunchDisc : public CommandBase 
{
public:
	PunchDisc();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool isFinished;
};

#endif
