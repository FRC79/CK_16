#ifndef PUNCHDISC_H
#define PUNCHDISC_H

#include "../CommandBase.h"
#include "../RobotMap.h"

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
	bool rolling;
};

#endif
