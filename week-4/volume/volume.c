// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    // Store # of items read to track place in header
    int items = 0;
    // Store header in array before writing
    uint8_t header[HEADER_SIZE];
    // Read header
    while(items < HEADER_SIZE)
    {
        // Copy each header byte to output file
        items += fread(&header, sizeof(uint8_t), 1, input);
    }

    for (int i = 0; i < HEADER_SIZE; i++)
    {
        printf("%i\n", header[i]);
    }

    // // Read samples from input file and write updated data to output file
    // // Store each item temporarily
    // int16_t buffer;
    // // Read 1 at a time
    // while (fread(&header, sizeof(int16_t), 1, input))
    // {
    //     fwrite(&header, sizeof(int16_t), 1, input);
    // }

    // Close files
    fclose(input);
    fclose(output);

    // printf("Bytes written:\n");
    // FILE *test_in = fopen("./input.wav", "r");
    // FILE *test_out = fopen("./output.wav", "r");
    // uint8_t print_byte_in, print_byte_out;
    // for (int i = 0; i < HEADER_SIZE;
    //         i++,
    //         fread(&print_byte_in, sizeof(uint8_t), 1, test_in)
    //         // fread(&print_byte_out, sizeof(uint8_t), 1, test_out)
    //     )
    // {
    //     printf("in: %i, out: %i\n", print_byte_in, header[i]);
    //     // if (print_byte_in != print_byte_out)
    //     // {
    //     //     printf("Didn't write header correctly!\n");
    //     // }
    // }
    // fclose(test_in);
    // fclose(test_out);
}
