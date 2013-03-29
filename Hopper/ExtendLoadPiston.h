#ifndef EXTENDLOADPISTON_H
#define EXTENDLOADPISTON_H

#include "../CommandBase.h"

/* Description */

class ExtendLoadPiston : public CommandBase 
{
public:
	ExtendLoadPiston();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	bool is_finished;
};

#endif
