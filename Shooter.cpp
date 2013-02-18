#include "Shooter.h"

Shooter::Shooter(CANJaguar* rear, CANJaguar* front, Solenoid *fireCylinder, DiscAutoLoader *loader)
{
	m_rear = rear;
	m_front = front;
	m_loader = loader;
	m_task = new Task("Shooter", (FUNCPTR)CheckShooter);
	auto_fire = m_fire = m_enable = false;
	m_autoLoad = m_loader->IsEnabled();
	m_fireCylinder = fireCylinder;
}

Shooter::~Shooter(){}

void Shooter::CheckShooter(Shooter *s)
{
	DiscAutoLoader *loader;
	loader = s->GetDiscAutoLoader();
	
	Solenoid *fireCylinder;
	fireCylinder = s->GetFireCylinder();
	
	if(s->IsEnabled())
	{	
		// Fire Cylinder if I'm supposed to AND I'm loaded
		if(loader->IsDiscLoaded() && s->IsReadyToFire())
		{
			fireCylinder->Set(true);
			s->SetAutoLoad(loader->IsEnabled()); // Store prev autoLoad value
			loader->Disable();// Want to wait on the autoLoad until we're done firing 
			Wait(SHOOTER_DELAY);// We wait to retract until we're done
			fireCylinder->Set(false);
			if(s->GetAutoLoad()){loader->Reset();} // Now we set it back to whatever it was
			// WE MAY HAVE TO ADD AN Enable FUNCTION TO DiscAutoLoader
			s->SetReadyToFire(s->GetAutoFire()); // If auto_fire is enabled we keep firing
		}
	}
	else
	{
		fireCylinder->Set(false); // If shooter is disabled don't fire
	}
	Wait(0.01);
}

bool Shooter::IsEnabled()
{
	return m_enable;
}

bool Shooter::IsReadyToFire()
{
	return m_fire;
}

void Shooter::SetReadyToFire(bool state)
{
	m_fire = state;
}

bool Shooter::GetAutoLoad()
{
	return m_autoLoad;
}

void Shooter::SetAutoLoad(bool state)
{
	m_autoLoad = state;
}

bool Shooter::GetAutoFire()
{
	return auto_fire;
}

DiscAutoLoader *Shooter::GetDiscAutoLoader()
{
	return m_loader;
}

Solenoid *Shooter::GetFireCylinder()
{
	return m_fireCylinder;
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
