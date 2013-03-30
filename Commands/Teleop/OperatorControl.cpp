#include "OperatorControl.h"

OperatorControl::OperatorControl() : CommandGroup("OperatorControl")
{
	/* Run all of the operator control commands in parallel. */
	AddParallel(new OperatorArcadeDrive());
//	AddParallel(new OperatorHopperControl());
	AddParallel(new OperatorShooterControl());
	AddParallel(new OperatorToggleHanger());
	AddParallel(new OperatorToggleTilt());
}
