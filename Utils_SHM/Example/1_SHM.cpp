/*
    1_SHM.cpp para propositos generales
    
    #define DEBUG_SHM -> Para mostras los logs en la consola

    By Yecid Moreno : 2021
    git: https://github.com/YecidMorenoUSP

    Baseado de:
        Microsoft -> https://docs.microsoft.com/en-us/windows/win32/memory/creating-named-shared-memory

    Requerimientos:
        1. [V] Crear memoria compartida Windows
        2. [X] Crear memoria compartida Linux
*/

#define DEBUG_SHM
#include "../utilsSHM.h"

typedef struct{
    int A;
    float B;
    char C[20];

    void print(){
        printf("---------------\n");
        printf("A: %d\n",A);
        printf("B: %f\n",B);
        printf("C: %s\n",C);
        printf("---------------\n");
    }

    void setA(int A){
        this->A = A;
    }

}SharedBuffer;

int main()
{  
   // int x = !((SHM::SHM_ERROR_CREATE & 0x01000000)^0x01000000);
   
   SHM::SHM_Object shmData;
   shmData.BUF_SIZE = sizeof(SharedBuffer);
   shmData.KEY_NAME =  (char*)"testSHM3";
   int error = 0;
   if((error = SHM::getSHM(&shmData)) != SHM::SHM_NO_ERROR){
      printf("Error : %d",error);
      return 0;
   }

   SharedBuffer * sharedBuffer = (SharedBuffer *) shmData.pBuf;
   
   int index = sharedBuffer->A;
   printf("\n>> Su indice es : %d\n",index);

   for(int i = 0 ; i < 10 ; i++){
      sharedBuffer->A += 1;
      sharedBuffer->print();
      Sleep(1000 + index*10);
   }

   // _getch();

    SHM::closeSHM(&shmData);

   return 0;
}