// #############################################################################
// # File decode.h
// # UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#ifndef H_DECODE
#define H_DECODE

/* Saving the nb of lines, columsn as well as the maximum length of a sequence of a line and a sequence of a collumn */
void decode_file(char *filename, int *n_rows, int *n_cols, int *max_rows, int *max_cols);

/* Decoding an instance's file content */
void read_file(char *filename, int **lines, int **columns, int n_rows, int n_cols, int max_lines, int max_columns);

void read_file_v2(char *filename, int **lines, int **columns, int n_rows, int n_cols, int maximum);

#endif