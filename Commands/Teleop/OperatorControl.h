#ifndef OPERATORCONTROL_H
#define OPERATORCONTROL_H

#include "Commands/CommandGroup.h"

#include "OperatorArcadeDrive.h"
#include "OperatorHopperControl.h"
#include "OperatorShooterControl.h"
#include "OperatorToggleHanger.h"
#include "OperatorToggleTilt.h"

class OperatorControl : public CommandGroup
{
public:
	OperatorControl();
};

#endif
