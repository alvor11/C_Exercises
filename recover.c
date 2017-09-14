#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr,"Usage: ./recover image\n");
        return 1;
    }
    FILE *infile = fopen(argv[1], "r");
    //if (infile == NULL)
    //{
       //return 2;
    //}
    uint8_t buf[512];
    char fname[8];
    int counter = 0;
    FILE *img = NULL;
    while (!feof(infile)) 
    {
        fread(buf, 512, 1, infile);
        if (buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff && (buf[3] & 0xf0) == 0xe0) 
        {
            if (img != NULL)  // close opened jpg
            {
                fclose(img);
            }
            sprintf(fname, "%i%i%i.jpg", counter / 100, counter / 10, counter % 10);
            counter++;
            img = fopen(fname, "w"); // open new jpeg
        }
        if (counter > 0)// write jpeg
            {
                fwrite(buf, 512, 1, img);
            }
    }
    if(img != NULL)
    {
        fclose(img);
    }
    fclose(infile);
}

