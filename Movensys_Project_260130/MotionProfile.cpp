#include "MotionProfile.h"
void MotionProfile::SetPVTProfile(int axis)
{
	// motor 1
	pvt[0].axis = axis;
	pvt[0].pointCount = 7;
	pvt[0].points[0].pos = 125;
	pvt[0].points[0].velocity = 2000;
	pvt[0].points[0].timeMilliseconds = 125;
	pvt[0].points[1].pos = 625;
	pvt[0].points[1].velocity = 2000;
	pvt[0].points[1].timeMilliseconds = 375;
	pvt[0].points[2].pos = 750;
	pvt[0].points[2].velocity = 0;
	pvt[0].points[2].timeMilliseconds = 500;

	pvt[0].points[3].pos = 750;
	pvt[0].points[3].velocity = 0;
	pvt[0].points[3].timeMilliseconds = 550;

	pvt[0].points[4].pos = 625;
	pvt[0].points[4].velocity = -2000;
	pvt[0].points[4].timeMilliseconds = 675;
	pvt[0].points[5].pos = 125;
	pvt[0].points[5].velocity = -2000;
	pvt[0].points[5].timeMilliseconds = 925;
	pvt[0].points[6].pos = 0;
	pvt[0].points[6].velocity = 0;
	pvt[0].points[6].timeMilliseconds = 1050;

	//// motor 2
	//pvt[1].axis = axis2;
	//pvt[1].pointCount = 5;
	//pvt[1].points[0].pos = 250;
	//pvt[1].points[0].velocity = 2000;
	//pvt[1].points[0].timeMilliseconds = 250;
	//pvt[1].points[1].pos = 500;
	//pvt[1].points[1].velocity = 0;
	//pvt[1].points[1].timeMilliseconds = 500;

	//pvt[1].points[2].pos = 500;
	//pvt[1].points[2].velocity = 0;
	//pvt[1].points[2].timeMilliseconds = 550;

	//pvt[1].points[3].pos = 250;
	//pvt[1].points[3].velocity = -2000;
	//pvt[1].points[3].timeMilliseconds = 800;
	//pvt[1].points[4].pos = 0;
	//pvt[1].points[4].velocity = 0;
	//pvt[1].points[4].timeMilliseconds = 1050;
}
void MotionProfile::SetMovProfile(int axis)
{
	pos.axis = axis;
	pos.profile.type = ProfileType::T::Trapezoidal;
	pos.profile.velocity = 1000;
	pos.profile.acc = 3500;
	pos.profile.dec = 3500;
	pos.target = 600;
}
Motion::PVTCommand* MotionProfile::GetPVTCommandAddr(int axis)
{
	return &pvt[axis];
}
Motion::PosCommand* MotionProfile::GetPosCommandAddr()
{
	return &pos;
}