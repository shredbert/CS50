#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Create BYTE datatype for easier access
typedef uint8_t BYTE;
 
int main(int argc, char *argv[])
{
    // One arg only
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
 
    // Open & check file valid
    FILE *data = fopen(argv[1], "r");
    if (!data)
    {
        printf("Bad filename\n");
        return 1;
    }

    // Track # of files for naming & allocate space for name string
    int files = 0;
    char *filename = malloc(sizeof(char) * 8);
    BYTE buffer[512];

    // TODO: Iterate in 512 byte blocks into buffer
    while (fread(&buffer, sizeof(BYTE), 512, data) == 512)
    {
        // TODO: Search bytes for headers 0xff, 0xd8, 0xff, &
        // (buffer[3] & 0xf0) == 0xe0, & track # of files
        // If true, start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // When found & first file, change filename & open for writing
            sprintf(filename, "%03i.jpg", files);
            printf("JPEG found!!!\n%s\n", filename);
            FILE *new = fopen(filename, "w");
            if (!new)
            {
                printf("Error writing file\n");
                return 1;
            }

            // TODO: If not first file, close prev & start next
            // To check, create vars for prev & crnt files & compare?
            // TODO: Write each block until next header
            // TODO: Check if fread() returning 512 -- if not, no more images?
            // Check length of buffer[] -- how???
            // Use fwrite() to write new JPEG files in current directory
            // fwrite(&buffer, sizeof(BYTE), 512, new);
            // fclose(new);
            // TODO: Reset to new block when found again
            // Increment files for next
            files++;
        }
        // TODO: If not new JPEG, keep writing
        else
        {
            // TODO: Check if started writing yet? (else will write vals before
            // JPEG found
        }
    }
    
    // TODO: Close all files & free memory
    free(filename);
    fclose(data);
}
