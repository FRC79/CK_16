#ifndef SPINSHOOTERWHEELSBB_H
#define SPINSHOOTERWHEELSBB_H

#include "../CommandBase.h"

/* Description */

class SpinShooterWheelsBB : public CommandBase 
{
public:
	static const double GEAR_RATIO = 1.0 / 2.5;
	
	SpinShooterWheelsBB(double front_rpms);
	SpinShooterWheelsBB(double front_rpms, double back_rpms);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	BangBang_Controller *frontCtrl, *backCtrl;
	double frontSpeed, backSpeed;
};

#endif
