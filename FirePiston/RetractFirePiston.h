#ifndef RETRACTFIREPISTON_H
#define RETRACTFIREPISTON_H

#include "../CommandBase.h"

/* Description */

class RetractFirePiston : public Command 
{
public:
	RetractFirePiston();
	RetractFirePiston(bool runContinuously);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool isFinished;
	bool runsForever;
};

#endif
