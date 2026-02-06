#pragma once
#include "IncludeApi.h"

class ApiBuf
{
private:
	ApiBuffer apiBuf;
	ApiBufferOptions bufOp;
public:
	ApiBuf(WMX3Api* wmx3);
	void CreateBuffer(unsigned int ch, unsigned int size);
	void StartRecord(int ch);
	void EndRecord();
	void WaitBuffer(unsigned int ch);
	void SleepBuffer(unsigned int msec);
	void ExecuteApi(unsigned int ch);
	void HaltApi(unsigned int ch);
};
