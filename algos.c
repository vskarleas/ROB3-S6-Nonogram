// #############################################################################
// # File algos.c
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
#include "ui.h"

/* It verifies the decisions regarding a line according to its sequence and the rules of the puzzle */
/* FINAL VERSION IS V2 */


//DEPRECATED
/* VERSION 0: This version treats correctly the majority of cases but it doesn't take into consideration the already colourised
   black cells that are before the section that is tested and returned true. A test of total amount of black cells
   needs to be performed definitely */
bool T(int j, int l, int *tab, int *seq, int total_length)
{
    // This is the case were everything is possible
    if (l == 0)
    {
        return true;
    }
    if (l >= 1)
    {
        // Case 2a: There is no available amount cells for the sequence to be valid
        if (j < seq[l - 1] - 1)
        {
            return false;
        }
        // Case 2b: It can be true if and only if there is only one sequence. Otherwise
        // it's not possible to treat the rest of sequences in that available number of
        // cells. If it finds a white cell then the sequence is not valid and returns false
        if (j == seq[l - 1] - 1)
        {

            for (int i = 0; i <= j; i++)
            {
                if (tab[i] == WHITE)
                {
                    return false;
                }
            }

            return (l == 1); // The condition that needs to be true in order for that sub case (2b) to be verfied
        }
        // Case 2c
        if (j > seq[l - 1] - 1)
        {
            // We check the previous combination
            if (tab[j] == WHITE)
            {
                return (T(j - 1, l, tab, seq, total_length));
            }
            // We check every combination that is possible for a given sequence
            else
            {
                int counter = 0;
                int i;
                // The counter will allows us to verify if the sequence was verified
                for (i = j; i > j - seq[l - 1]; i--)
                {
                    if (tab[i] == BLACK || tab[i] == DEFAULT)
                    {
                        counter++;
                    }
                }

                if (i < total_length)
                {
                    // After the sequence there is a black cell that under normal circomstances
                    // it should be white for the sequence to be valid in that position. Howeber
                    // it is not the case and we need to check for the same sequence once step
                    // on the left before we can conclude
                    if (tab[i] == BLACK && l > 1)
                    {
                        return (T(j - 1, l, tab, seq, total_length));
                    }
                    // Case where after the sequence the next cell is white or not coloured. In that case we move on for the next seqence
                    else if (counter == seq[l - 1] && (tab[i] == WHITE || tab[i] == DEFAULT))
                    {

                        return (T(i - 1, l - 1, tab, seq, total_length));
                    }
                    // none of the previous cases so we keep searching moving one step on the left for the same sequence
                    else
                    {
                        return (T(j - 1, l, tab, seq, total_length));
                    }
                }
                else
                {
                    return false; // means that i is greater than the length of the line or column so the response is false
                }
            }
        }
    }

    // everything fails so the response is false
    return false;
}

