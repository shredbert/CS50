#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Bad args!!!\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f)
    {
        printf("Bad file!!!\n");
        return 2;
    }

    BYTE *b = malloc(sizeof(BYTE) * 3);
    fread(b, sizeof(BYTE), 3, f);
    fclose(f);

    printf("Bytes: %i, %i, %i\n", *b, *(b + 1), *(b + 2));
    
    if (*b != 0xff || *(b + 1) != 0xd8 || *(b + 2) != 0xff)
    {
        printf("Not JPEG!!!\n");
    }
    else
    {
        printf("Maybe JPEG!!!\n");
    }

    free(b);
}
