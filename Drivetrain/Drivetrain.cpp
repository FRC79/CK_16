#include "Drivetrain.h"
#include "RobotDrive.h"
#include "../RobotMap.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain")
{
	// Init speed controllers
	Front_R = new CANJaguar(RobotMap::FRONT_RIGHT_DRIVE_ID);
	Front_L = new CANJaguar(RobotMap::FRONT_LEFT_DRIVE_ID);
	Rear_R = new CANJaguar(RobotMap::REAR_RIGHT_DRIVE_ID);
	Rear_L = new CANJaguar(RobotMap::REAR_LEFT_DRIVE_ID);
	
	// Set encoder position references for motors
	Front_R->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
	Front_L->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
	Rear_R->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
	Rear_L->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
	
	// Set how many tics are in one revolution of the wheel
	Front_R->ConfigEncoderCodesPerRev(TICS_PER_REV);
	Front_L->ConfigEncoderCodesPerRev(TICS_PER_REV);
	Rear_R->ConfigEncoderCodesPerRev(TICS_PER_REV);
	Rear_L->ConfigEncoderCodesPerRev(TICS_PER_REV);
	
	// Init RobotDrive
	RoboDrive = new RobotDrive(Front_L, Rear_L, Front_R, Rear_R);
	
	// Invert motors
	RoboDrive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	RoboDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
	RoboDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	RoboDrive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	
	// Init Gyro
	TurnGyro = new Gyro(RobotMap::TURN_GYRO_ID);
}

Drivetrain::~Drivetrain()
{
	delete Front_R;
	delete Front_L;
	delete Rear_R;
	delete Rear_L;
}

void Drivetrain::ArcadeDrive(float power, float rot)
{
	RoboDrive->ArcadeDrive(power, rot, false); // Power and rotation
}

Gyro* Drivetrain::GetTurnGyro()
{
	return TurnGyro;
}

void Drivetrain::SetLeftAndRightMotorOutputs(float left_power, float right_power)
{
	RoboDrive->SetLeftRightMotorOutputs(left_power, right_power); // Left and right sides
}

void Drivetrain::SetMotorOutputs(float power)
{
	SetLeftAndRightMotorOutputs(power, power);
}

/* Get encoder value for the specified motor */
double Drivetrain::GetPosition(Motor encoder_motor)
{
	switch(encoder_motor){
	case kFrontRight:
		return Front_R->GetPosition();
		break;
	case kFrontLeft:
		return Front_L->GetPosition();
		break;
	case kRearRight:
		return Rear_R->GetPosition();
		break;
	case kRearLeft:
		return Rear_L->GetPosition();
		break;
	default:
		return 0.0;
		break;
	}
}

void Drivetrain::InitDefaultCommand()
{
}
