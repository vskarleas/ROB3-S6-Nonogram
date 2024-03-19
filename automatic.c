// #############################################################################
// # File automatic.c
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

#include <time.h>

/* Introduces a delay in milliseconds */
void msleep(unsigned long milisec) {
    struct timespec req = {0};
    time_t sec = (int)(milisec / 1000);
    milisec = milisec - (sec * 1000);
    req.tv_sec = sec;
    req.tv_nsec = milisec * 1000000L;
    while (nanosleep(&req, &req) == -1);
}


int main(int argc, char **argv)
{
    printf("\n\e[0;102mAUTOMATIC mode\e[0m\nThe list of tests can be found on the list.txt file. All the puzzle are referenced in the instancers folder\n\n");

    FILE *fp;
    char file_name[60];

    /* opening file for reading */
    fp = fopen("list.txt", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return (-9);
    }
    int test_id = 1;
    while (fgets(file_name, sizeof(file_name), fp) != NULL)
    {
        printf("\e[0;34mTest No %d\e[0m\nIn progress...\n", test_id);
        /* Only complete algorithm is applied */
        char *no_extension = strtok(file_name, ".");
        char *filename = malloc(strlen("instances/") + strlen(no_extension) + 4);
        strcpy(filename, "instances/");
        strcat(filename, no_extension);
        strcat(filename, ".txt");

        int n_rows, n_cols, max_rows, max_columns;

        /* First analysis of the instance */
        decode_file(filename, &n_rows, &n_cols, &max_rows, &max_columns);

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
            rows_columns[i] = rows[i]; // Copy the entire row
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

        temps_initial = clock();
        result = color_grid_v3(grid, n_rows, n_cols, rows_columns, maximum, 0); // mode 0 means that we do not print the evolution of the algorithm
        temps_final = clock();

        temps_cpu = (temps_final - temps_initial) * 1e-6; // Total time in seconds

        // create_postscript_file_v2(grid, file_name, n_rows, n_cols);
        write_pbm_file(n_cols, n_rows, grid, file_name, "tests/");

        switch (result)
        {
        case SUCCESS:
            printf("\n\e[0;32mSUCCESS for %s.txt \e[0m\n[%d, %d]", file_name, n_rows, n_cols);
            printf("\nThe operation took %f seconds\n", temps_cpu);
            break;
        case FAIL:
            printf("\n\e[0;31mFAILED for %s.txt\e[0m\n", file_name);
            printf("\nThe operation took %f seconds\n", temps_cpu);
            break;
        case NO_DECISION:
            printf("\n\e[0;36mNO DECISION for %s.txt\e[0m\n", file_name);
            printf("\nThe operation took %f seconds\n", temps_cpu);
            break;
        default:
            printf("An error occured on enum State response\n");
            break;
        }

        // Free allocated memory
        free(filename);
        free_2d(rows, n_rows);
        free_2d(columns, n_cols);
        free(rows_columns);
        free_2d(grid, n_rows);

        test_id++;
        printf("\n================================================\n");
        msleep(2000);
    }
    fclose(fp);
    printf("\n++++++++++++++++++++++++++++++++++++++++++++\nPlease find all the results on tests folder\n");
}