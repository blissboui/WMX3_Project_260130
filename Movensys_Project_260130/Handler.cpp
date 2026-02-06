#include "Handler.h"
int err = 0;
char errString[256] = { 0 };
Handler::Handler() : apiBuf(engine.GetWmxAddr()), mCtrl(engine.GetWmxAddr())
{
}
void Handler::StartSetup()
{
	// 디바이스 생성
	printf("Starting application...\n");
	engine.CreateDevice();

	// 통신 시작
	engine.StartCommunication();

	// 버퍼 생성
	apiBuf.CreateBuffer(0, 1024 * 1024 * 3);
}
void Handler::ShowStatus(int n)
{
	system("cls");
	switch (n)
	{
	case 1:
		cout << "Running..." << endl;
		break;
	case 2:
		cout << "Stop" << endl;
		break;
	case 3:
		cout << "Exit" << endl;
		break;
	}
}
void Handler::EndSetup()
{
	// 통신 해제, 디바이스 삭제
	engine.EndEngine();
}
void Handler::ServoOn(int axis1, int axis2)
{
	// 서보 on
	mCtrl.ServoOn(axis1, axis2);
}
void Handler::ServoOff(int axis1, int axis2)
{
	// 서보 off
	mCtrl.ServoOff(axis1, axis2);
}
void Handler::SetPVTProfile(int axis)
{
	mCtrl.SetPVTProfile(axis);
}
void Handler::SetMovProfile(int axis)
{
	mCtrl.SetMovProfile(axis);
}
int Handler::GetStatusBit(void)
{
	unsigned char data;
	ioData.GetOutByte(0, &data);
	if (data == 0)
		return 0;
	return (int)log2(data) + 1;
}
void Handler::ResetStatusBit(void)
{
	// 전체 bit off
	ioData.SetOutByte(0, 0);
}
void Handler::StartMotion()
{
	// 0번 모터 모션 실행
	mCtrl.StartPVT(0);
	// 1번 모터 모션 실행
	//mCtrl.StartPVT(1);
	mCtrl.StartMov(1);
	mCtrl.WaitMotion(0);
	mCtrl.WaitMotion(1);
}
void Handler::SetApiBufCutMotion()
{
	apiBuf.StartRecord(0);
	// 0번 축 모션 실행
	mCtrl.StartPVT(0);

	// 1번 축 모션 실행
	mCtrl.StartMov(1);

	apiBuf.WaitBuffer(0);
	apiBuf.SleepBuffer(50);
	apiBuf.EndRecord();
}
void Handler::ExecuteApi(int ch)
{
	apiBuf.ExecuteApi(ch);
}
void Handler::HaltApi(int ch)
{
	apiBuf.HaltApi(ch);
}