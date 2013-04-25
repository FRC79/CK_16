#ifndef INVERTHANGERSTATE_H
#define INVERTHANGERSTATE_H

#include "../CommandBase.h"

/* Extends the hanger if it's retracted and retracts it if
 * it's extended. */

class InvertHangerState : public CommandBase 
{
public:
	InvertHangerState();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool isFinished;
};

#endif
