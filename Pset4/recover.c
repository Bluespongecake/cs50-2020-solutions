#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define blocksize 512

int main(int argc, char *argv[])
{
    
    long inFileSize; //found out how to get the size of a file on cplusplus.com on the fread explaination page
    long resultant;
    typedef uint8_t BYTE;
    int picnum = 0;
    char picname[8];
    
    FILE *infile;
    if (argc > 2 || argc < 2)
    {
        printf("Usage: recover <data>\n");
        return 1;
    }
    
    infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("could not open requested file\n");
        return 1;
    }
    
    int jpeg_start[3] = 
    {
        0xff,
        0xd8,
        0xff,
    };
    
    fseek(infile, 0, SEEK_END);
    inFileSize = ftell(infile);
    rewind(infile);
    
    BYTE *buffer = malloc(sizeof(BYTE) * blocksize);
    
    printf("Infile size: %li kilobytes\n", inFileSize / 1024);
    printf("Infile Blocks: %f\n", (float)inFileSize / 512);

    int num = 0;
    FILE *outfile;

    while (fread(buffer, blocksize, 1, infile))
    {
        //found the start of a new image by matching the first 4 bytes in the block
        if (buffer[0] == jpeg_start[0] && 
            buffer[1] == jpeg_start[1] && 
            buffer[2] == jpeg_start[2] && 
            (buffer[3] & 0xe0) == 0xe0)
        {
            if (picnum > 0)
            {
                fclose(outfile);                                    //if there is a previous file open, close it
            }
            
            sprintf(picname, "%03d.jpg",
                    picnum);                                        //Write a name for the picture. idk why but this took a bloody long time to figure out
            outfile = fopen(picname, "a");                          //open new file with new name
            picnum++;  
            fwrite(buffer, blocksize, 1, outfile);                  //write to the new file
            
        }
        else if (picnum > 0)                                        //if at least one file has been found
        {
            fwrite(buffer, blocksize, 1, outfile);                  //then write to the current open file
        }
        
        num++;
    }
    printf("\n%i blocks searched\n%i jpgs recovered\n", num, picnum - 1);
    
    
    //free up all that space and stuff
    fclose(infile);
    free(buffer);
    
    return 0;
}
