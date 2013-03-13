#include "DualSolenoid.h"

DualSolenoid::DualSolenoid(Solenoid *in_solenoid, Solenoid *out_solenoid, 
		bool invert, bool default_state)
{
	m_in_solenoid = in_solenoid;
	m_out_solenoid = out_solenoid;
	m_invert = invert;
	m_state = default_state;
}

DualSolenoid::~DualSolenoid()
{
	delete m_in_solenoid;
	delete m_out_solenoid;
}

bool DualSolenoid::Get()
{
	return m_state;
}

void DualSolenoid::Set(bool state)
{
	if(m_invert)
	{
		m_in_solenoid->Set(!state);
		m_out_solenoid->Set(state);
	}
	else
	{
		m_in_solenoid->Set(state);
		m_out_solenoid->Set(!state);
	}
	
	m_state = state;
}

bool DualSolenoid::GetInverted()
{
	return m_invert;
}

void DualSolenoid::SetInverted(bool invert)
{
	m_invert = invert;
}
