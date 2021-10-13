//#define DEBUG_COM
#include "Utils_COM.h"

// [I] IMPORTANTE

    typedef struct {
      char A[2];
      char B[2];
      int TimeGlobal;
      int Time;
      int index;
    } ToSend;
    
    typedef struct {
      char Type [8];
    } ToRec;

    typedef struct {
      char rest[4];
      int32_t Type [1];
    } ToRec2;
    
    ToSend * toSend;
    ToRec  * toRecv;
    ToRec2   toRec2;
    COM::COM_Object comData;

// [F] IMPORTANTE


int _T1 = 0;
int _T0 = 0;
int SENDING = 0;
bool isRUNNING = false;

void setup() {
  
  // [I] IMPORTANTE
  
      comData.baudRate = 1000000;
      comData.buffRec_SIZE  = sizeof(ToRec);
      comData.buffSend_SIZE = sizeof(ToSend);

      //toSend  =  (ToSend*) &comData.buffSend;
      //toRecv  =  (ToRec*)  &comData.buffRec;
      
      memmove(&toSend , &comData.buffSend ,  sizeof(ToSend));
      memmove(&toRecv , &comData.buffRec  ,  sizeof(ToRec ));
    
      COM::initCOM(&comData);

      COM_DEBUG_LOG("\n size of ToSend %d",sizeof(ToSend));
      COM_DEBUG_LOG("\n size of ToRec %d",sizeof(ToRec));
      COM_DEBUG_LOG("\n size of ToRec2 %d",sizeof(ToRec2));

  // [F] IMPORTANTE

  sprintf(toSend->A, "J");
  sprintf(toSend->B, "P");
  toSend->index = 0;

  _T0 = millis();

}

void loop() {
  // [I] IMPORTANTE
        COM::Update();
  // [F] IMPORTANTE

  if ((SENDING--) > 0 && isRUNNING) {

    
    toSend->Time  = millis() - _T1;
    toSend->TimeGlobal  = millis() - _T0;
    toSend->index = toSend->index + 1;

    Serial.write(comData.buffSend, sizeof(ToSend));

    delay(3);

  }

}

void COM_Callback(){
  
   if (isCommand(toRecv->Type, COM_BEGIN_TX)) {
      COM_DEBUG_LOG("\nHola Wuapo");
      toSend->index = 0;
      SENDING = 100;
      isRUNNING = true;
      _T0 = millis();
      _T1 = millis();
    } else if (isCommand(toRecv->Type, COM_END_TX)) {
      COM_DEBUG_LOG("\nChao Wuapo");
      SENDING = 0;
      isRUNNING = false;
      _T1 = millis();
    } else if (isCommand(toRecv->Type, COM_ALIVE_TX)) {
      SENDING = 100;
      _T1 = millis();
      toSend->A[0] = toSend->A[0] + 1;
      toSend->B[0] = toSend->B[0] + 1;
      COM_DEBUG_LOG("\nAqui estoy Wuapo");
    } else {
      COM_DEBUG_LOG("\nQue quiere loca ????   :    ");
      COM_DEBUG_LOG("%s",toRecv->Type);
      //COM::ReadBytesSync(&toRec2,sizeof(ToRec));   
      //Serial.printf("\n REC2 %c %c %c %c %d",toRec2.rest[0],toRec2.rest[1],toRec2.rest[2],toRec2.rest[3],toRec2.Type[0]);
    }
}
