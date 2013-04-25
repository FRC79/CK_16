#ifndef RUNCOMPRESSOR_H
#define RUNCOMPRESSOR_H

#include "../CommandBase.h"
#include "Relay.h"
#include "DigitalInput.h"
#include "../RobotMap.h"

/* Runs the compressor until it the tanks are at the
 * desired pressure and trip the pressure switch. */

class RunCompressor : public CommandBase 
{
public:
	RunCompressor();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool isFinished;
	Relay* compressor;
	DigitalInput* pressureSwitch;
};

#endif
