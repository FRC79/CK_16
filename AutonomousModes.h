//#ifndef AUTONOMOUSMODES_H
//#define AUTONOMOUSMODES_H
//
//#include "CANJaguar.h"
//#include "Solenoid.h"
//#include "Task.h"
//#include "Timer.h"
//
//class AutonomousModes
//{
//public:
//	AutonomousModes(CANJaguar *roller, CANJaguar *feed_motor, CANJaguar *fire_motor,
//			Solenoid *load_piston, Solenoid *fire_piston);
//	~AutonomousModes();
//	
//	void StartFire3FromPyramid();
//	
//	static void Fire3FromPyramid();
//	
//	CANJaguar* GetRollerMotor();
//	CANJaguar* GetFeedMotor();
//	CANJaguar* GetFireMotor();
//	Solenoid* GetLoadPiston();
//	Solenoid* GetFirePiston();
//	
//private:
//	CANJaguar *m_roller, *m_feed_motor, *m_fire_motor;
//	Solenoid *m_load_piston, *m_fire_piston;
//	Task *fire3_task;
//};
//
//#endif
