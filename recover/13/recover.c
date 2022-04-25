#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2 || argv[1] == NULL)
    {
      printf("%s\n","Usage: ./recover IMAGE");
      return 1;
    }
    FILE* output = NULL;
    int counter = 0;
    BYTE buffer[512];
    char filename[8];
    FILE *input = fopen(argv[1], "r");
    while (fread(&buffer, sizeof(BYTE), 512, input) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0)== 0xe0)
        {
            if (output != NULL)
            {
              fclose(output);
            }
            sprintf(filename, "%03i.jpg", counter);
            output = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), 512, output);
            counter++;
        }
        else if (output != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, output);
        }
    }
    fclose(input);
    fclose(output);
}