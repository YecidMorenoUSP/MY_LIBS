#define DEBUG_FILES
#include "../Utils_FILES.h"

#include <iostream>
#include <stdio.h>

#define TO_STR_CHAR(A) #A
#define COLOR_RED_TX(A)   TO_STR_CHAR(\x1B[31m##A\033[0m)
#define COLOR_GREEN_TX(A) TO_STR_CHAR(\x1B[32m##A\033[0m)
#define COLOR_PINK_TX(A)  TO_STR_CHAR(\x1B[35m##A\033[0m)

#define ERROR_ARGS "\n\
Formato Incorrecto, .\\ADDBLOCK.exe [NAME]\n\
    Donde : \n\
            [NAME] -> Debe ser una Unica palabra en mayuscula,\n\
                      y que no este definida en el proyecto. \n\
"
                  // [ BEGIN ]
#define ERROR_FILE  "[   %s   ] No se encontro el archivo %s \n",COLOR_RED_TX(X)
#define ERROR_OPEN  "[   %s   ] No se puede abrir el archivo %s \n",COLOR_RED_TX(X)
#define ERROR_EXIST "[   %s   ] Parece que el bloque %s ya Existe \n",COLOR_RED_TX(X)
#define ERROR_FIND  "[   %s   ] No se encontro la cadena %s \n",COLOR_RED_TX(X)

#define SUCESS_FILE  "[   %s   ] Archivo %s cargado correctamente \n",COLOR_GREEN_TX(V)
#define SUCESS_OPEN  "[   %s   ] Archivo %s cargado correctamente \n",COLOR_GREEN_TX(V)
#define SUCESS_EXIST "[   %s   ] El bloque %s puede ser agregado \n",COLOR_GREEN_TX(V)
#define SUCESS_FIND  "[   %s   ] Remplazado %s correctamente \n",COLOR_GREEN_TX(V)

#define STR_SEARCH_ADD_BLOCK_ENUM           std::string("BLKType_COUNT, //<ADD_BLOCK_ENUM>")
#define STR_SEARCH_ADD_BLOCK_INIT           std::string("//<ADD_BLOCK_INIT>")
#define STR_SEARCH_ADD_BLOCK_DEF_INCLUDE    std::string("//<ADD_BLOCK_DEFINE_NAME_AND_INCLUDE_H>")

#define STR_REPLACE_ADD_BLOCK_ENUM           "BLKType_"+NAME_BLOCK+",\n\t" + STR_SEARCH_ADD_BLOCK_ENUM
#define STR_REPLACE_ADD_BLOCK_INIT           "Block"+NAME_BLOCK+"_INIT();\t\t  \\\n\t\t\t\t\t " + STR_SEARCH_ADD_BLOCK_INIT
#define STR_REPLACE_ADD_BLOCK_DEF_INCLUDE    "#define name_of_object "+NAME_BLOCK+"\n#include \"BLOCKS/BLOCK_"+NAME_BLOCK+".h\"\n\n" +STR_SEARCH_ADD_BLOCK_DEF_INCLUDE

#define STR_NAME_TEMPLATE_OUT_H     "BLOCKS/BLOCK_DEFAULT.h"
#define STR_NAME_OF_FILE_OUT_H      "BLOCKS/BLOCK_"+NAME_BLOCK+".h"
#define STR_NAME_BLOCKS_H           "BLOCKS.h"
#define STR_NAME_BLOCKS_CPP         "BLOCKS.cpp"

std::string NAME_BLOCK = "NEW_BLOCK";



void beginProcess(){
    printf("\n[ BEGIN ] ADDBLOCK [%s] -> ExoControl\n",NAME_BLOCK.c_str());
}

void endProcess(int value = 0){

    if(value >= 0){
        printf("[  %s  ] Bloque \x1B[35m%s\033[0m agregado correctamente \n",COLOR_GREEN_TX(VVV),NAME_BLOCK.c_str());
    }else{
        printf("[  %s  ] Bloque \x1B[35m%s\033[0m no ha sido agregado \n",COLOR_RED_TX(XXX),NAME_BLOCK.c_str());
    }
    printf("[  END  ] ADDBLOCK [%s] -> ExoControl\n\n",NAME_BLOCK.c_str());
    exit(value);
}

