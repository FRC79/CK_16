#include "WPILib.h"
#include "CANJaguar.h"
//#include "Intake.h"
#include "BallConveyor.h"
#include "Timer.h"
#include "CAN_VPID_Controller.h"
#include "CSVReader.h"

class CK16_Auton
{
	
	CANJaguar *frontLeft, *rearLeft, *rearRight, *frontRight,;
	CSVReader *config;
public:
	CK15_Auton(CANJaguar *frontL,CANJaguar *rearL,CANJaguar *frontR, CANJaguar *rearR, CSVReader *m_csv);
	void initialize();
	void step(int stepNum);
	void CK16_Auton::autonStartClock();
		
};
