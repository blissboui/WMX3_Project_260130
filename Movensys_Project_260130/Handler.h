#pragma once
#include "EngineCtrl.h"
#include "ApiBuf.h"
#include "MotorCtrl.h"

class Handler
{
private:
	EngineCtrl engine;
	ApiBuf apiBuf;
	MotorCtrl mCtrl;
	Io ioData;
public:
	Handler();
	void StartSetup();
	void ShowStatus(int n);
	void EndSetup();
	void ServoOn(int axis1, int axis2);
	void ServoOff(int axis1, int axis2);
	void SetPVTProfile(int axis);
	void SetMovProfile(int axis);
	int GetStatusBit(void);
	void ResetStatusBit(void);
	void StartMotion();
	void SetApiBufCutMotion();
	void ExecuteApi(int ch);
	void HaltApi(int ch);
};