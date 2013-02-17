#include "Shooter.h"

Shooter::Shooter(CANJaguar* rear, CANJaguar* front, Solenoid *fireCylinder, DiscAutoLoader *loader)
{
	m_rear = rear;
	m_front = front;
	m_loader = loader;
	m_task = new Task("Shooter", (FUNCPTR)checkShooter);
	auto_fire = m_fire = m_enable = false;
	m_autoLoad = m_loader->IsEnabled();
	m_fireCylinder = fireCylinder;
}

Shooter::~Shooter(); // I'm about 90% sure this is valid syntax

static void checkShooter(Shooter *s)
{
	if(m_enable)
	{
		// Fire Cylinder if I'm supposed to AND I'm loaded
		if(m_loader->IsDiscLoaded() && m_fire)
		{
			m_fireCylinder->Set(true);
			m_autoLoad = m_loader->IsEnabled(); // Store prev autoLoad value
			m_loader->Disable();// Want to wait on the autoLoad until we're done firing 
			Wait(SHOOTER_DELAY);// We wait to retract until we're done
			m_fireCylinder->Set(false);
			if(m_autoLoad){m_loader->Enable()} // Now we set it back to whatever it was
			m_fire = auto_fire; // If auto_fire is enabled we keep firing
		}
	}
	else
	{
		m_fireCylinder->Set(false); // If shooter is disabled don't fire
	}
	Wait(0.01)
}

void Shooter::Enable()
{
	m_enable = true;
}

void Shooter::Disable()
{
	m_enable = false;
}

void Shooter::EnableAutomaticFire()
{
	auto_fire = true;
}

void Shooter::DisableAutomaticFire()
{
	auto_fire = false;
}

void Shooter::Fire()
{
	m_fire = true;
}

void Shooter::StopFire()
{
	m_fire = false;
}