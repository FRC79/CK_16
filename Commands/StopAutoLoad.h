#ifndef STOPAUTOLOAD_H
#define STOPAUTOLOAD_H

#include "../CommandBase.h"

/* This command handles stopping the auto loader. */

class StopAutoLoad : public CommandBase 
{
public:
	StopAutoLoad();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	bool is_finished;
};

#endif
