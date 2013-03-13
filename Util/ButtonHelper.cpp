#include "ButtonHelper.h"

ButtonHelper::ButtonHelper(Joystick *joystick)
{
	m_joystick = joystick;
	
	// Initialize button state arrays
	int i;
	for(i=0; i < NUM_BUTTONS; i++)
	{
		buttonsAreDown[i] = false;
		buttonsWereDown[i] = false;
	}
}

ButtonHelper::~ButtonHelper(){}

void ButtonHelper::Update()
{
	int i;
	for(i=0; i < NUM_BUTTONS; i++)
	{
		buttonsWereDown[i] = buttonsAreDown[i];
		buttonsAreDown[i] = m_joystick->GetRawButton(i+1); // There is no 0th button
	}
}

bool ButtonHelper::WasButtonToggled(int button)
{
	if(buttonsWereDown[button-1] && !buttonsAreDown[button-1])
	{
		return true;
	}
	else
	{
		return false;
	}
}
