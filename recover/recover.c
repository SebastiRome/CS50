#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

// Number of bytes in a bloc of a jpeg
const int jpeg_bloc = 512;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover XXXX.raw\n");
        return 1;
    }

    // Open input file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file");
        return 2;
    }

    //An uninitialize file pointer to use to output data gotten from input file
    FILE *output = NULL;

    char *filename = malloc(8 * sizeof(char));

    // Read samples from input file and write updated data to output file
    int count_image = 0;
    BYTE buffer[jpeg_bloc];
    while (fread(&buffer, sizeof(BYTE), jpeg_bloc, input) == jpeg_bloc)
    {
        // Check if the first four bytes are a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", count_image);
            output = fopen(filename, "w");
            count_image++;
        }
        if (output != NULL)
        {
            fwrite(&buffer, sizeof(BYTE), jpeg_bloc, output);
        }
    }

    // Close files
    free(filename);
    fclose(input);
    fclose(output);

    return 0;
}

