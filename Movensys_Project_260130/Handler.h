#pragma once
#include "AdvancedMotionApi.h"
#include "ApiBufferApi.h"
#include "CompensationApi.h"
#include "CoreMotionApi.h"
#include "CyclicBufferApi.h"
#include "EventApi.h"
#include "IOApi.h"
#include "LogApi.h"
#include "UserMemoryApi.h"
#include "WMX3Api.h"
#include <iostream>

using namespace wmx3Api;
using namespace std;
class Handler
{
private:
	WMX3Api wmxlib;
	CoreMotion cMotion;
	Motion::PVTCommand pvt[2];
	Motion::PosCommand incMove;
	CoreMotionStatus st;
	ApiBufferOptions bufOp;
	Io ioData;
	int err = 0;
	char errString[256];
public:
	ApiBuffer buffer{ &wmxlib };
	//ApiBuffer buffer(&wmxlib);
	Handler() : cMotion(&wmxlib)
	{
	}
	void StartSetup()
	{
		// 디바이스 생성
		printf("Starting application...\n");
		err = wmxlib.CreateDevice(_T("C:\\Program Files\\SoftServo\\WMX3"), DeviceType::DeviceTypeNormal, INFINITE);
		if (err != ErrorCode::None)
		{
			wmxlib.ErrorToString(err, errString, sizeof(errString));
			printf("(%s)", errString);
			throw err;
		}

		// 통신 시작
		err = wmxlib.StartCommunication(5000);	 // 통신 시작될때까지 5초간 대기
		if (err != ErrorCode::None)
		{
			wmxlib.ErrorToString(err, errString, sizeof(errString));
			printf("(%s)", errString);
			throw err;
		}
		// 버퍼 생성
		buffer.Clear(0);
		buffer.CreateApiBuffer(0, 1024 * 1024 * 3);
		bufOp.autoRewind = true;
		buffer.SetOptions(0, &bufOp);
	}
	void StopSetup()
	{
		// 통신 해제, 디바이스 삭제
		wmxlib.StopCommunication();
		wmxlib.CloseDevice();
	}
	void StopServo()
	{
		// 서보 off
		cMotion.axisControl->SetServoOn(0, 0);
		cMotion.axisControl->SetServoOn(1, 0);
	}
	void ServoOn()
	{
		int counter = 1000;
		// 1 모터 서보 on
		err = cMotion.axisControl->SetServoOn(0, 1);
		if (err != ErrorCode::None)
		{
			wmxlib.ErrorToString(err, errString, sizeof(errString));
			printf("(%s)", errString);
			throw err;
		}

		// 2 모터 서보 on
		err = cMotion.axisControl->SetServoOn(1, 1);
		if (err != ErrorCode::None)
		{
			wmxlib.ErrorToString(err, errString, sizeof(errString));
			printf("(%s)", errString);
			throw err;
		}

		// 서보 on 완료 대기
		do
		{
			err = cMotion.GetStatus(&st);
			if (err != ErrorCode::None)
			{
				wmxlib.ErrorToString(err, errString, sizeof(errString));
				printf("(%s)", errString);
				throw err;
			}
			Sleep(10);
			counter--;
		} while (counter > 0 && (st.axesStatus[0].servoOn & st.axesStatus[1].servoOn) == 0);
	}
	void SetPVTProfile()
	{
		// 0 motor profile
		pvt[0].axis = 0;
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

		// 1 motor profile
		incMove.axis = 1;
		incMove.profile.type = ProfileType::T::Trapezoidal;
		incMove.profile.velocity = 1000;
		incMove.profile.acc = 3500;
		incMove.profile.dec = 3500;
		incMove.target = 600;

		pvt[1].axis = 1;
		pvt[1].pointCount = 5;
		pvt[1].points[0].pos = 250;
		pvt[1].points[0].velocity = 2000;
		pvt[1].points[0].timeMilliseconds = 250;
		pvt[1].points[1].pos = 500;
		pvt[1].points[1].velocity = 0;
		pvt[1].points[1].timeMilliseconds = 500;

		pvt[1].points[2].pos = 500;
		pvt[1].points[2].velocity = 0;
		pvt[1].points[2].timeMilliseconds = 550;

		pvt[1].points[3].pos = 250;
		pvt[1].points[3].velocity = -2000;
		pvt[1].points[3].timeMilliseconds = 800;
		pvt[1].points[4].pos = 0;
		pvt[1].points[4].velocity = 0;
		pvt[1].points[4].timeMilliseconds = 1050;
	}
	unsigned char GetStorBit(void)
	{
		unsigned char data;
		ioData.GetOutBit(0, 0, &data);
		return data;
	}
	void StartMotion()
	{	
		// 0번 모터 모션 실행
		err = cMotion.motion->StartPVT(&pvt[0]);
		if (err != ErrorCode::None)
		{
			wmxlib.ErrorToString(err, errString, sizeof(errString));
			printf("(%s)", errString);
			throw err;
		}
		// 1번 모터 모션 실행
		err = cMotion.motion->StartPVT(&pvt[1]);
		if (err != ErrorCode::None)
		{
			wmxlib.ErrorToString(err, errString, sizeof(errString));
			printf("(%s)", errString);
			throw err;
		}
		cMotion.motion->Wait(0);
		cMotion.motion->Wait(1);
	}
	void StartCutMotion()
	{
		err = buffer.StartRecordBufferChannel(0);
		if (err != ErrorCode::None)
		{
			buffer.ErrorToString(err, errString, sizeof(errString));
			printf("(%s)", errString);
			throw err;
		}
		// 0번 모터 모션 실행
		err = cMotion.motion->StartPVT(&pvt[0]);
		if (err != ErrorCode::None)
		{
			wmxlib.ErrorToString(err, errString, sizeof(errString));
			printf("(%s)", errString);
			throw err;
		}
		// 1번 모터 모션 실행
		err = cMotion.motion->StartMov(&incMove);
		if (err != ErrorCode::None)
		{
			wmxlib.ErrorToString(err, errString, sizeof(errString));
			printf("(%s)", errString);
			throw err;
		}
		buffer.Wait(0);
		buffer.Sleep(50);
		buffer.EndRecordBufferChannel();

		buffer.Execute(0);
	}
};