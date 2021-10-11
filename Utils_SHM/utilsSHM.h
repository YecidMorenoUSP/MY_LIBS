#pragma once

/*
    UtilsSHM.h para propositos generales
    
    #define DEBUG_SHM -> Para mostras los logs en la consola

    By Yecid Moreno : 2021
    git: https://github.com/YecidMorenoUSP

    Baseado de:
        Microsoft -> https://docs.microsoft.com/en-us/windows/win32/memory/creating-named-shared-memory

    Requerimientos:
        1. [V] Crear memoria compartida Windows
        2. [X] Crear memoria compartida Linux
*/

#include <stdio.h>
#include <conio.h>

// #define DEBUG_SHM
void  SHM_DEBUG_LOG( char const* const _Format,...){
        #if defined(DEBUG_SHM)
            printf(_Format);
        #endif // DEBUG_SHM    
}


#pragma comment(lib, "user32.lib")

#define SHM_BUF_SIZE 256
#define SHM_KEY      "0x00000001\0"

namespace SHM{

    enum SHM_ERROR{
        SHM_NO_ERROR          = 0x10000000,
        SHM_ERROR_CREATE      = 0x01000000,
        SHM_ERROR_CREATE_FILE = 0x01000001,
        SHM_ERROR_CREATE_BUFF = 0x01000010,
        SHM_ERROR_OPEN        = 0x00100000,
        SHM_ERROR_OPEN_FILE   = 0x00100001,
        SHM_ERROR_OPEN_BUFF   = 0x00100010,
    };

    typedef struct{
            char * pBuf;
            void * hMapFile;

            char * KEY_NAME =  (char*) SHM_KEY;
            int BUF_SIZE    =  SHM_BUF_SIZE;

    }SHM_Object;

    static int getSHM(SHM_Object * shmData);
    static int createSHM(SHM_Object * shmData);
    static int openSHM(SHM_Object * shmData);
    static int closeSHM(SHM_Object * shmData);

}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    
    #include <windows.h>
    #include "utilsSHM_WINDOWS.h"

#else

    #error Falta implementacion para Linux y MacOS

#endif