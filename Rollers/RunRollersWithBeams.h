#ifndef RUNROLLERSWITHBEAMS_H
#define RUNROLLERSWITHBEAMS_H

#include "../CommandBase.h"
#include "../RobotMap.h"

/* Description */

class RunRollersWithBeams : public CommandBase 
{
public:
	RunRollersWithBeams();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif