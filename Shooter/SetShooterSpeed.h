#ifndef SETSHOOTERSPEED_H
#define SETSHOOTERSPEED_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Andrew Schreiber
 */
class SetShooterSpeed: public CommandBase {
public:
	SetShooterSpeed(float speed);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	float _speed;
};

#endif
