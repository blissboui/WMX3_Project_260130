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
        // 서보 on
        handler.ServoOn(0, 1);
        // 프로파일 생성
        handler.SetPVTProfile(0);
        handler.SetMovProfile(1);
        // 모션 설정
        handler.SetApiBufCutMotion();
        statusFlag = 1;
        while (1)
        {
            bitNum = handler.GetStatusBit();

            if (bitNum == 1 && statusFlag == 1)
            {
                handler.ExecuteApi(0);
                statusFlag = 2;
                handler.ShowStatus(bitNum);
            }

            else if (bitNum == 2 && statusFlag == 2)
            {
                handler.HaltApi(0);
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
    handler.ServoOff(0, 1);
    handler.EndSetup();
    return 0;
}

