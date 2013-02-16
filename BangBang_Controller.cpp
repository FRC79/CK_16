#include "BangBang_Controller.h"
#include "Notifier.h"
#include "PIDOutput.h"
#include "CANJaguar.h"
#include <math.h>
#include "Synchronized.h"

/**
 * Allocate a PID object with the given constants for P, I, D
 * @param source The PIDSource object that is used to get values
 * @param output The PIDOutput object that is set to the output value


 PLEASE NOTE - This code will spin at a given velocity until certain 
 velocity has been reached and then stops.

 */
BangBang_Controller::BangBang_Controller(CANJaguar *source, PIDOutput *output) :
	m_semaphore (0)
{
	m_semaphore = semBCreate(SEM_Q_PRIORITY, SEM_FULL);

	m_controlLoop = new Notifier(BangBang_Controller::CallCalculate, this);


	m_P = Kp;
	m_maximumOutput = 1.0;
	m_minimumOutput = 0.0;

	m_maximumInput = 0;
	m_minimumInput = 0;

	m_continuous = true; //TODO maybe?
	m_enabled = false;
	m_setpoint = 0;

	m_prevError = 0;
	m_totalError = 0;
	m_tolerance = .05;

	m_result = 0;
	m_previousResult = 0.0;

	m_pidInput = source;
	m_pidOutput1 = output1;
	m_pidOutput2 = output2;
	m_period = period;
	m_InvertOutputs = InvertOutputs;
	m_F = kF;
	m_controlVelocity = 0.0;

	m_controlLoop->StartPeriodic(m_period);
}

 /**
  * Read the input, calculate the output accordingly, and write to the output.
  * This should only be called by the Notifier indirectly through CallCalculate
  * and is created during initialization.
  */	
void BangBang_Controller::Calculate()
{
	bool enabled;
	CANJaguar *pidInput;
	
		CRITICAL_REGION(m_semaphore)
		{
			if (m_pidInput == 0) return;
			if (m_pidOutput1 == 0) return;
			enabled = m_enabled;
			pidInput = m_pidInput;
		}
		END_REGION;

		//If speed is < desired speed, then output = 1.0
		//If speed is anything else, output = 0.0 (STOP)
	
	
		
		if(m_controlVelocity < pidInput){
			
		} else {
			output = 1.0;
		}
	
		if(m_controlVelocity = pidInput){
			
		}else{
			output = 0.0;
		}
		
		pidOutput1->PIDWrite(result);
				pidOutput2->PIDWrite((m_InvertOutputs) ? -result : result);
				m_prevPosition = currentPosition; // Store the current position
	}
	
	/**
	 * Call the Calculate method as a non-static method. This avoids having to prepend
	 * all local variables in that method with the class pointer. This way the "this"
	 * pointer will be set up and class variables can be called more easily.
	 * This method is static and called by the Notifier class.
	 * @param controller the address of the PID controller object to use in the background loop
	 */
	void BangBang_Controller::CallCalculate(void *controller)
	{
		BangBang_Controller *control = (BangBang_Controller*) controller;
		control->Calculate();
	}
	

	void BangBang_Controller::Set(float controlVelocity)
	{
		m_controlVelocity = controlVelocity
	}

	/**
	 * Begin running the PIDController
	 */
	void BangBang_Controller::Enable()
	{
		CRITICAL_REGION(m_semaphore)
		{			
			m_enabled = true;
		}
		END_REGION;	
	}
	/**
	 * Stop running the PIDController, this sets the output to zero before stopping.
	 */
	void BangBang_Controller::Disable()
	{
		CRITICAL_REGION(m_semaphore)
		{
			m_pidOutput1->PIDWrite(0);
			m_enabled = false;
		}
		END_REGION;
	}

	/**
	 * Return true if PIDController is enabled.
	 */
	bool BangBang_Controller::IsEnabled()
	{
		bool enabled;
		CRITICAL_REGION(m_semaphore)
		{
			enabled = m_enabled;
		}
		END_REGION;
		return enabled;
	}

	//TODO ? add methods for:
//	  virtual ITable* GetTable();
//	    virtual std::string GetSmartDashboardType();
//	    virtual void ValueChanged(ITable* source, const std::string& key, EntryValue value, bool isNew);
//	    virtual void UpdateTable();
//	    virtual void StartLiveWindowMode();
//	    virtual void StopLiveWindowMode();


