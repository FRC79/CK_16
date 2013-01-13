#ifndef CLIENTVPCONNECTION_H
#define CLIENTVPCONNECTION_H

/*
 * This class handles the connection between the
 * cRio and the driverstation's SmartDashboard
 * running the KrunchCV vision processing extension.
 * Data calculated from the extension is retreivable
 * from this handler.
 */

class ClientVPConnection
{
public:
	/*
	 * All of these functions are based on the highest
	 * goal found in the camera image. Though there may
	 * be mulitple goals in the robot's view, only the
	 * highest recognizable goal will be considered so
	 * that shooting for the goal with the greatest
	 * amount of points awarded is always a priority.
	 */
	bool IsTargetFound();
	double GetAzimuth();
	double GetRange();
	double GetRPMS();
};

#endif
