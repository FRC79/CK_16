//#include "AutonomousModes.h"
//
//AutonomousModes::AutonomousModes(CANJaguar *roller, CANJaguar *feed_motor, CANJaguar *fire_motor,
//		Solenoid *load_piston, Solenoid *fire_piston)
//{
//	m_roller = roller;
//	m_feed_motor = feed_motor;
//	m_fire_motor = fire_motor;
//	m_load_piston = load_piston;
//	m_fire_piston = fire_piston;
//	
//	fire3_task = new Task("fire3", (FUNCPTR)Fire3FromPyramid);
//}
//
//AutonomousModes::~AutonomousModes(){}
//
//void AutonomousModes::StartFire3FromPyramid()
//{
//	fire3_task->Start();
//}
//
//static void Fire3FromPyramid(AutonomousModes *local_auton)
//{
//	// Auton code
//	// Start shooter wheels
//	CANJaguar *feed_motor, *fire_motor, *roller;
//	Solenoid *fire_piston, *load_piston;
//	feed_motor = local_auton->GetFeedMotor();
//	fire_motor = local_auton->GetFireMotor();
//	roller = local_auton->GetRollerMotor();
//	fire_piston = local_auton->GetFirePiston();
//	load_piston = local_auton->GetLoadPiston();
//	
//	feed_motor->Set(60.0);
//	fire_motor->Set(60.0);
//	
//	Wait(4.0); // Wait 4 secs
//	
//	fire_piston->Set(true); // fire
//	
//	Wait(2.0); // Hold it out
//	
//	fire_piston->Set(false); // close
//	
//	Wait(1.0); // Wait to avoid clashing of pistons
//	
//	load_piston->Set(true);
//	
//	Wait(1.0); // Load it
//	
//	load_piston->Set(false);
//	
//	Wait(1.0); // Wait for it to come up
//	
//	roller->Set(0.5); // Reel in disc
//	
//	fire_piston->Set(true); // fire
//			
//	Wait(2.0); // Hold it out
//	
//	fire_piston->Set(false); // close
//	
//	Wait(1.0); // Wait to avoid clashing of pistons
//	
//	load_piston->Set(true);
//	
//	Wait(1.0); // Load it
//	
//	load_piston->Set(false);
//	
//	Wait(1.0); // Wait to avoid damage
//	
//	fire_piston->Set(true); // fire
//					
//	Wait(2.0); // Hold it out
//	
//	fire_piston->Set(false); // close
//
//	
//}
//
//CANJaguar* AutonomousModes::GetRollerMotor()
//{
//	return m_roller;
//}
//
//CANJaguar* AutonomousModes::GetFeedMotor()
//{
//	return m_feed_motor;
//}
//
//CANJaguar* AutonomousModes::GetFireMotor()
//{
//	return m_fire_motor;
//}
//
//Solenoid* AutonomousModes::GetLoadPiston()
//{
//	return m_load_piston;
//}
//
//Solenoid* AutonomousModes::GetFirePiston()
//{
//	return m_fire_piston;
//}
