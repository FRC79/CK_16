#ifndef CANCELCOMMAND_H
#define CANCELCOMMAND_H

#include "Commands/Command.h"

/* Description */

class CancelCommand : public Command
{
public:
	CancelCommand(Command *command);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool isFinished;
	Command* commandToCancel;
};

#endif
