[![YecidMorenoUSP - ExoControl](https://img.shields.io/static/v1?label=YecidMorenoUSP&message=MY_LIBS&color=blue&logo=github)](https://github.com/YecidMorenoUSP/MY_LIBS)
[![alt](https://img.shields.io/github/license/YecidMorenoUSP/MY_LIBS?color=blue)](LICENSE.md)
![Windows](https://img.shields.io/badge/Windows-x64%20\|%20x86-blue?style=flat&logo=windows)

## UTILS_COM

### How Use? Client
### How Use? Server
1. Definiciones del precomplilador
    ```c++
    #define SERVER_TCP_SEND_FIRST
    #define DEBUG_SERVER_TCP
    #define DEFAULT_BUFLEN 64
    ```
2. Cargar la biblioteca
   ```c++
   #include <ServerTCP.h>
   ```
3. Crear las plantillas para los buffer de entrada y salida
4. Configurar la interfaz Serial: 
5. Conectarse a un dispositivo
6. Enviar un buffer
7. Recibir un buffer
8. Cerrar conexion   

### Commands
### How Install?
1. Guardar la carpeta `Utils_TCP` en una ubicacion conocida
2. *Compilar*: con el parametro **-I** adicione la ruta donde está ubicada la carpeta de la bibiloteca.
    ```PS
    g++ server.cpp -o server.exe -I "${DEV2}/MY_LIBS/Utils_TCP"
    g++ client.cpp -o client.exe -I "${DEV2}/MY_LIBS/Utils_TCP"

    start .\server.exe
    start .\client.exe

    ```
3. *Debug*: De manera opcional adicione la definición **DEBUG_SERVER_TCP** o **DEBUG_CLIENT_TCP**, para visualizar en consola el estado de ejecucion.
    ```PS
    g++ ... -D DEBUG_SERVER_TCP
    g++ ... -D DEBUG_CLIENT_TCP
    ```

### Errors


## License
Released under [MIT](LICENSE) by [@YecidMorenoUSP](https://github.com/YecidMorenoUSP).
  

