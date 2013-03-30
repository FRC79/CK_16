#ifndef TILTDOWN_H
#define TILTDOWN_H

#include "../CommandBase.h"
#include "../RobotState.h"

/* Description */

class TiltDown : public CommandBase 
{
public:
	TiltDown();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	bool is_finished;
};

#endif
