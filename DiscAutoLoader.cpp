#include "DiscAutoLoader.h"

#include "Timer.h"

DiscAutoLoader::DiscAutoLoader(CANJaguar *roller, DualSolenoid *load_piston,
		DigitalInput *top_disc_sensor, DigitalInput *bottom_disc_sensor)
{
	m_roller = roller;
	m_load_piston = load_piston;
	m_top_disc_sensor = top_disc_sensor;
	m_bottom_disc_sensor = bottom_disc_sensor;
	final_time = 0.0;
	ResetVariables();
	enabled = false;
}

DiscAutoLoader::~DiscAutoLoader(){}

void DiscAutoLoader::ResetVariables()
{
	ready_to_shoot = false;
	disc_in_position = false;
	disc_loaded = false;
	ready_to_load = false;
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

void DiscAutoLoader::SetFinalTime(double time_in_milliseconds)
{
	double nano_seconds = time_in_milliseconds * 10e6;
	final_time = GetTime() + nano_seconds;
	timer_running = true;
}

void DiscAutoLoader::AutoLoad()
{
	if(enabled)
	{
		// Update disc position state variables
		disc_in_position = (m_top_disc_sensor->Get() == BROKEN ? true : false);
		disc_loaded = (m_bottom_disc_sensor->Get() == BROKEN ? true : false);
		
		if(!disc_in_position && !disc_loaded)
		{
			m_roller->Set(0.5);
			m_load_piston->Set(false);
		}
		else if(disc_in_position && !disc_loaded)
		{
			if(!ready_to_load)
			{
				if(!timer_running)
				{
					// Start timer
					SetFinalTime(2000.0);
				}
				else
				{
					// Keep checking if timer is finished
					if(GetClock() >= final_time)
					{
						final_time = 0.0;
						timer_running = false;
						ready_to_load = true;
					}
				}
			}
			else
			{
				// Ready to load
				m_roller->Set(0.0);
				m_load_piston->Set(true);
				ready_to_load = false;
			}	
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
