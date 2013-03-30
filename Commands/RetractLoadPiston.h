#ifndef RETRACTLOADPISTON_H
#define RETRACTLOADPISTON_H

#include "../CommandBase.h"

/* Description */

class RetractLoadPiston : public CommandBase 
{
public:
	RetractLoadPiston();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	bool is_finished;
};

#endif
