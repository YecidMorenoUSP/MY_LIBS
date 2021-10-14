// #define DEBUG_FILES
// #include "../Utils_FILES.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

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

    void replace(std::string * str,std::string strSearch , std::string strReplace){
        size_t pos = str->find(strSearch);
        str->replace(pos, string(strSearch).length(), strReplace);
    }

    std::string getStr(std::ifstream * file){
        std::ostringstream text;
        text << file->rdbuf();
        return  text.str();
    }

};

int main(){
    printf("\n[ BEGIN ] Utils_FILES Example\n");

    std::ifstream originFile = FILES::openR("text.txt");

    std::string str = FILES::getStr(&originFile);

    FILES::replace(&str,
                  "BLKType_COUNT, //<ADD_BLOCK_ENUM>",
                  "BLKType_ADDED,\n\tBLKType_COUNT, //<ADD_BLOCK_ENUM>");


    FILES::close(&originFile);

    std::ofstream out_file("text2.txt");
    out_file << str; 
    out_file.close();

    printf("\n[  END  ] Utils_FILES Example\n\n");
    return 0;
}