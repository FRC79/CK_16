#include "DiscAutoLoader.h"

DiscAutoLoader::DiscAutoLoader(CANJaguar *roller, DualSolenoid *load_piston,
		DigitalInput *top_disc_sensor, DigitalInput *bottom_disc_sensor)
{
	m_roller = roller;
	m_load_piston = load_piston;
	m_top_disc_sensor = top_disc_sensor;
	m_bottom_disc_sensor = bottom_disc_sensor;
	ResetVariables();
	enabled = false;
	m_task = new Task("AutoLoad", (FUNCPTR)autoLoaderChecker)
}


static void autoLoaderChecker(DiscAutoLoader *a)
{
	while(1)
	{
		if(a->IsEnabled())
		{
			a->AutoLoad();
		}
		Wait(0.1);
	}
}


DiscAutoLoader::~DiscAutoLoader(){}

void DiscAutoLoader::ResetVariables()
{
	ready_to_shoot = false;
	disc_in_position = false;
	disc_loaded = false;
}

void DiscAutoLoader::Reset()
{
	ResetVariables();
	enabled = true; // Enable
}

void DiscAutoLoader::Disable()
{
	enabled = false;
}

bool DiscAutoLoader::IsEnabled()
{
	return enabled;
}

bool DiscAutoLoader::IsDiscInPosition()
{
	return disc_in_position;
}

bool DiscAutoLoader::IsDiscLoaded()
{
	return disc_loaded;
}

void DiscAutoLoader::AutoLoad()
{
	// Update disc position state variables ALWAYS
	disc_in_position = (m_top_disc_sensor->Get() == BROKEN ? true : false);
	disc_loaded = (m_bottom_disc_sensor->Get() == BROKEN ? true : false);
	
	if(enabled)
	{

		if(!disc_in_position && !disc_loaded)
		{
			// Run rollers until we have on to load
			m_roller->Set(0.5);
			m_load_piston->Set(false);
		}
		else if(disc_in_position && !disc_loaded)
		{
			// Load it into the chamber
			m_roller->Set(0.0);
			m_load_piston->Set(true);
			Wait(0.05)
		}
		else if(!disc_in_position && disc_loaded)
		{
			m_roller->Set(0.5);
			m_load_piston->Set(false);
		}
		else if(disc_in_position && disc_loaded)
		{
			m_roller->Set(0.0);
			m_load_piston->Set(false);
		}
	}
}
