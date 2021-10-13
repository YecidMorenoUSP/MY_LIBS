
#define DEBUG_COM
#include "../Utils_COM.h"

#include <iostream>

#include <time.h>


typedef struct{
    char A[2];
    char B[2];
    int  TimeGlobal;
    int  Time;
    int index;
}ToRec;

typedef struct{
        char type [8];
}ToSend;

int main(){

    COM::COM_Object comData;

    comData.buffRec_SIZE  = sizeof(ToRec);
    comData.buffSend_SIZE = sizeof(ToSend);

    comData.Parameter.BaudRate = 1000000;
    comData.Parameter.ByteSize = 8;
    comData.Parameter.StopBits = ONESTOPBIT;
    comData.Parameter.Parity = NOPARITY;
    comData.Parameter.fDtrControl = DTR_CONTROL_ENABLE;

    sprintf(comData.portName,"\\\\.\\COM15");

    ToSend * toSend = (ToSend *) comData.buffSend;
    ToRec  * toRec  = (ToRec  *) comData.buffRec;


    COM::openCOM(&comData);
    
    
    sprintf(toSend->type,COM_BEGIN_TX);
    COM::sendCOM(&comData);

    clock_t start = clock();

    for (size_t i = 0; i < 1000; i++)
    {
        if(i%80 == 0){
            sprintf(toSend->type,COM_ALIVE_TX);
            COM::sendCOM(&comData);
        }
        
        COM::recvCOM(&comData);
        // printf("\nVal : %s",toRec->A);
        // printf("\nVal : %s",toRec->B);
        printf("\nTime  : %d",toRec->Time);
        printf("\nTimeG : %d",toRec->TimeGlobal);
        printf("\nindex : %d",toRec->index);
    }

    clock_t stop = clock();

    double elapsed = double(stop - start) / CLOCKS_PER_SEC;

    sprintf(toSend->type,COM_END_TX);
    COM::sendCOM(&comData);

    COM::closeCOM(&comData);

    printf("\n\nEllapsep time %f",elapsed);

    Sleep(4000);

    return 0;
}