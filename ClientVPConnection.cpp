#include "ClientVPConnection.h"
#include "SmartDashboard/SmartDashboard.h"

/*
 * It is possible to make this class completely with
 * static functions, but ClientVPConnection is a long
 * thing to type every time you want to get data from
 * the SmartDashboard
 */

bool ClientVPConnection::IsTargetFound()
{
	return SmartDashboard.GetBoolean("found");
}

double ClientVPConnection::GetAzimuth()
{
	return SmartDashboard.GetNumber("azimuth");
}

double ClientVPConnection::GetRange()
{
	return SmartDashboard.GetNumber("range");
}

double ClientVPConnection::GetRPMs()
{
	return SmartDashboard.GetNumber("rpms");
}
