// #############################################################################
// # File api.h
// # UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#ifndef H_API
#define H_API

/* Returns true if LignesAVoir or ColonnesAVoir are not emtpy yet */
bool to_see_is_not_empty(bool *table, int n);

/* Colorizes the line once it knows that it can be colourised correctly */
void color_lineORcolumn(int *line, int *seq, int length);

/* Retruns the correct length of a sequence and not the maximum one */
int correct_length(int *seq, int size);

/* Checks if a line or column can be colorised and proceeds to the appropriate action (colorisation or not)  */
bool color_decision(int *tab, int *seq, int length, int maximum);

/* Returns true if every cell of the grid is colorised */
bool grid_in_color(int **grid, int rows, int columns);

/* Counts how many cells exist on the grid that are not colourised yet */
int grid_defaults_count(int **grid, int rows, int columns);

/* It counts the blacks cells in a line or column (mode 1) | it returns the number of black cells that we wish for a given sequence */
int count_black_cells(int *tab, int length, int mode);

/* Completing the colorisation process with recursion */
int color_grid_complet(int **grid, int **rows_columns, int n_rows, int n_columns, int i, int j, int maximum, int mode);

#endif