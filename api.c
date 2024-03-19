// #############################################################################
// # File api.c
// # UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "constants.h"
#include "algos.h"
#include "api.h"
#include "memory.h"
#include "tables.h"

// DEPRECATED
/* Returns true if LignesAVoir or ColonnesAVoir are not emtpy yet */
bool to_see_is_not_empty(bool *table, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (table[i] == true)
        {
            return true;
        }
    }
    return false;
}

/* Colorizes the line once it knows that it can be colourised correctly */
void color_lineORcolumn(int *line, int *seq, int length)
{
    int k = 0;
    int current = 0;
    while (seq[k] != 0)
    {
        for (int i = 0; i < seq[k]; i++)
        {
            line[current] = BLACK;
            current++;
        }
        if (current < length)
        {
            line[current] = WHITE;
            current++;
        }
        k++;
    }
}

/* Retruns the correct length of a sequence and not the maximum one */
int correct_length(int *seq, int size)
{
    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (seq[i] != 0)
        {
            count++;
        }
    }
    return count;
}

// DEPRECATED
/* Checks if a line or column can be colorised and proceeds to the appropriate action (colorisation or not)  */
bool color_decision(int *tab, int *seq, int length, int maximum)
{
    int l = correct_length(seq, maximum);
    // returns false if it's impossible to color this line otherwise it returns true
    if (T_v2(length - 1, l, tab, seq) == true)
    {
        color_lineORcolumn(tab, seq, length);
        return true;
    }
    else
    {
        return false;
    }
}

/* Returns true if every cell of the grid is colorised */
bool grid_in_color(int **grid, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (grid[i][j] == DEFAULT)
            {
                return false;
            }
        }
    }
    return true;
}

/* Counts how many cells exist on the grid that are not colourised yet */
int grid_defaults_count(int **grid, int rows, int columns)
{
    int count = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (grid[i][j] == DEFAULT)
            {
                count++;
            }
        }
    }

    return count;
}

/* It counts the blacks cells in a line or column (mode 1) | it returns the number of black cells that we wish for a given sequence */
int count_black_cells(int *tab, int length, int mode)
{
    int counter = 0;
    if (mode == 1) // line or column mode
    {
        for (int i = 0; i < length; i++)
        {
            if (tab[i] == BLACK)
            {
                counter++;
            }
        }
    }
    else if (mode == 2) // Case 2a: There is no available amount cells for the sequence to be valid
    {
        for (int i = 0; i < length; i++)
        {
            counter = counter + tab[i];
        }
    }
    else
    {
        printf("An error occured. Try again:(\n");
        exit(-3);
    }

    return counter;
}

/* Completing the colorisation process with recursion */
// Logic inspired by Manu Guerinel
int color_grid_complet(int **grid, int **rows_columns, int n_rows, int n_columns, int i, int j, int maximum, int mode)
{
    /* Making a temporary copy of the grid for returning_back porpuses */
    int **duplicate;
    duplicate = malloc(n_rows * sizeof(int *));
    if (duplicate == NULL)
    {
        allocation_error_print_general("duplicate");
    }

    for (int i = 0; i < n_rows; i++)
    {
        duplicate[i] = malloc(n_columns * sizeof(int));
        if (duplicate[i] == NULL)
        {
            allocation_error_print_with_id("duplicate row", i);
        }
    }

    // Grid -> duplicate
    copy_grid(grid, duplicate, n_rows, n_columns);

    // ==========================
    // White test
    // ==========================
    grid[i][j] = WHITE;
    if (color_grid_v3(grid, n_rows, n_columns, rows_columns, maximum, mode) == SUCCESS)
    {
        free_2d(duplicate, n_rows);
        return 1;
    }
    copy_grid(duplicate, grid, n_rows, n_columns); // going back to previous state

    // ==========================
    // Black test
    // ==========================
    grid[i][j] = BLACK;
    if (color_grid_v3(grid, n_rows, n_columns, rows_columns, maximum, mode) == SUCCESS)
    {
        free_2d(duplicate, n_rows);
        return 1;
    }
    copy_grid(duplicate, grid, n_rows, n_columns); // going back to previous state

    // Otherwise
    free_2d(duplicate, n_rows);
    return 0;
}