#include "ApiBuf.h"

ApiBuf::ApiBuf(WMX3Api* wmx3) : apiBuf(wmx3)
{
}
void ApiBuf::CreateBuffer(unsigned int ch, unsigned int size)
{
	apiBuf.Clear(ch);
	apiBuf.CreateApiBuffer(ch, size);
	bufOp.autoRewind = true;
	apiBuf.SetOptions(ch, &bufOp);
}
void ApiBuf::StartRecord(int ch)
{
	err = apiBuf.StartRecordBufferChannel(ch);
	if (err != ErrorCode::None)
	{
		apiBuf.ErrorToString(err, errString, sizeof(errString));
		printf("(%s)", errString);
		throw err;
	}
}
void ApiBuf::EndRecord()
{
	err = apiBuf.EndRecordBufferChannel();
	if (err != ErrorCode::None)
	{
		apiBuf.ErrorToString(err, errString, sizeof(errString));
		printf("(%s)", errString);
		throw err;
	}
}
void ApiBuf::WaitBuffer(unsigned int ch)
{
	apiBuf.Wait(0);
}
void ApiBuf::SleepBuffer(unsigned int msec)
{
	apiBuf.Sleep(msec);
}
void ApiBuf::ExecuteApi(unsigned int ch)
{
	apiBuf.Execute(ch);
}
void ApiBuf::HaltApi(unsigned int ch)
{
	apiBuf.Halt(ch);
}