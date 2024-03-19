// #############################################################################
// # File bitmap.h
// # UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#ifndef H_BITMAP
#define H_BITMAP

/* Writing a PBM file for BitMap image creation */
void write_pbm_file(int width, int height, int **array, char *file_name, char *repository);

/* It writes an EPS file for BitMap image creation - postscript */
void create_postscript_file_v1_3(int **pixels, char *file_name, int hauteur, int largeur);

void create_postscript_file_v2(int **pixels, char *file_name, int hauteur, int largeur);

#endif