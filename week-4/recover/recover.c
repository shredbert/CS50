#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
 
    FILE *data = fopen(argv[1], "r");
    if (!data)
    {
        printf("Bad filename\n");
        return 2;
    }

    // TODO: Iterate through files, looking for 0xff, 0xd8, 0xff, & (buffer[3]
    // & 0xf0 == 0xe0), & tracking #
    int files = 0;

    // TODO: Ensure enough memory for string to represent entire filename ->
    // i.e., 7 chars
    char *filename = malloc(sizeof(char) * 7);
    free(filename);

    // TODO: Iterate using return val of fread() -> i.e., returning 512 bytes

    // TODO: Read 512 bytes at a time into buffer

    // TODO: Check for 0xff, 0xd8, 0xff, & (buffer[3] & 0xf0 == 0xe0), &
    // tracking #

    // TODO: Close/write accordingly if new JPEG

    // TODO: Keep writing if same JPEG

    // TODO: When found, increment files & write name as '###.jpg' using
    // sprintf(filename, "%03i.jpg", 2);

    // TODO: Use fopen() to open new file to write with stored filename
    
    // TODO: Use fwrite() to write new JPEG files in current directory

    // TODO: Close all files
}
