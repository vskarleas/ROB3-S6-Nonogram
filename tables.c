// #############################################################################
// # File tables.c
// # UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "constants.h"
#include "tables.h"

/* Copying date from gridA to gridB (1D)*/
void copy_grid_1d(int *grid, int *final, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        final[i] = grid[i];
    }
}

/* Copying date from gridA to gridB (2D arrays) */
void copy_grid(int **grid, int **final, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            final[i][j] = grid[i][j];
        }
    }
}

/* Initializing the LignesAVoir abd the ColonnesAVoir tables */
void init_to_see(bool *tab, int n)
{
    for (int i = 0; i < n; i++)
    {
        tab[i] = true;
    }
}

/* Isolating a specific line from the grid */
void line_isolation(int **grid, int line_id, int length, int *returned)
{
    for (int i = 0; i < length; i++)
    {
        returned[i] = grid[line_id][i];
    }
}

/* Values from a seperate table (represents a line) are copied to the 2D grid */
void line_to_grid(int **grid, int line_id, int *line, int length)
{
    for (int i = 0; i < length; i++)
    {
        grid[line_id][i] = line[i];
    }
}

/* Values from a seperate table (represents a column here) are copied to the 2D grid */
void column_to_grid(int **grid, int column_id, int *column, int length)
{
    for (int i = 0; i < length; i++)
    {
        grid[i][column_id] = column[i];
    }
}

/* Isolating a specific column from the grid */
void column_isolation(int **grid, int column_id, int length, int *returned)
{
    for (int i = 0; i < length; i++)
    {
        returned[i] = grid[i][column_id];
    }
}

/* Concatenate two strings */
char *concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

/* Finding the next not-colorised cell in a 2D array */
void recalculation(int **grid, int rows, int columns, int *i, int *j)
{
    int x = 0;
    int y = 0;

    while (x < rows && (*i) == -1)  //We take (*i) because we want to check the value of the pointer
    {
        for (y = 0; y < columns; y++)
        {
            if (grid[x][y] == DEFAULT)
            {
                (*i) = x;
                (*j) = y;
                break;
            }
        }
        x++;
    }
}