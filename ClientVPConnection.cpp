#include "ClientVPConnection.h"
#include "SmartDashboard.h"

/*
 * It is possible to make this class completely with
 * static functions, but ClientVPConnection is a long
 * thing to type every time you want to get data from
 * the SmartDashboard
 */

ClientVPConnection::IsTargetFound()
{
	return SmartDashboard.GetBoolean("found");
}

ClientVPConnection::GetAzimuth()
{
	return SmartDashboard.GetNumber("azimuth");
}

ClientVPConnection::GetRange()
{
	return SmartDashboard.GetNumber("range");
}

ClientVPConnection::GetRPMs()
{
	return SmartDashboard.GetNumber("rpms");
}