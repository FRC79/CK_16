#include "TeleopHelper.h"
#include <math.h>

double TeleopHelper::mapJoystickToSpeedOutput(double input)
{
	if(fabs(input) < 0.05)
	{
		// Stop if joystick is near zero
		return 0.0;
	}
	else
	{
		double mapping;

		if(fabs(input) <= 0.7)
		{
			mapping = 0.33 * pow(fabs(input), 2) + 0.2;
			mapping = (input >= 0) ? mapping : -mapping; // Change to negative if the input was negative
			return mapping;
		}
		else
		{
			mapping = 3.57 * fabs(input) - 2.14;
			mapping = (input >= 0) ? mapping : -mapping; // Change to negative if the input was negative
			return mapping;
		}
	}
}