//DEPRECATED
/* VERSION 1 */
bool T_v1(int j, int l, int *tab, int *seq)
{
    // Checking wheter we have wrong-colorised a cell during a decision that
    // doesn't respect the maximum amount of cells that can be colorised
    if (count_black_cells(tab, j + 1, 1) > count_black_cells(seq, l, 2))
    {
        return false;
    }

    // ================
    // Case 1
    // ================

    /* This is the case were everything is possible */
    if (l == 0)
    {
        return true;
    }

    // ================
    // Case 2a
    // ================

    if (j < seq[l - 1] - 1) // please consider that is seauence seq the place at seq[0] is never used on our program. It's just initialises on a nunber that we never take into consideration
    {
        return false;
    }

    // ================
    // Case 2b
    // ================

    /* It can be true if and only if there is only one sequence. Otherwise
       it's not possible to treat the rest of sequences in that available number of
       cells. If it finds a white cell then the sequence is not valid and returns false */
    if (j == seq[l - 1] - 1)
    {
        if (l == 1)
        {
            for (int i = 0; i < seq[l-1]; i++)
            {
                if (tab[j - i] == WHITE)
                {
                    return false;
                }
            }

            return true;
        }
        else
        {
            return false;
        }
    }

    // ================
    // Subcases for 2c
    // ================

    /* Checking if current index is black and perfom sequence verification */
    if (tab[j] == BLACK)
    {
        // Case where after the sequence the next cell is white or not coloured. In that case we move on for the next seqence (l - 1)
        if (tab[j - seq[l - 1]] == WHITE)
        {
            int i;
            for (i = j; i > j - seq[l - 1]; i--)
            {
                if (tab[i] == WHITE)
                {
                    return false;
                }
            }
            return (T_v1(j - seq[l - 1] - 1, l - 1, tab, seq));
        }
        
    }

    /* After the sequence there is a black cell that under normal circomstances
       it should be white for the sequence to be valid in that position. However
       it is not the case and we need to check for the same sequence once step
       on the left before we can conclude. */
    if (tab[j - seq[l - 1]] == BLACK)
    {
        return (T_v1(j - 1, l, tab, seq));
    }

    /* The sequence was valid for the local search that was perfomed on index j and
       on index j - seq[l] (black exclusivly), so last but not least we need to perform
       a global test. If there is a white ceel that is found then we move on one step
       on the left as usual according to question 3. */
    int i;
    for (i = j; i > j - seq[l - 1]; i--)
    {
        if (tab[i] == WHITE)
        {
            return T_v1(i - 1, l, tab, seq);
        }
    }

    return (T_v1(j - seq[l - 1] - 1, l - 1, tab, seq) || T_v1(j - 1, l, tab, seq));

    // everything fails so the response is false
    return false;
}

/* VERSION 2: Black cells test perfomed and simplified tests for j > seq[l] - 1 */
bool T_v2(int j, int l, int *tab, int *seq)
{
    // Checking wheter we have wrong-colorised a cell during a decision that
    // doesn't respect the maximum amount of cells that can be colorised
    if (count_black_cells(tab, j + 1, 1) > count_black_cells(seq, l, 2))
    {
        return false;
    }

    // ================
    // Case 1
    // ================

    /* This is the case were everything is possible */
    if (l == 0)
    {
        return true;
    }

    // ================
    // Case 2a
    // ================

    if (j < seq[l - 1] - 1) // please consider that is seauence seq the place at seq[0] is never used on our program. It's just initialises on a nunber that we never take into consideration
    {
        return false;
    }

    // ================
    // Case 2b
    // ================

    /* It can be true if and only if there is only one sequence. Otherwise
       it's not possible to treat the rest of sequences in that available number of
       cells. If it finds a white cell then the sequence is not valid and returns false */
    if (j == seq[l - 1] - 1)
    {
        if (l == 1)
        {
            for (int i = 0; i < seq[l - 1]; i++)
            {
                if (tab[j - i] == WHITE)
                {
                    return false;
                }
            }

            return true;
        }
        else
        {
            return false;
        }
    }

    // ================
    // Subcases for 2c
    // ================

    /* Checking if current index is black and perfom sequence verification */
    if (tab[j] == BLACK)
    {
        // Case where after the sequence the next cell is white or not coloured. In that case we move on for the next seqence (l - 1)
        if (tab[j - seq[l - 1]] == WHITE || tab[j - seq[l - 1]] == DEFAULT)
        {
            int i;
            for (i = j; i > j - seq[l - 1]; i--)
            {
                if (tab[i] == WHITE)
                {
                    return false;
                }
            }

            return (T_v2(j - seq[l - 1] - 1, l - 1, tab, seq));
        }

        /* After the sequence there is a black cell that under normal circomstances
       it should be white for the sequence to be valid in that position. So it's false in that case. */
        if (tab[j - seq[l - 1]] == BLACK)
        {
            return false;
        }
    }

    /* After the sequence there is a black cell that under normal circomstances
       it should be white for the sequence to be valid in that position. However
       it is not the case and we need to check for the same sequence once step
       on the left before we can conclude. */
    if (tab[j - seq[l - 1]] == BLACK)
    {
        return (T_v2(j - 1, l, tab, seq));
    }

    /* The sequence was valid for the local search that was perfomed on index j and
       on index j - seq[l] (black exclusivly), so last but not least we need to perform
       a global test. If there is a white cell that is found then we move on one step
       on the left as usual according to question 3. */
    int i;
    for (i = j; i > j - seq[l - 1]; i--)
    {
        if (tab[i] == WHITE)
        {
            return T_v2(i - 1, l, tab, seq);
        }
    }

    return (T_v2(j - seq[l - 1] - 1, l - 1, tab, seq) || T_v2(j - 1, l, tab, seq));

    // everything fails so the response is false
    return false;
}



