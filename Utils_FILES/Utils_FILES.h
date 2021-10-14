#pragma once

/*
    Utils_FILES.h para propositos generales
    
    #define DEBUG_FILES -> Para mostras los logs en la consola

    By Yecid Moreno : 2021
    git: https://github.com/YecidMorenoUSP

    Requerimientos:
        1. [X]
*/

// #define DEBUG_FILES

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

void  FILES_DEBUG_LOG( char const* const _Format,...){
        #if defined(DEBUG_FILES)
            printf(_Format);
        #endif // DEBUG_COM    
}

namespace FILES{
    std::ifstream openR(std::string nameFile){
        std::ifstream in_file(nameFile);
        return in_file;
    }

    std::ofstream openW(std::string nameFile){
        std::ofstream out_file(nameFile);
        return out_file;
    }

    void close(std::ifstream * file){
        file->close();
    }

    int findStr(std::string * str,std::string strSearch){
        int pos = str->find(strSearch);
        return pos;
    }

    bool replace(std::string * str,std::string strSearch , std::string strReplace){
        int pos = findStr(str,strSearch);
        if(pos<0) return false;

        str->replace(pos, std::string(strSearch).length(), strReplace);
        return true;
    }

    std::string getStr(std::ifstream * file){
        std::ostringstream text;
        text << file->rdbuf();
        return  text.str();
    }

};