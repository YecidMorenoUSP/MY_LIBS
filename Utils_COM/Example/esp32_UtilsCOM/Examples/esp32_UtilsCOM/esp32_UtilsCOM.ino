//#define DEBUG_COM
#include "/../Utils_COM.h"

typedef struct {
  char A[2];
  char B[2];
  int TimeGlobal;
  int Time;
  int index;
} ToSend;

typedef struct {
  char Type [10];
} ToRec;

ToSend * toSend;
ToRec  * toRecv;
COM::COM_Object comData;

int _T1 = 0;
int _T0 = 0;
int SENDING = 0;

void setup() {
  Serial.begin(1000000);

  COM_DEBUG_LOG("\nHola  %d \n ", 10);

  comData.baudRate = 1000000;
  comData.buffRec_SIZE  = sizeof(ToRec);
  comData.buffSend_SIZE = sizeof(ToSend);

  memmove(&toSend, &comData.buffSend, sizeof(ToSend));
  memmove(&toRecv, &comData.buffRec , sizeof(ToRec ));

  sprintf(toSend->A, "J");
  sprintf(toSend->B, "P");
  toSend->index = 0;

  _T0 = millis();

}

void loop() {

  serialEvent();

  if ((SENDING--) > 0) {

    toSend->A[0] = toSend->A[0] + 1;
    toSend->B[0] = toSend->B[0] + 1;
    toSend->Time  = millis() - _T1;
    toSend->TimeGlobal  = millis() - _T0;
    toSend->index = toSend->index + 1;

    Serial.write(comData.buffSend, sizeof(ToSend));

    delay(3);

  }

}


void serialEvent() {
  while (Serial.available() >= sizeof(ToRec)) {

    Serial.readBytes(comData.buffRec, sizeof(ToRec));

    if (isCommand(toRecv->Type, COM_BEGIN_TX)) {
      COM_DEBUG_LOG("\nHola Wuapo");
    } else if (isCommand(toRecv->Type, COM_END_TX)) {
      COM_DEBUG_LOG("\nChao Wuapo");
    } else if (isCommand(toRecv->Type, COM_ALIVE_TX)) {
      COM_DEBUG_LOG("\nAqui estoy Wuapo");
    } else {
      COM_DEBUG_LOG("\nQue quiere loca ????   :    ");
      COM_DEBUG_LOG("%s",toRecv->Type);
    }

    

    return;
    SENDING = 100;
    sprintf(toSend->A, "J");
    sprintf(toSend->B, "P");
    //    toSend->index = 0;
    _T1 = millis();

  }
}
