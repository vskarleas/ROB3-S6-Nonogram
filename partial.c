// #############################################################################
// # File partial.c
// # UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "utile.h"
#include "algos.h"
#include "constants.h"
#include "decode.h"
#include "memory.h"
#include "tables.h"
#include "ui.h"
#include "bitmap.h"

int main(int argc, char **argv)
{
    printf("\n\e[0;102mUNCOMPLET mode\e[0m\nYou can test an individual instance using the uncomplet/partial algoritm (part 1.3 in the project)\n\n");
    char file_name[100];

    printf("\nWhat's the instance's file name (with .txt extenesion): ");
    scanf("%s", file_name);

    char *no_extension = strtok(file_name, ".");

    char *filename = malloc(strlen("instances/") + strlen(no_extension) + 4);
    strcpy(filename, "instances/");
    strcat(filename, no_extension);
    strcat(filename, ".txt");

    filename[strcspn(filename, "\n")] = '\0'; // make sure that the file is in correct format so that we can start counting nb_lines and nb_columns immediatly

    int n_rows, n_cols, max_rows, max_columns;

    /* First analysis of the instance */
    decode_file(filename, &n_rows, &n_cols, &max_rows, &max_columns);

    printf("\nNB Lines: %d\n", n_rows);
    printf("Max Lines: %d\n", max_rows);
    printf("NB Columns: %d\n", n_cols);
    printf("Max Columns: %d\n\n", max_columns);

    int maximum = max(max_columns, max_rows);

    /* Main Memory allocation */
    int **rows;
    rows = malloc(n_rows * sizeof(int *));
    if (rows == NULL)
    {
        allocation_error_print_general("rows");
    }

    for (int i = 0; i < n_rows; i++)
    {
        rows[i] = malloc(maximum * sizeof(int));
        if (rows[i] == NULL)
        {
            allocation_error_print_with_id("rows row", i);
        }
    }

    int **columns;
    columns = malloc(n_cols * sizeof(int *));
    if (columns == NULL)
    {
        allocation_error_print_general("columns");
    }

    for (int i = 0; i < n_cols; i++)
    {
        columns[i] = malloc(maximum * sizeof(int));
        if (columns[i] == NULL)
        {
            allocation_error_print_with_id("columns row", i);
        }
    }

    /* Instance decoding */
    read_file_v2(filename, rows, columns, n_rows, n_cols, maximum);

    /* Concatenating rows and columsn sequences in a single table to simplify the treatment process */
    int **rows_columns = malloc(sizeof(int *) * (n_rows + n_cols));

    for (int i = 0; i < n_rows; i++)
    {
        rows_columns[i] = rows[i]; // Copy the entire row pointer
    }

    for (int i = 0; i < n_cols; i++)
    {
        rows_columns[n_rows + i] = columns[i]; // Copy to subsequent rows
    }

    /* Grid creation and initialization */
    int **grid;
    grid = malloc(n_rows * sizeof(int *));
    if (columns == NULL)
    {
        allocation_error_print_general("grid");
    }

    for (int i = 0; i < n_rows; i++)
    {
        grid[i] = malloc(n_cols * sizeof(int));
        if (grid[i] == NULL)
        {
            allocation_error_print_with_id("grid row", i);
        }
    }

    initialize2D(grid, n_rows, n_cols);

    /* Result */
    enum State result;
    clock_t temps_initial;
    clock_t temps_final;
    float temps_cpu = 0.0;

    printf("\e[0;36mPlease note that this method does not gurantee the resolution of every puzzle. Use it with precaution!\nIf it entes an infinite loop and once you force quit it (CNTRL + Z), then the workspace won't be cleaned in the background.\nHowever, if you try again by executing bash run.sh everything will get formated for you automaticly\n\e[0m");

    int time = midle_menu();
    printf("In progress...\n");

    if (time == 1)
    {
        temps_initial = clock();
        result = color_grid_v2(grid, n_rows, n_cols, rows_columns, maximum);
        temps_final = clock();

        temps_cpu = (temps_final - temps_initial) * 1e-6; // Total time in seconds
        clearScreen();
        printf("\nThe operation took %f seconds\n", temps_cpu);
    }
    else if (time == 2)
    {
        result = color_grid_v2(grid, n_rows, n_cols, rows_columns, maximum);
        clearScreen();
    }
    else
    {
        exit(-6);
    }
    write_pbm_file(n_cols, n_rows, grid, file_name, "results/v1_3-");

    switch (result)
    {
    case SUCCESS:
        printf("\n\e[0;32mSUCCESS\e[0m\n[%d, %d]", n_rows, n_cols);
        printf("\nThe colourised grid is:\n\n");
        printing_grid(grid, n_rows, n_cols, 2);
        break;
    case FAIL:
        printf("\n\e[0;31mThe provided puzzle can NOT BE SOLVED\e[0m\n");
        // printf("\nThe grid is:\n");
        // printing_grid(grid, n_rows, n_cols, 4);
        break;
    case NO_DECISION:
        printf("\n\e[0;36mThere is NO DECISION for the provided puzzle\e[0m\n");
        printf("\nThe grid is:\n\n");
        printing_grid(grid, n_rows, n_cols, 2);
        break;
    default:
        printf("An error occured on enum State response\n");
        break;
    }
    printf("You can find the generated image at the results folder with name V1_3-%s\n\n", file_name);
}