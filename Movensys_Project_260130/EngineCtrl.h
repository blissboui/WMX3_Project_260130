#pragma once
#include "IncludeApi.h"

class EngineCtrl
{
private:
	WMX3Api wmxlib;
public:
	void CreateDevice();
	void StartCommunication();
	void EndEngine();
	WMX3Api* GetWmxAddr();
};