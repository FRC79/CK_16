#ifndef RUNROLLERWITHBEAMS_H
#define RUNROLLERWITHBEAMS_H

#include "../CommandBase.h"
#include "../RobotMap.h"

/* Description */

class RunRollerWithBeams : public CommandBase 
{
public:
	RunRollerWithBeams();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool is_finished;
	float roller_power;
};

#endif