/* Coloring the grid following seperate lines and seperates collumns approach */
/* FINAL VERSION IS V3 */
enum State color_grid_v1(int **main_grid, int n_rows, int n_columns, int **rows, int **columns, int maximum)
{
    bool response;

    int **grid;
    grid = malloc(n_rows * sizeof(int *));
    if (grid == NULL)
    {
        allocation_error_print_general("grid");
    }

    for (int i = 0; i < n_rows; i++)
    {
        grid[i] = malloc(n_columns * sizeof(int));
        if (grid[i] == NULL)
        {
            allocation_error_print_with_id("grid row", i);
        }
    }

    // Local copy of the grid
    copy_grid(main_grid, grid, n_rows, n_columns);

    // Maintaining a list of the lines and columns that need to be explored
    bool lines_to_see[n_rows];
    init_to_see(lines_to_see, n_rows);
    bool columns_to_see[n_columns];
    init_to_see(columns_to_see, n_columns);

    while (to_see_is_not_empty(lines_to_see, n_rows) || to_see_is_not_empty(columns_to_see, n_columns)) // there are still lines or columns to be explored
    {
        for (int i = 0; i < n_rows; i++)
        {

            // Analysis of the line in question
            int *tab;
            tab = malloc(n_columns * sizeof(int)); // The number of columns is the length of the line in question
            if (tab == NULL)
            {
                fprintf(stderr, "\nFailed to allocate memory for tab.\n");
                exit(-10);
            }

            line_isolation(grid, i, n_columns, tab);
            response = color_decision(tab, rows[i], n_columns, maximum); // we take the ieme table of seqeunces for the ieme line in the analysis process

            if (response == false)
            {
                return FAIL;
            }

            line_to_grid(grid, i, tab, n_columns);
            free(tab);

            // setting that the current line was treated
            lines_to_see[i] = false;
        }
        for (int i = 0; i < n_columns; i++)
        {
            // Analysis of the line in question
            int *tab;
            tab = malloc(n_rows * sizeof(int)); // The number of rows is the length of the column in question
            if (tab == NULL)
            {
                fprintf(stderr, "\nFailed to allocate memory for tab.\n");
                exit(-11);
            }

            column_isolation(grid, i, n_rows, tab);
            response = color_decision(tab, columns[i], n_rows, maximum);

            if (response == false)
            {
                return FAIL;
            }

            column_to_grid(grid, i, tab, n_rows);
            free(tab);

            // setting that the current column was treated
            columns_to_see[i] = false;
        }
    }

    // Copying the final result back to the main grid
    copy_grid(grid, main_grid, n_rows, n_columns);

    free_2d(grid, n_rows);

    if (grid_in_color(grid, n_rows, n_columns) == true)
    {
        return SUCCESS;
    }
    else
    {
        return NO_DECISION;
    }
}

