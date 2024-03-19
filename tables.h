// #############################################################################
// # File tables.h
// # UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#ifndef H_TABLES
#define H_TABLES

/* Copying date from gridA to gridB (1D)*/
void copy_grid_1d(int *grid, int *final, int rows);

/* Copying date from gridA to gridB */
void copy_grid(int **grid, int **final, int rows, int columns);

/* Initializing the LignesAVoir abd the ColonnesAVoir tables */
void init_to_see(bool *tab, int n);

/* Isolating a specific line from the grid */
void line_isolation(int **grid, int line_id, int length, int *returned);

/* Values from a seperate table (represents a line) are copied to the 2D grid */
void line_to_grid(int **grid, int line_id, int *line, int length);

/* Values from a seperate table (represents a column here) are copied to the 2D grid */
void column_to_grid(int **grid, int column_id, int *column, int length);

/* Isolating a specific column from the grid */
void column_isolation(int **grid, int column_id, int length, int *returned);

/* Concatenate two strings */
char* concat(const char *s1, const char *s2);

/* Finding the next not-colorised cell */
void recalculation(int **grid, int n_rows, int n_columns, int *x_updated, int *y_updated);

#endif