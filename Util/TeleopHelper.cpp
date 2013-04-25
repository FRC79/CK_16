#include "TeleopHelper.h"
#include <math.h>

double TeleopHelper::mapJoystickToPowerOutput(double input)
{
	if(fabs(input) < 0.05)
	{
		// Stop if joystick is near zero
		return 0.0;
	}
	else
	{
		double mapping;

		if(fabs(input) <= 0.75)
		{
			mapping = 0.95 * ((0.5 * pow(fabs(input), 2)) + 0.2);
			mapping = (input >= 0) ? mapping : -mapping; // Change to negative if the input was negative
			return mapping;
		}
		else
		{
			mapping = 2.16 * fabs(input) - 1.16;
			mapping = (input >= 0) ? mapping : -mapping; // Change to negative if the input was negative
			return mapping;
		}
	}
}
