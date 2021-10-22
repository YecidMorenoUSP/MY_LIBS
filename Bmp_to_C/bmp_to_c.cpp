#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <string>

#include  "../Utils_FILES/Utils_FILES.h"

char *bmp_to_C(char *name)
{
    std::ofstream out = FILES::openW(std::string(name)+".h");

    char c_out[100];

    FILE *fp;
    uint8_t buf[16];
    static char array[100];
    char *p;
    int n, i, len = strlen(name);
    long sz;
    strcpy(array, name);
    fp = fopen(name, "rb");
    if (fp == NULL)
        return NULL;

    fseek (fp, 0, SEEK_END);   // non-portable
    sz = ftell (fp);
    fseek (fp, 0, SEEK_SET);   // non-portable

    array[len - 4] = '_'; 
    printf("const unsigned char PROGMEM %s[%ld] = {\n", array, sz);
    sprintf(c_out,"const unsigned char PROGMEM %s[%ld] = {\n", array, sz);
    out<<c_out;
    do {
        n = fread(buf, 1, 16, fp);
        for (i = 0; i < n; i++) {
            printf("0x%02X,", buf[i]);
            sprintf(c_out,"0x%02X,", buf[i]);
            out<<c_out;
        }
        printf("\n");
        out<<"\n";
    }while(n > 0);
    printf("};\n");
    sprintf(c_out,"};\n");
    out<<c_out;
    fclose(fp);

    out.close();
    
    printf("%s",c_out);

    return array;
}

int main(int argc, char **argv)
{
    while (--argc) {
        bmp_to_C(*++argv);
    }
    return (0);
}