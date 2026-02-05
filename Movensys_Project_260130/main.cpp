/*
    260130 시작
    
*/
#include "Handler.h"

int main()
{
    Handler handler;
    bool flag = true;

    while (1)
    {
        try
        {
            if (flag)
            {
                // 디바이스 생성, 통신 시작
                handler.StartSetup();
                // 프로파일 생성
                handler.SetPVTProfile();
                // 서보 on
                handler.ServoOn();
                // 모션 구동
                handler.StartCutMotion();
            //handler.StartMotion();
                flag = false;
            }
            if (handler.GetStorBit())
                handler.buffer.Halt(0);
        }
        catch (int err)
        {
            // 예외 발생 시 초기화 후 에러코드 출력
            printf(" Error : %d", err);
            cin.get();
            handler.StopServo();
            handler.StopSetup();
            flag = true;
            system("cls");
            continue;
        }
    }
    handler.StopServo();
    handler.StopSetup();
    printf("Exit \n");
    return 0;

}

