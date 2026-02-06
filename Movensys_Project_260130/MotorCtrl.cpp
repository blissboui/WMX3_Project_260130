#include "MotorCtrl.h"
MotorCtrl::MotorCtrl(WMX3Api* wmx) : cMotion(wmx), wmx(wmx)
{
}
void MotorCtrl::ServoOn(int axis)
{
	int counter = 1000;
	// 1 모터 서보 on
	err = cMotion.axisControl->SetServoOn(axis, 1);
	if (err != ErrorCode::None)
	{
		(*wmx).ErrorToString(err, errString, sizeof(errString));
		printf("(%s)", errString);
		throw err;
	}

	// 서보 on 완료 대기
	do
	{
		err = cMotion.GetStatus(&st);
		if (err != ErrorCode::None)
		{
			(*wmx).ErrorToString(err, errString, sizeof(errString));
			printf("(%s)", errString);
			throw err;
		}
		Sleep(10);
		counter--;
	} while (counter > 0 && st.axesStatus[axis].servoOn == 0);
}
void MotorCtrl::ServoOn(int axis1, int axis2)
{
	ServoOn(axis1);
	ServoOn(axis2);
}
void MotorCtrl::ServoOff(int axis)
{
	// 서보 off
	err = cMotion.axisControl->SetServoOn(axis, 0);
	if (err != ErrorCode::None)
	{
		(*wmx).ErrorToString(err, errString, sizeof(errString));
		printf("(%s)", errString);
		throw err;
	}
}
void MotorCtrl::ServoOff(int axis1, int axis2)
{
	ServoOff(axis1);
	ServoOff(axis2);
}
void MotorCtrl::StartPVT(int axis)
{
	err = cMotion.motion->StartPVT(profile.GetPVTCommandAddr(axis));
	if (err != ErrorCode::None)
	{
		(*wmx).ErrorToString(err, errString, sizeof(errString));
		printf("(%s)", errString);
		throw err;
	}
}
void MotorCtrl::StartMov(int axis)
{
	err = cMotion.motion->StartMov(profile.GetPosCommandAddr());
	if (err != ErrorCode::None)
	{
		(*wmx).ErrorToString(err, errString, sizeof(errString));
		printf("(%s)", errString);
		throw err;
	}
}
void MotorCtrl::SetPVTProfile(int axis)
{
	profile.SetPVTProfile(axis);
}
void MotorCtrl::SetMovProfile(int axis)
{
	profile.SetMovProfile(axis);
}
void MotorCtrl::WaitMotion(int axis)
{
	cMotion.motion->Wait(axis);
}