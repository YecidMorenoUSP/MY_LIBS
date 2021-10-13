#pragma once

/*
    UtilsCOM.h para propositos generales
    
    #define DEBUG_COM -> Para mostras los logs en la consola

    By Yecid Moreno : 2021
    git: https://github.com/YecidMorenoUSP

    Baseado de:
        SerialPort.h

    Requerimientos:
        1. [X]
*/


#include <stdio.h>
#include <conio.h>
#include <windows.h>

// #define DEBUG_COM
void  COM_DEBUG_LOG( char const* const _Format,...){
        #if defined(DEBUG_COM)
            printf(_Format);
        #endif // DEBUG_COM    
}

#define ARDUINO_WAIT_TIME 500
#define COM_BUF_SIZE 256

namespace COM{

    enum COM_ERROR{
        COM_NO_ERROR          = 0x01000000,
        COM_ERROR             = 0x00100000,
    };

    typedef struct{

        int CONECTED = false;

        char portName [20] = "COM15";

        char * buffRec  = new char[COM_BUF_SIZE];
        char * buffSend = new char[COM_BUF_SIZE];
    
        void * handler;

        int buffRec_SIZE     =  COM_BUF_SIZE;
        int buffSend_SIZE    =  COM_BUF_SIZE;

        DCB Parameter = {0};

        COMSTAT status;
        DWORD errors;

    }COM_Object;

    static int openCOM(COM_Object  * comData);
    static int closeCOM(COM_Object * comData);
    static int sendCOM(COM_Object  * comData);
    static int recvCOM(COM_Object  * comData);

};

#include "Utils_COM.cpp"