#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
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

    uint8_t buffer[512];
    FILE *img = NULL;
    int jpeg_count = 0;

    // Read 512-byte blocks
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Check for JPEG header
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If already writing a JPEG, close it
            if (img != NULL)
            {
                fclose(img);
            }

            // Create new JPEG filename
            char filename[8];
            sprintf(filename, "%03i.jpg", jpeg_count);
            jpeg_count++;

            // Open new JPEG file
            img = fopen(filename, "w");
        }

        // If currently writing a JPEG, write the block
        if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }

    // Close remaining files
    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);
    return 0;
}