#ifndef FIREDISC_H
#define FIREDISC_H

#include "../CommandBase.h"
#include "../RobotState.h"

/**
 *
 *
 * @author Andrew Schreiber
 */
class FireDisc: public CommandBase {
public:
	FireDisc();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	bool isFinished;
};

#endif
