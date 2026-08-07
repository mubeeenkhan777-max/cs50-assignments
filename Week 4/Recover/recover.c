#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open memory card
    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Buffer for one block
    uint8_t buffer[BLOCK_SIZE];

    // JPEG counter
    int file_count = 0;

    // Current JPEG file
    FILE *jpg = NULL;

    // Read card one block at a time
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // Check if this block begins a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If a JPEG is already open, close it
            if (jpg != NULL)
            {
                fclose(jpg);
            }

            // Create filename
            char filename[8];
            sprintf(filename, "%03i.jpg", file_count);

            // Open new JPEG
            jpg = fopen(filename, "w");

            // Increase file number
            file_count++;
        }

        // If a JPEG is open, write this block to it
        if (jpg != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, jpg);
        }
    }

    // Close last JPEG
    if (jpg != NULL)
    {
        fclose(jpg);
    }

    // Close memory card
    fclose(card);

    return 0;
}
