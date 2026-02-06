#pragma once
#include "IncludeApi.h"
#include "MotionProfile.h"
class MotorCtrl
{
private:
	CoreMotion cMotion;
	CoreMotionStatus st;
	MotionProfile profile;
	WMX3Api* wmx;
public:
	MotorCtrl(WMX3Api* wmx);
	void ServoOn(int axis);
	void ServoOn(int axis1, int axis2);
	void ServoOff(int axis);
	void ServoOff(int axis1, int axis2);
	void StartPVT(int axis);
	void StartMov(int axis);
	void SetPVTProfile(int axis);
	void SetMovProfile(int axis);
	void WaitMotion(int axis);
};