std::string getSTR_and_close(const char * name){

    std::ifstream fileName = FILES::openR(name);
    if(fileName.fail()){
        printf(ERROR_FILE,name);
        endProcess(-1);
    }else printf(SUCESS_FILE,name);
    std::string str = FILES::getStr(&fileName);
    FILES::close(&fileName);

    return str;
}

void create_write_close(const char * name, std::string * str){
    std::ofstream out_file(name);
    if(out_file.fail()){
        printf(ERROR_OPEN,name);
        endProcess(-1);
    }else printf(SUCESS_OPEN,name);
    out_file << (*str); 
    out_file.close();
}

void verificarExistencia(std::string * str , std::string text){
    if(FILES::findStr(str,text) >= 0){
        printf(ERROR_EXIST,text.c_str());
        endProcess(-1);
    }else printf(SUCESS_EXIST,text.c_str());
}

int main(int argc, char const *argv[]){

    //Validar la entrada por argumentos

    if(argc != 2){
        beginProcess();
        printf(ERROR_ARGS);
        endProcess(-1);
    }
    
    // Inicio del programa
    NAME_BLOCK = argv[1];
    std::transform(NAME_BLOCK.begin(), NAME_BLOCK.end(),NAME_BLOCK.begin(), ::toupper);
    beginProcess();

    // Abrir y cerrar los archivos necesarios y guardar variables
        // BLOCKS_H
        std::string strBLOCKS_H = getSTR_and_close(STR_NAME_BLOCKS_H);

        // BLOCKS_CPP
        std::string strBLOCKS_CPP = getSTR_and_close(STR_NAME_BLOCKS_CPP);

        // BLOCK_DEFAULT_H
        std::string strBLOCK_DEFAULT_H = getSTR_and_close(STR_NAME_TEMPLATE_OUT_H);
    

    // Verificar que el bloque no exista en ninguno de los archivos
        verificarExistencia(&strBLOCKS_H,"BLKType_"+NAME_BLOCK);
        verificarExistencia(&strBLOCKS_CPP,"Block"+NAME_BLOCK+"_INIT();");
        verificarExistencia(&strBLOCKS_CPP,"#define name_of_object "+NAME_BLOCK);

    
    // Remplazar los elementos necesarios
    if(!FILES::replace(&strBLOCKS_H,STR_SEARCH_ADD_BLOCK_ENUM,STR_REPLACE_ADD_BLOCK_ENUM)){
        printf(ERROR_FIND,STR_SEARCH_ADD_BLOCK_ENUM.c_str());
        endProcess(-1);
    }else printf(SUCESS_FIND,STR_SEARCH_ADD_BLOCK_ENUM.c_str());

    if(!FILES::replace(&strBLOCKS_CPP,STR_SEARCH_ADD_BLOCK_INIT,STR_REPLACE_ADD_BLOCK_INIT)){
        printf(ERROR_FIND,STR_SEARCH_ADD_BLOCK_INIT.c_str());
        endProcess(-1);
    }else printf(SUCESS_FIND,STR_SEARCH_ADD_BLOCK_INIT.c_str());
    if(!FILES::replace(&strBLOCKS_CPP,STR_SEARCH_ADD_BLOCK_DEF_INCLUDE,STR_REPLACE_ADD_BLOCK_DEF_INCLUDE)){
        printf(ERROR_FIND,STR_SEARCH_ADD_BLOCK_DEF_INCLUDE.c_str());
        endProcess(-1);
    }else printf(SUCESS_FIND,STR_SEARCH_ADD_BLOCK_DEF_INCLUDE.c_str());

    // Preparar los arhivos de salida y actualizarlos
        // BLOCKS_H
        create_write_close(STR_NAME_BLOCKS_H,&strBLOCKS_H);
        create_write_close(STR_NAME_BLOCKS_CPP,&strBLOCKS_CPP);
        create_write_close((STR_NAME_OF_FILE_OUT_H).c_str(),&strBLOCK_DEFAULT_H);

    //Fin del programa
    endProcess(0);
    return 0;

    
}