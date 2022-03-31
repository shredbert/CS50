#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("More args plz!!!\n");
        return 1;
    }

    // Read into memory
    FILE *f = fopen(argv[1], "r");

    if (!f)
    {
        printf("Bad file!!!\n");
        return 2;
    }

    // Create array of bytes to store
    BYTE b[3];
    // Read first 3 bytes
    fread(b, sizeof(BYTE), 3, f);

    if (b[0] != 0xff || b[1] != 0xd8 || b[2] != 0xff)
    {
        printf("Not JPEG!!!\n");
    }
    else
    {
        printf("Maybe JPEG???\n");
    }
}
