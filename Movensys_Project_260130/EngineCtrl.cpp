#include "EngineCtrl.h"
void EngineCtrl::CreateDevice()
{
	err = wmxlib.CreateDevice(_T("C:\\Program Files\\SoftServo\\WMX3"), DeviceType::DeviceTypeNormal, INFINITE);
	if (err != ErrorCode::None)
	{
		wmxlib.ErrorToString(err, errString, sizeof(errString));
		printf("(%s)", errString);
		throw err;
	}
}
void EngineCtrl::StartCommunication()
{
	err = wmxlib.StartCommunication(5000);	 // 통신 시작될때까지 5초간 대기
	if (err != ErrorCode::None)
	{
		wmxlib.ErrorToString(err, errString, sizeof(errString));
		printf("(%s)", errString);
		throw err;
	}
}
void EngineCtrl::EndEngine()
{
	// 통신 해제, 디바이스 삭제
	wmxlib.StopCommunication();
	wmxlib.CloseDevice();
}

WMX3Api* EngineCtrl::GetWmxAddr()
{
	return &wmxlib;
}
