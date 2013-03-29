#ifndef RETRACTFIREPISTON_H
#define RETRACTFIREPISTON_H

#include "../CommandBase.h"

/* Description */

class RetractFirePiston : public CommandBase 
{
public:
	RetractFirePiston();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool is_finished;
};

#endif
