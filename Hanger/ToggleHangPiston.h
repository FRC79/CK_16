#ifndef TOGGLEHANGPISTON_H
#define TOGGLEHANGPISTON_H

#include "Commands/CommandGroup.h"
#include "RetractHangPiston.h"
#include "ExtendHangPiston.h"
#include "../RobotState.h"

/**
 *
 *
 * @author Andrew Schreiber
 */
class ToggleHangPiston: public CommandGroup {
public:	
	ToggleHangPiston();
};

#endif
