#ifndef DUALSOLENOID_H
#define DUALSOLENOID_H

#include "Solenoid.h"

/*
 * This class represents a dual solenoid by
 * keeping track of the overall and individual
 * states of two solenoids.
 */

class DualSolenoid
{
public:
	DualSolenoid(Solenoid *in_solenoid, Solenoid *out_solenoid, bool invert,
			bool default_state);
	~DualSolenoid();
	
	/* Get and Set overall solenoid state */
	bool Get();
	void Set(bool state);
	
	/* 
	 * Set invert WILL NOT reset the solenoid states
	 * automatically. It only resets the invert variable.
	 * To reset, a Set() must be called 
	 */
	bool GetInverted();
	void SetInverted(bool invert);

private:
	bool m_state;
	bool m_invert;
	Solenoid *m_in_solenoid;
	Solenoid *m_out_solenoid;
};

#endif
