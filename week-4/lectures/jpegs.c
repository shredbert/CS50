#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char** argv)
{
    // Ensure filename given as arg
    if (argc != 2)
    {
        printf("Give me some arrrrggggsssssss\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");

    // Check file valid
    if (!file)
    {
        printf("Bad file!!!\n");
        return 1;
    }

    printf("Good file!!!\n");

    // Save first 3 bytes into memory
    BYTE bytes[3];
    fread(&bytes, sizeof(BYTE), 3, file);
    printf("%i\n", bytes[0]);
    printf("%i\n", bytes[1]);
    printf("%i\n", bytes[2]);

    // Check that first 3 bytes == ff, d8, & ff & print result
    if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff)
    {
        printf("That's probably a JPEG!!!\n");
    }
    else
    {
        printf("Definitely not a JPEG!!!\n");
    }

    // CLOSE FILE!!!
    fclose(file);
}
