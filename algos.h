// #############################################################################
// # File algos.h
// # UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#ifndef H_ALGOS
#define H_ALGOS

#include "constants.h"

/* It verifies the decisions regarding a line according to its sequence and the rules of the puzzle */
bool T(int j, int l, int *tab, int *seq, int total_length);

/* VERSION 1 */
bool T_v1(int j, int l, int *tab, int *seq);

/* It verifies the decisions regarding a line according to its sequence and the rules of the puzzle */
bool T_v2(int j, int l, int *tab, int *seq);

/* Coloeing the grid and making decisions */
enum State color_grid_v1(int **main_grid, int n_rows, int n_columns, int **rows, int **columns, int maximum);

/* Coloring the grid and making decisions */
enum State color_grid_v2(int **grid, int n_rows, int n_columns, int **rows_columns, int maximum);

/* Final version that colourises and calls recursivly in order to examine all the possible cases */
/* NOTA BENE: Same logic with v2 but more elaborated */
enum State color_grid_v3(int **grid, int n_rows, int n_columns, int **rows_columns, int maximum, int mode);

#endif