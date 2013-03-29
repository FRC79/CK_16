#include "DiscShooter.h"
#include "Timer.h"
#include "../RobotMap.h"

DiscShooter::DiscShooter() : Subsystem("DiscShooter")
{
	// Init components
	FrontShooterWheel = new CANJaguar(RobotMap::FRONT_SHOOTER_WHEEL_ID);
	BackShooterWheel = new CANJaguar(RobotMap::BACK_SHOOTER_WHEEL_ID);
	FirePiston = new Solenoid(RobotMap::SHOOTER_FIRE_PISTON_ID);
	piston_delay_time = RobotMap::PISTON_DELAY_TIME;
	
	// Setup encoders on the Jags
	FrontShooterWheel->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
	BackShooterWheel->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
	FrontShooterWheel->ConfigEncoderCodesPerRev(TICS_PER_SHOOTER_REV);
	BackShooterWheel->ConfigEncoderCodesPerRev(TICS_PER_SHOOTER_REV);
	
	is_fire_piston_extended = false;
	
	// Instantiate corresponding components into DualSolenoids
	TiltPiston = new DoubleSolenoid(RobotMap::TILT_PISTON_IN_ID, 
			RobotMap::TILT_PISTON_OUT_ID);
	
	is_tilted_up = true;
}

DiscShooter::~DiscShooter()
{
	delete FrontShooterWheel;
	delete BackShooterWheel;
	delete FirePiston;
	delete TiltPiston;
}

CANJaguar* DiscShooter::GetShooterWheel(ShooterWheel wheel)
{
	switch(wheel){
	case kFront:
		return FrontShooterWheel;
		break;
	case kBack:
		return BackShooterWheel;
		break;
	default:
		return NULL;
		break;
	}
}

/* Only sets an individual power rating to each jag (open loop). */
void DiscShooter::SetFrontAndBackMotorOutputs(float front_power, float back_power)
{
	FrontShooterWheel->Set(front_power);
	BackShooterWheel->Set(back_power);
}

/* Only sets a power rating to the jags (open loop). */
void DiscShooter::SetMotorOutputs(float power)
{
	SetFrontAndBackMotorOutputs(power, power);
}

void DiscShooter::StopMotors()
{
	SetMotorOutputs(0.0);
}

bool DiscShooter::IsFirePistonExtended()
{
	return is_fire_piston_extended;
}

void DiscShooter::SetFirePiston(bool piston_state)
{
	FirePiston->Set(piston_state);
	is_fire_piston_extended = piston_state;
}

void DiscShooter::InvertCurrentFirePistonState()
{
	SetFirePiston(!IsFirePistonExtended());
}

void DiscShooter::ExtendFirePiston()
{
	SetFirePiston(true);
}

void DiscShooter::RetractFirePiston()
{
	SetFirePiston(false);
}

/* Extends and then retracts the fire piston after a 
 * certain period of time. */
void DiscShooter::FireThenRetract()
{
	ExtendFirePiston();
	Wait(piston_delay_time);
	RetractFirePiston();
	Wait(piston_delay_time);
}

bool DiscShooter::IsTiltedUp()
{
	return is_tilted_up;
}

void DiscShooter::SetTilt(bool tilted_up)
{
	TiltPiston->Set(tilted_up ? DoubleSolenoid::kForward : DoubleSolenoid::kReverse);
	SmartDashboard::PutBoolean(RobotMap::SHOOTER_TILTED_KEY, tilted_up); // send state to SmartDashboard
	is_tilted_up = tilted_up;
}

void DiscShooter::InvertCurrentTiltState()
{
	SetTilt(!IsTiltedUp());
}

void DiscShooter::TiltUp()
{
	SetTilt(true);
}

void DiscShooter::TiltDown()
{
	SetTilt(false);
}

void DiscShooter::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}