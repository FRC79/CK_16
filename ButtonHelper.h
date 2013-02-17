#ifndef BUTTONHELPER_H
#define BUTTONHELPER_H

#include "Joystick.h"

/* 
 * This class helps with the state changes
 * of buttons on a joystick and makes dealing
 * with button toggles much simpler to implement.
 */

class ButtonHelper
{
public:
	ButtonHelper(Joystick *joystick);
	~ButtonHelper();
	
	/* The ButtonHelper must be updated in order
	 * to record previous and existing states.
	 * This should be done near the begining of
	 * an implementation. */
	void Update();
	
	/* Returns a boolean specifiying whether or
	 * not the button was toggled */
	bool WasButtonToggled(int button);
	
private:
	static const int NUM_BUTTONS = 10;
	bool buttonsWereDown[NUM_BUTTONS];
	bool buttonsAreDown[NUM_BUTTONS];
	Joystick *m_joystick;
};

#endif
