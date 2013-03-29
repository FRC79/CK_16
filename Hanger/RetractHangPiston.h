#ifndef RETRACTHANGPISTON_H
#define RETRACTHANGPISTON_H

#include "../CommandBase.h"

/* Description */

class RetractHangPiston : public CommandBase 
{
public:
	RetractHangPiston();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	bool is_finished;
};

#endif