/* Coloring the grid (partially) and making decisions */
enum State color_grid_v2(int **grid, int n_rows, int n_columns, int **rows_columns, int maximum)
{
    // NOTE: x is for horizontal (lines) and y is for vertical (columns) on grid's 2D array
    while (grid_defaults_count(grid, n_rows, n_columns) != 0)
    {
        for (int x = 0; x < n_rows; x++)
        {
            // This first test checks whether we need to proceed to line analysis or not.
            //  If the sequence can be applied directly with any cells uncolorised,
            //  then we coulorise them and we move on to the next line
            int pre_l = correct_length(rows_columns[x], maximum);
            int nb_blacks = count_black_cells(rows_columns[x], pre_l, 2);
            int nb_whites = pre_l - 1;
            if ((nb_blacks + nb_whites) == n_columns)
            {
                color_lineORcolumn(grid[x], rows_columns[x], n_columns);
            }
            else
            {
                for (int y = 0; y < n_columns; y++)
                {
                    /* If no color is aplied yet to the specific cell */
                    if (grid[x][y] == DEFAULT)
                    {
                        int l;
                        bool white_test, black_test;

                        // ==========================
                        // Local test for white state
                        // ==========================
                        grid[x][y] = WHITE;

                        // Analysis of the line in question (in parallel of every column for this line [this is done with every change of y])
                        int *tab = (int *)malloc(n_rows * sizeof(int)); // The number of rows is the length of the column in question
                        if (tab == NULL)
                        {
                            fprintf(stderr, "\nFailed to allocate memory for tab.\n");
                            exit(-1);
                        }

                        // Isolation of the column for the current y
                        column_isolation(grid, y, n_rows, tab);

                        /* HORIZONTAL test */
                        l = correct_length(rows_columns[x], maximum);
                        white_test = T_v2(n_columns - 1, l, grid[x], rows_columns[x]);

                        /* VERTICAL test */
                        if (white_test)
                        {
                            l = correct_length(rows_columns[n_rows + y], maximum);           // updating l value
                            white_test = T_v2(n_rows - 1, l, tab, rows_columns[n_rows + y]); // we need + 1 because y counts from 0, so in order to take the correct sequence for the column, we need n_rows + 0 + 1 to be distinguised
                        }

                        // ==========================
                        // Local test for black state
                        // ==========================
                        grid[x][y] = BLACK;
                        tab[x] = BLACK; // This step is essential. Previsouly the colourisation in white happened before isolation. Here we have to do it manually because we have already isolated the column

                        /* HORIZONTAL test */
                        l = correct_length(rows_columns[x], maximum);
                        black_test = T_v2(n_columns - 1, l, grid[x], rows_columns[x]);

                        /* VERTICAL test */
                        if (black_test)
                        {
                            l = correct_length(rows_columns[n_rows + y], maximum);           // updating l value
                            black_test = T_v2(n_rows - 1, l, tab, rows_columns[n_rows + y]); // we need + 1 because y counts from 0, so in order to take the correct sequence for the column, we need n_rows + 0 + 1 to be distinguised
                        }

                        free(tab);

                        // ==========================
                        // Reversing any changes
                        // ==========================
                        grid[x][y] = DEFAULT;

                        // ==========================
                        // Decisions and conclusions
                        // ==========================
                        if (white_test == false)
                        {
                            if (black_test == false)
                            {
                                //printf("\n%d,  %d\n", x, y);
                                return FAIL;
                            }
                            else
                            {
                                grid[x][y] = BLACK;
                            }
                        }
                        else if (black_test == false)
                        {
                            if (white_test == true)
                            {
                                grid[x][y] = WHITE;
                            }
                            else
                            {
                                return NO_DECISION;
                            }
                        }
                    }
                    //printing_grid(grid, n_rows, n_columns, 3);
                }
                printing_grid(grid, n_rows, n_columns, 3);
            }
        }
    }

    if (grid_in_color(grid, n_rows, n_columns))
    {
        return SUCCESS;
    }
    else
    {
        return NO_DECISION;
    }
}

/* Final version that colourises and calls recursivly in order to examine all the possible cases (complet) */
/* NOTA BENE: Same logic with v2 but more elaborated and completed */
enum State color_grid_v3(int **grid, int n_rows, int n_columns, int **rows_columns, int maximum, int mode)
{
    enum State result;
    result = SUCCESS;                        // status by default. It will be updated accordingly
    int last_time = 1, before_last_time = 1; // indicators of our not-colourised cells in the puzzle grid in two different times. last_empty happened before after_last_empty in a chronological sequence

