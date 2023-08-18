#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 512 // size of a block of data
#define JPEG_HEADER_SIZE 4 // size of the JPEG header

int main(int argc, char *argv[]) {
    // Open the memory card for reading
    FILE *card = fopen("card.raw", "rb");
    if (card == NULL) {
        perror("Error opening memory card");
        return 1;
    }

    // Read the data from the memory card one block at a time
    unsigned char data[BLOCK_SIZE];
    int block_num = 0; // counter for the number of blocks read
    while (fread(data, BLOCK_SIZE, 1, card) == 1) {
        // Check if the first four bytes are a JPEG
        if (data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff && (data[3] & 0xf0) == 0xe0)
        {
            // Create a new file to hold the JPEG data
            char filename[256];
            sprintf(filename, "jpeg_%d.jpg", block_num);
            FILE *jpeg = fopen(filename, "wb");
            if (jpeg == NULL)
            {
                perror("Error creating JPEG file");
                return 1;
            }

            // Write the JPEG header to the file
            fwrite(data, JPEG_HEADER_SIZE, 1, jpeg);

            // Read and write the rest of the JPEG data
            int bytes_read;
            while ((bytes_read = fread(data, 1, BLOCK_SIZE, card)) > 0) {
                fwrite(data, bytes_read, 1, jpeg);
            }

            // Close the JPEG file
            fclose(jpeg);
        }

        block_num++;
    }

    // Close the memory card
    fclose(card);

    return 0;
}