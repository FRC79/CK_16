#ifndef STOPDRIVEMOTORS_H
#define STOPDRIVEMOTORS_H

#include "../CommandBase.h"

/* Stops the wheel motors on the drivetrain. */

class StopDriveMotors : public CommandBase
{
public:
	StopDriveMotors();
	StopDriveMotors(bool runContinuously);
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
