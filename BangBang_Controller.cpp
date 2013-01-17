//#include "CAN_VPID_Controller.h"
#include "Notifier.h"
#include "PIDOutput.h"
#include "CANJaguar.h"
#include <math.h>
#include "Synchronized.h"
/**
 * Allocate a PID object with the given constants for P, I, D
 * @param Kp the proportional coefficient
 * @param Ki the integral coefficient
 * @param Kd the derivative coefficient
 * @param source The PIDSource object that is used to get values
 * @param output The PIDOutput object that is set to the output value
 * @param period the loop time for doing calculations. This particularly effects calculations of the
 * integral and differental terms. The default is 50ms.


 PLEASE NOTE - This code has been modified to handle velocity control
 This means that it no longer works for position. We also used the derivative
 of position instead of velocity so as to remove the getVelocity bugs.

 */
BangBang_Controller::BangBang_Controller(float Kp, CANJaguar *source) :
	m_semaphore (0)
{
//	m_semaphore = semBCreate(SEM_Q_PRIORITY, SEM_FULL);
//
//	m_controlLoop = new Notifier(CAN_VPID_Controller::CallCalculate, this);
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
////	m_prevError = 0;
////	m_totalError = 0;
////	m_tolerance = .05;
//
//	m_result = 0;
//	m_previousResult = 0.0;
//
////	m_pidInput = source;
////	m_pidOutput1 = output1;
////	m_pidOutput2 = output2;
////	m_period = period;
////	m_InvertOutputs = InvertOutputs;
////	m_F = kF;
//
//	m_controlLoop->StartPeriodic(m_period);
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

	
}

