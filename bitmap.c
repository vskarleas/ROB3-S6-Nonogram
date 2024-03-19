// #############################################################################
// # File bitmap.c
// # UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bitmap.h"

/* Writing a PBM file for BitMap image creation */
void write_pbm_file(int width, int height, int **array, char *file_name, char *repository)
{
    char *no_extension = strtok(file_name, ".");
    char *filename = malloc(strlen(repository) + strlen(no_extension) + 4);
    strcpy(filename, repository);                                
    strcat(filename, file_name);                                        
    strcat(filename, ".pbm");      

    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        exit(-8);
    }

    // Write PBM header
    fprintf(fp, "P1\n%d %d \n", width, height);

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            const char pixel = array[x][y] ? '0' : '1'; // Map non-zero values to '0', zero to '1' because that's the format of PBM while respecting the constants.h file
            fputc(pixel, fp);
        }
        fputc('\n', fp);
    }

    fclose(fp);
}


/* It writes an EPS file for AdobeVector image creation - postscript */
void create_postscript_file_v1_3(int **pixels, char *file_name, int hauteur, int largeur)
{
    // Extension management
    char *no_extension = strtok(file_name, ".");
    char *with_extension = malloc(strlen(no_extension) + 8);
    strcpy(with_extension, no_extension);
    strcat(with_extension, "V1_3.eps"); // Concatenation

    // File management
    FILE *fptr;
    fptr = fopen(with_extension, "w");
    if (fptr == NULL)
    {
        printf("EPS File Error!\n");
        exit(1);
    }

    // File header
    fprintf(fptr, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fptr, "%%%%BoundingBox: 0 0 %d %d\n", largeur, hauteur); // Adjusted bounding box
    fprintf(fptr, "\n");

    // Iterate through the pixels array
    int is_contour_started = 0;
    for (int y = 0; y < hauteur; y++)
    {
        for (int x = 0; x < largeur; x++)
        {
            if (pixels[y][x] == 1)
            {
                if (!is_contour_started)
                {
                    fprintf(fptr, "%.0d %.0d moveto ", x, hauteur - y - 1); // Adjusted starting point
                    is_contour_started = 1;
                }
            }
            else
            {
                if (is_contour_started)
                {
                    fprintf(fptr, "%.0d %.0d lineto ", x - 1, hauteur - y); // Adjusted ending point
                    // fprintf(fptr, "fill\n");
                    is_contour_started = 0;
                }
            }
        }
        if (is_contour_started)
        {
            fprintf(fptr, "%.0d %.0d lineto ", largeur - 1, hauteur - y); // Close contour at end of row
            // fprintf(fptr, "fill\n");
            is_contour_started = 0;
        }
    }
    fprintf(fptr, "fill\n");

    fprintf(fptr, "\n");
    fprintf(fptr, "showpage\n");
    fclose(fptr);
    //free(with_extension);
}

void create_postscript_file_v2(int **pixels, char *file_name, int hauteur, int largeur)
{
    // Extension management
    char *no_extension = strtok(file_name, ".");
    char *with_extension = malloc(strlen(no_extension) + 6);
    strcpy(with_extension, no_extension);
    strcat(with_extension, "V2.eps"); // Concatenation

    // File management
    FILE *fptr;
    fptr = fopen(with_extension, "w");
    if (fptr == NULL)
    {
        printf("EPS File Error!\n");
        exit(1);
    }

    // File header
    fprintf(fptr, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(fptr, "%%%%BoundingBox: 0 0 %d %d\n", largeur, hauteur); // Adjusted bounding box
    fprintf(fptr, "\n");

    // Iterate through the pixels array
    int is_contour_started = 0;
    for (int y = 0; y < hauteur; y++)
    {
        for (int x = 0; x < largeur; x++)
        {
            if (pixels[y][x] == 1)
            {
                if (!is_contour_started)
                {
                    fprintf(fptr, "%.0d %.0d moveto ", x, hauteur - y - 1); // Adjusted starting point
                    is_contour_started = 1;
                }
            }
            else
            {
                if (is_contour_started)
                {
                    fprintf(fptr, "%.0d %.0d lineto ", x - 1, hauteur - y); // Adjusted ending point
                    // fprintf(fptr, "fill\n");
                    is_contour_started = 0;
                }
            }
        }
        if (is_contour_started)
        {
            fprintf(fptr, "%.0d %.0d lineto ", largeur - 1, hauteur - y); // Close contour at end of row
            // fprintf(fptr, "fill\n");
            is_contour_started = 0;
        }
    }
    fprintf(fptr, "fill\n");

    fprintf(fptr, "\n");
    fprintf(fptr, "showpage\n");
    fclose(fptr);
    //free(with_extension);
}