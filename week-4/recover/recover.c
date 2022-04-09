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

    // Track # of files for naming & whether have started writing yet
    int files = 0, jpeg_fnd = 0;
    // Allocate space for filename string
    char *filename = malloc(sizeof(char) * 8);
    // Put block size in var
    int BLOCK_SIZE = 512;
    // Buffer for reading images
    BYTE buffer[BLOCK_SIZE];

    // Iterate over bytes the size of the img blocks
    while (fread(&buffer, sizeof(BYTE), BLOCK_SIZE, data) == BLOCK_SIZE)
    {
        // Check for start of JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // Turn to true--avoid first bytes
            jpeg_fnd = 1;
            // Set new filename
            sprintf(filename, "%03i.jpg", files);
            // Increment # of files for next go around--won't impact current
            // name
            files++;
            // Open file for writing
            FILE *new_img = fopen(filename, "w");
            if (!new_img)
            {
                printf("Error opening write file for image %i\n", files);
                return 1;
            }
            // Write & close
            fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, new_img);
            fclose(new_img);
        }
        // If not new JPEG, append
        else
        {
            if (jpeg_fnd)
            {
                FILE *new_img = fopen(filename, "a");
                if (!new_img)
                {
                    printf("Error opening write file for image %i\n", files);
                    return 1;
                }
                fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, new_img);
                fclose(new_img);
            }
        }
    }
    
    // Close all files & free memory
    free(filename);
    fclose(data);
}
