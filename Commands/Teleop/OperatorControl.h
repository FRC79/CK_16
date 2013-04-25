#ifndef OPERATORCONTROL_H
#define OPERATORCONTROL_H

#include "Commands/CommandGroup.h"

#include "OperatorArcadeDrive.h"
#include "OperatorLoadPistonControl.h"
#include "OperatorShooterControl.h"
#include "OperatorToggleHanger.h"
#include "OperatorToggleTilt.h"

class OperatorControl : public CommandGroup
{
public:
	OperatorControl();
};

#endif
