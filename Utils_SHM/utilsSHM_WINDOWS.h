#pragma once

#include "utilsSHM.h"

namespace SHM{

        static int getSHM(SHM_Object * shmData){
            if( openSHM(shmData) != SHM_NO_ERROR){
                if(createSHM(shmData) != SHM_NO_ERROR){
                    return SHM_ERROR_CREATE|SHM_ERROR_OPEN;
                }
            }
            return SHM_NO_ERROR;
        }

        static int createSHM(SHM_Object * shmData){
            
            shmData->hMapFile = CreateFileMapping(
                        INVALID_HANDLE_VALUE,    // use paging file
                        NULL,                    // default security
                        PAGE_READWRITE,          // read/write access
                        0,                       // maximum object size (high-order DWORD)
                        shmData->BUF_SIZE,                // maximum object size (low-order DWORD)
                        shmData->KEY_NAME);                 // name of mapping object

            if (shmData->hMapFile == NULL)
            {
                SHM_DEBUG_LOG("Could not create file mapping object (%d).\n", GetLastError());
                return SHM_ERROR_CREATE_FILE;
            }
            shmData->pBuf = (char *) MapViewOfFile(shmData->hMapFile,   // handle to map object
                                FILE_MAP_ALL_ACCESS, // read/write permission
                                0,
                                0,
                                shmData->BUF_SIZE);

            if (shmData->pBuf == NULL)
            {
                SHM_DEBUG_LOG("Could not map view of file (%d).\n",GetLastError());

                CloseHandle(shmData->hMapFile);

                return SHM_ERROR_CREATE_BUFF;
            }

            return SHM_NO_ERROR;
        }


        static int openSHM(SHM_Object * shmData){

            shmData->hMapFile = OpenFileMapping(
                            FILE_MAP_ALL_ACCESS,   // read/write access
                            FALSE,                 // do not inherit the name
                            shmData->KEY_NAME);               // name of mapping object

            if (shmData->hMapFile == NULL)
            {
                SHM_DEBUG_LOG(("Could not open file mapping object (%d).\n"),
                    GetLastError());
                return SHM_ERROR_OPEN_FILE;
            }

            shmData->pBuf = (char *) MapViewOfFile(shmData->hMapFile, // handle to map object
                        FILE_MAP_ALL_ACCESS,  // read/write permission
                        0,
                        0,
                        shmData->BUF_SIZE);

            if (shmData->pBuf == NULL)
            {
                SHM_DEBUG_LOG(("Could not map view of file (%d).\n"),
                    GetLastError());

                CloseHandle(shmData->hMapFile);

                return SHM_ERROR_OPEN_BUFF;

            }

            return SHM_NO_ERROR;
        }

        static int closeSHM(SHM_Object * shmData){
            UnmapViewOfFile(shmData->pBuf);
            CloseHandle(shmData->hMapFile);
            return SHM_NO_ERROR;
        }


    }
