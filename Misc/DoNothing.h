#ifndef DONOTHING_H
#define DONOTHING_H

#include "../CommandBase.h"

/* Description */

class DoNothing : public CommandBase 
{
public:
	DoNothing();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
