[![YecidMorenoUSP - ExoControl](https://img.shields.io/static/v1?label=YecidMorenoUSP&message=MY_LIBS&color=blue&logo=github)](https://github.com/YecidMorenoUSP/MY_LIBS)
[![alt](https://img.shields.io/github/license/YecidMorenoUSP/MY_LIBS?color=blue)](LICENSE.md)
![Windows](https://img.shields.io/badge/Windows-x64%20\|%20x86-blue?style=flat&logo=windows)

## UTILS_SHM

### How Use?
1. *Cargar bilioteca*
    ```c++
    #include <utilsSHM.h>
    ```
2. *Definir la estructura de datos*: de esta manera se crea una plantilla o modelo de como va a estar distribuida la memoria compartida, y el acceso a la misma, en el caso de acceder desde otros lenguejes de programacion, esto es un aspecto importante, para evitar escritas y lecturas erradas.
   
   ```c++
   typedef struct{
    int   Var1;
    float Var2;
    char  Var3[100];
   }SharedBuffer;   
   ```
3. ddd
   ```c++
   SHM::SHM_Object shmData;
   shmData.BUF_SIZE = sizeof(SharedBuffer);
   shmData.KEY_NAME =  (char*)"testSHM3";
   int error = 0;
   if((error = SHM::getSHM(&shmData)) != SHM::SHM_NO_ERROR){
      printf("Error : %d",error);
      return 0;
   }
   ```

4. *Compilar*: con el parametro **-I** adicione la ruta donde está ubicada la carpeta de la bibiloteca, y de manera opcional adicione la definición **DEBUG_SHM**, para visualizar en consola el estado de ejecucion.

    ```PS
    g++ main.cpp -o main.exe -I "${DEV2}/MY_LIBS/Utils_SHM" -D DEBUG_SHM
    ```

|Name                  | Value       | Info
|----                  | ----        |  ----
|SHM_NO_ERROR          | 0x10000000  | No existen errores
|SHM_ERROR_CREATE_FILE | 0x01000001  | Ha ocurrido un error crenado la memoria compartida, posiblemente ya fue creada o no posse los permisos necesarios para esta operacion, en caso de que sea global
|SHM_ERROR_CREATE_BUFF | 0x01000010  | Generalmente el tamanho del buffer no coincide con el tamanh de la memoria compartida
|SHM_ERROR_CREATE      | 0x01000000  | Indica que ocurrio un problema al momento de crear el bloque de memoria
|SHM_ERROR_OPEN_FILE   | 0x00100001  | No existe el archivo que está intentando abrir o no posee permisos
|SHM_ERROR_OPEN_BUFF   | 0x00100010  | Generalmente el tamanho del buffer no coincide con el tamanh de la memoria compartida
|SHM_ERROR_OPEN        | 0x00100000  | Ha habido un problema al momento de abrir la memoria compartida

## License

Released under [MIT](LICENSE) by [@YecidMorenoUSP](https://github.com/YecidMorenoUSP).
  

