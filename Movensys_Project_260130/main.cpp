/*
    260130 시작

*/
#include "Handler.h"

int main()
{
    Handler handler;
    int statusFlag = 0;
    int bitNum = 0;
    try
    {
        // 디바이스 생성, 통신 시작
        handler.StartSetup();
        // 프로파일 생성
        handler.SetPVTProfile();
        // 서보 on
        handler.ServoOn();
        // 모션 설정
        handler.SetCutMotion();
        statusFlag = 1;
        while (1)
        {
            //handler.StartMotion();
            bitNum = handler.GetStatusBit();

            if (bitNum == 1 && statusFlag == 1)
            {
                handler.buffer.Execute(0);
                statusFlag = 2;
                handler.ShowStatus(bitNum);
            }

            else if (bitNum == 2 && statusFlag == 2)
            {
                handler.buffer.Halt(0);
                statusFlag = 1;
                handler.ShowStatus(bitNum);
            }

            else if (bitNum == 3)
            {
                handler.ShowStatus(bitNum);
                break;
            }

            if (bitNum != 0)
                handler.ResetStatusBit();
        }
    }
    catch (int err)
    {
        // 예외 발생 시 에러코드 출력
        printf(" Error : %d", err);
        cin.get();
    }
    handler.StopServo();
    handler.EndSetup();
    return 0;
}

