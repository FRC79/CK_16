#ifndef EXTENDHANGPISTON_H
#define EXTENDHANGPISTON_H

#include "../CommandBase.h"

/* Description */

class ExtendHangPiston : public CommandBase 
{
public:
	ExtendHangPiston();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	bool is_finished;
};

#endif