    while (last_time > 0 && result == SUCCESS)
    {
        for (int x = 0; x < n_rows; x++)
        {
            // This first test checks whether we need to proceed to line analysis or not.
            //  If the sequence can be applied directly with any cells uncolorised,
            //  then we coulorise them and we move on to the next line

            int pre_l = correct_length(rows_columns[x], maximum);
            int nb_blacks = count_black_cells(rows_columns[x], pre_l, 2);
            int nb_whites = pre_l - 1;
            if ((nb_blacks + nb_whites) == n_columns)
            {
                color_lineORcolumn(grid[x], rows_columns[x], n_columns);
            }
            else
            {
                for (int y = 0; y < n_columns; y++)
                {
                    /* If no color is aplied yet to the specific cell */
                    if (grid[x][y] == DEFAULT)
                    {
                        int l;
                        bool white_test, black_test;

                        // ==========================
                        // Local test for white state
                        // ==========================
                        grid[x][y] = WHITE;

                        // Analysis of the line in question (in parallel of every column)
                        int *tab = (int *)malloc(n_rows * sizeof(int)); // The number of rows is the length of the column in question
                        if (tab == NULL)
                        {
                            fprintf(stderr, "\nFailed to allocate memory for tab.\n");
                            exit(-2);
                        }

                        column_isolation(grid, y, n_rows, tab);
                        // print_line(tab, n_rows);

                        /* HORIZONTAL test */
                        l = correct_length(rows_columns[x], maximum);
                        white_test = T_v2(n_columns - 1, l, grid[x], rows_columns[x]);

                        /* VERTICAL test */
                        if (white_test)
                        {
                            l = correct_length(rows_columns[n_rows + y], maximum);
                            white_test = T_v2(n_rows - 1, l, tab, rows_columns[n_rows + y]);
                        }

                        // ==========================
                        // Local test for black state
                        // ==========================
                        grid[x][y] = BLACK;
                        tab[x] = BLACK; // This step is essential. Previsouly the colourisation in white happened before isolation. Here we have to do it manually because we have already isolated the column

                        // printf("\n");
                        // print_line(tab, n_rows);

                        /* HORIZONTAL test */
                        l = correct_length(rows_columns[x], maximum);
                        if (l == 0)
                        {
                            black_test = false; // We know with certainty that we can't colorise that cell in black because theyre is no sequence. It can be white or nothing but no black
                        }
                        else
                        {
                            black_test = T_v2(n_columns - 1, l, grid[x], rows_columns[x]); // we need + 1 because x counts from 0, so in

                            /* VERTICAL test */
                            if (black_test)
                            {
                                l = correct_length(rows_columns[n_rows + y], maximum);
                                black_test = T_v2(n_rows - 1, l, tab, rows_columns[n_rows + y]);
                            }
                        }

                        free(tab);

                        // ==========================
                        // Reversing any changes
                        // ==========================
                        grid[x][y] = DEFAULT;

                        // ==========================
                        // Decisions and conclusions
                        // ==========================
                        if (white_test == false)
                        {
                            if (black_test == false)
                            {
                                //printf("\n%d,  %d\n", x, y);
                                return FAIL;
                            }
                            else
                            {
                                grid[x][y] = BLACK;
                            }
                        }
                        else if (black_test == false)
                        {
                            if (white_test == true)
                            {
                                grid[x][y] = WHITE;
                            }
                            else
                            {
                                return NO_DECISION;
                            }
                        }

                        // printing_grid(grid, n_rows, n_columns, 2);
                        // printf("\n\n");
                    }
                }
            }
        }

        if (mode == 1)
        {
            printing_grid(grid, n_rows, n_columns, 3);
        }
        
        int changes = grid_defaults_count(grid, n_rows, n_columns);

        if (changes == last_time && changes == before_last_time)
        {
            /* It means that there was no change during the last 2 itterations
            of the boucle while, so we need to recalculate  */

            int x_updated = -1;
            int y_updated;
            recalculation(grid, n_rows, n_columns, &x_updated, &y_updated);

            if (color_grid_complet(grid, rows_columns, n_rows, n_columns, x_updated, y_updated, maximum, mode) == 1)
            {
                return SUCCESS;
            }
            result = NO_DECISION; // in order to terminate the while
        }
        before_last_time = last_time;
        last_time = changes;
    }

    /* Final test that determines if there is a final SUCCESS decision or NO_DECISION because not every cell was colorised */
    if (grid_in_color(grid, n_rows, n_columns))
    {
        return SUCCESS;
    }
    else
    {
        return NO_DECISION;
    }
}