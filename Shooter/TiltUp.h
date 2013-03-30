#ifndef TILTUP_H
#define TILTUP_H

#include "../CommandBase.h"
#include "../RobotState.h"

/* Description */

class TiltUp : public CommandBase 
{
public:
	TiltUp();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	bool is_finished;
};

#endif
