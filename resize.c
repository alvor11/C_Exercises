#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./size infile outfile\n");
        return 1;
    }
    int size = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    bi.biWidth = bi.biWidth * size;
    bi.biHeight = bi.biHeight * size;
    int width_old = (bi.biWidth / size) * sizeof(RGBTRIPLE);// old width in byte
    int paddingOld = (4 - width_old % 4) % 4;
    int paddingNew = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + paddingNew) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + 54;
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    for (int i = 0, biHeight = abs(bi.biHeight / size); i < biHeight; i++)// iterate along line
    {
        for(int g = 0; g < size; g++) //reapet line
        {
            for (int j = 0; j < bi.biWidth / size; j++) //iterate along pixel
            {
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                for(int t = 0; t < size; t++)// reapet pixel
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            for (int k = 0; k < paddingNew; k++)
            {
                fputc(0x00, outptr);
            }
            if(g < size - 1) // Как правильно записать это условие используя тернарный оператор?
                fseek(inptr, -width_old, SEEK_CUR);
                
        }
    fseek(inptr, paddingOld, SEEK_CUR);
    }
    fclose(inptr);
    fclose(outptr);
    return 0;
}
