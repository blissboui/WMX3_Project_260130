#pragma once
#include "IncludeApi.h"

class MotionProfile
{
private:
	Motion::PVTCommand pvt[2];
	Motion::PosCommand pos;
public:
	void SetPVTProfile(int axis);
	void SetMovProfile(int axis);
	Motion::PVTCommand* GetPVTCommandAddr(int axis);
	Motion::PosCommand* GetPosCommandAddr();
};
