#include "BangBang_Controller.h"
#include "Notifier.h"
#include "PIDOutput.h"
#include "CANJaguar.h"
#include <math.h>
#include "Synchronized.h"
//#include "Controller.h"
//#include "LiveWindowSendable"
//#include "ITableListener"

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
//	m_semaphore = semBCreate(SEM_Q_PRIORITY, SEM_FULL);
//
//	m_controlLoop = new Notifier(BangBang_Controller::CallCalculate, this);
//
//
//	m_P = Kp;
//	m_maximumOutput = 1.0;
//	m_minimumOutput = 0.0;
//
//	m_maximumInput = 0;
//	m_minimumInput = 0;
//
//	m_continuous = true; //TODO maybe?
//	m_enabled = false;
//	m_setpoint = 0;
//
//	m_prevError = 0;
//	m_totalError = 0;
//	m_tolerance = .05;
//
//	m_result = 0;
//	m_previousResult = 0.0;
//
//	m_pidInput = source;
//	m_pidOutput1 = output1;
//	m_pidOutput2 = output2;
//	m_period = period;
//	m_InvertOutputs = InvertOutputs;
//	m_F = kF;

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
	
//		CRITICAL_REGION(m_semaphore)
//		{
//			if (m_pidInput == 0) return;
//			if (m_pidOutput1 == 0) return;
//			enabled = m_enabled;
//			pidInput = m_pidInput;
//		}
//		END_REGION;

		//If speed is < desired speed, then output = 1.0
		//If speed is anything else, output = 0.0 (STOP)
	
		float controlVelocity; //TODO need to put in value
	
		
		if(controlVelocity < pidInput){
			
		} else {
			output = 1.0;
		}
	
		if(controlVelocity = pidInput){
			
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
	
	/**
	 * Set the PID Controller gain parameters.
	 * Set the proportional, integral, and differential coefficients.
	 * @param p Proportional coefficient
	 * @param i Integral coefficient
	 * @param d Differential coefficient
	 */
	void BangBang_Controller::SetPID(float p, float i, float d)
	{
		CRITICAL_REGION(m_semaphore)
		{
			m_P = p;
			m_I = i;
			m_D = d;
		}
		END_REGION;
	}

	/**
	 * Get the Proportional coefficient
	 * @return proportional coefficient
	 */
	float BangBang_Controller::GetP()
	{
		CRITICAL_REGION(m_semaphore)
		{
			return m_P;
		}
		END_REGION;
	}

	/**
	 * Get the Integral coefficient
	 * @return integral coefficient
	 */
	float BangBang_Controller::GetI()
	{
		CRITICAL_REGION(m_semaphore)
		{
			return m_I;
		}
		END_REGION;
	}

	/**
	 * Get the Differential coefficient
	 * @return differential coefficient
	 */
	float BangBang_Controller::GetD()
	{
		CRITICAL_REGION(m_semaphore)
		{
			return m_D;
		}
		END_REGION;
	}

	/**
	 * Return the current PID result
	 * This is always centered on zero and constrained the the max and min outs
	 * @return the latest calculated output
	 */
	float BangBang_Controller::Get()
	{
		float result;
		CRITICAL_REGION(m_semaphore)
		{
			result = m_result;
		}
		END_REGION;
		return result;
	}

	/**
	 *  Set the PID controller to consider the input to be continuous,
	 *  Rather then using the max and min in as constraints, it considers them to
	 *  be the same point and automatically calculates the shortest route to
	 *  the setpoint.
	 * @param continuous Set to true turns on continuous, false turns off continuous
	 */
	void BangBang_Controller::SetContinuous(bool continuous)
	{
		CRITICAL_REGION(m_semaphore)
		{
			m_continuous = continuous;
		}
		END_REGION;

	}

	/**
	 * Sets the maximum and minimum values expected from the input.
	 * 
	 * @param minimumInput the minimum value expected from the input
	 * @param maximumInput the maximum value expected from the output
	 */
	void BangBang_Controller::SetInputRange(float minimumInput, float maximumInput)
	{
		CRITICAL_REGION(m_semaphore)
		{
			m_minimumInput = minimumInput;
			m_maximumInput = maximumInput;	
		}
		END_REGION;

		SetSetpoint(m_setpoint);
	}

	/**
	 * Sets the minimum and maximum values to write.
	 * 
	 * @param minimumOutput the minimum value to write to the output
	 * @param maximumOutput the maximum value to write to the output
	 */
	void BangBang_Controller::SetOutputRange(float minimumOutput, float maximumOutput)
	{
		CRITICAL_REGION(m_semaphore)
		{
			m_minimumOutput = minimumOutput;
			m_maximumOutput = maximumOutput;
		}
		END_REGION;
	}

	/**
	 * Set the setpoint for the PIDController
	 * @param setpoint the desired setpoint
	 */
	void BangBang_Controller::SetSetpoint(float setpoint)
	{
		CRITICAL_REGION(m_semaphore)
		{
			if (m_maximumInput > m_minimumInput)
			{
				if (setpoint > m_maximumInput)
					m_setpoint = m_maximumInput;
				else if (setpoint < m_minimumInput)
					m_setpoint = m_minimumInput;
				else
					m_setpoint = setpoint;
			}
			else
			{
				m_setpoint = setpoint;
			}
		}
		END_REGION;	
	}

	/**
	 * Returns the current setpoint of the PIDController
	 * @return the current setpoint
	 */
	float BangBang_Controller::GetSetpoint()
	{
		float setpoint;
		CRITICAL_REGION(m_semaphore)
		{
			setpoint = m_setpoint;
		}
		END_REGION;
		return setpoint;
	}

	/**
	 * Retruns the current difference of the input from the setpoint
	 * @return the current error
	 */
	float BangBang_Controller::GetError()
	{
		float error;
		CRITICAL_REGION(m_semaphore)
		{
			error = m_error;
		}
		END_REGION;
		return error;
	}

	/*
	 * Set the percentage error which is considered tolerable for use with
	 * OnTarget.
	 * @param percentage error which is tolerable
	 */
	void BangBang_Controller::SetTolerance(float percent)
	{
		CRITICAL_REGION(m_semaphore)
		{
			m_tolerance = percent;
		}
		END_REGION;
	}

	/*
	 * Return true if the error is within the percentage of the total input range,
	 * determined by SetTolerance. This asssumes that the maximum and minimum input
	 * were set using SetInput.
	 */
	bool BangBang_Controller::OnTarget()
	{
		bool temp;
		CRITICAL_REGION(m_semaphore)
		{
			temp = fabs(m_error) < (m_tolerance / 100 * 
				(m_maximumInput - m_minimumInput));
		}
		END_REGION;
		return temp;
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

	/**
	 * Reset the previous error,, the integral term, and disable the controller.
	 */
	void BangBang_Controller::Reset()
	{
		Disable();

		CRITICAL_REGION(m_semaphore)
		{
			m_prevError = 0;
			m_totalError = 0;
			m_result = 0;
		}
		END_REGION;
	}

	//TODO ? add methods for:
//	  virtual ITable* GetTable();
//	    virtual std::string GetSmartDashboardType();
//	    virtual void ValueChanged(ITable* source, const std::string& key, EntryValue value, bool isNew);
//	    virtual void UpdateTable();
//	    virtual void StartLiveWindowMode();
//	    virtual void StopLiveWindowMode();


