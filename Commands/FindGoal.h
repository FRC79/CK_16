#ifndef FINDGOAL_H
#define FINDGOAL_H

#include "../CommandBase.h"

/* This command handles talking to the SmartDashboard to get
 * goal location information from the Vision Processing widget.
 * Specifically, it is looking for if a goal is found, our angular
 * offset relative to the goal, and our distance from the goal. */

class FindGoal : public CommandBase 
{
public:
	FindGoal();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	bool found;
	double azimuth;
	double range;
	bool is_finished;
};

#endif
