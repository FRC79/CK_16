#ifndef TESTDRIVE_H
#define TESTDRIVE_H

#include "../../CommandBase.h"

/* Description */

class TestDrive : public CommandBase 
{
public:
	TestDrive();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
