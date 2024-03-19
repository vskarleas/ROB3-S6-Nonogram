// #############################################################################
// # File decode.c
// # UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "utile.h"
#include "decode.h"

/* Saving the nb of lines, columsn as well as the maximum length of a sequence of a line and a sequence of a collumn */
void decode_file(char *filename, int *n_rows, int *n_cols, int *max_rows, int *max_cols)
{
    FILE *file = fopen(filename, "r");
    char ch;
    int temp = 0;

    // Verification
    if (file == NULL)
    {
        printf("There was an error opening the file!\n");
        return;
    }

    // Initialisations
    *n_rows = 0;
    *max_cols = 0;
    *max_rows = 0;
    *n_cols = 0;

    // Analyzing
    ch = fgetc(file);
    if (ch != '\n' && ch != '\r' && ch != ' ')
    {
        temp++;
    }
    while (ch != EOF)
    {
        // Check for new line and increment count
        if (ch == '\n')
        {
            *max_rows = max(*max_rows, temp);
            temp = 0;
            (*n_rows)++;
        }

        // Check for '#' at the beginning of a line
        if (ch == '#' && fgetc(file) == '\n')
        {
            break;
        }

        // Read the next character
        ch = fgetc(file);
        if (ch != '\n' && ch != '\r' && ch != ' ')
        {
            temp++;
        }
    }

    temp = 0;

    ch = fgetc(file);
    if (ch != '\n' && ch != '\r' && ch != ' ')
    {
        temp++;
    }
    while (ch != EOF)
    {
        // Check for new line and increment count
        if (ch == '\n')
        {
            *max_cols = max(*max_cols, temp);
            temp = 0;
            (*n_cols)++;
        }

        // Read the next character
        ch = fgetc(file);
        if (ch != '\n' && ch != '\r' && ch != ' ')
        {
            temp++;
        }
    }

    fclose(file);
}

//DEPRECATED
/* Decoding an instance's file content */
void read_file(char *filename, int **lines, int **columns, int n_rows, int n_cols, int max_lines, int max_columns)
{
    FILE *file = fopen(filename, "r");
    char ch;

    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }

    int id = 0;
    int local = 0;

    ch = fgetc(file);
    while (ch != EOF)
    {
        if (ch != '\n' && ch != '\r' && ch != ' ' && ch != '#')
        {
            lines[id][local] = ctoi(ch);
            local++;
        }

        // Check for new line and increment count
        if (ch == '\n')
        {
            if (local < max_lines)
            {
                for (int i = local; i < max_lines; i++)
                {
                    lines[id][i] = 0;
                }
            }
            local = 0;
            // reverse(0, max_lines-1, lines[id]);
            id++;
        }

        // Check for '#' at the beginning of a line
        if (ch == '#' && fgetc(file) == '\n')
        {
            break;
        }

        // Read the next character
        ch = fgetc(file);
    }

    id = 0;
    local = 0;

    ch = fgetc(file);
    while (ch != EOF)
    {
        if (ch != '\n' && ch != '\r' && ch != ' ' && ch != '#')
        {
            columns[id][local] = ctoi(ch);
            local++;
        }

        // Check for new line and increment count
        if (ch == '\n')
        {
            if (local < max_columns)
            {
                for (int i = local; i < max_columns; i++)
                {
                    columns[id][i] = 0;
                }
            }
            local = 0;
            // reverse(0, max_lines-1, lines[id]);
            id++;
        }

        // Check for '#' at the beginning of a line
        if (ch == '#' && fgetc(file) == '\n')
        {
            break;
        }

        // Read the next character
        ch = fgetc(file);
    }
}

/* It sets the sequences length to be the same for columsn and lines' sequences */
void read_file_v2(char *filename, int **lines, int **columns, int n_rows, int n_cols, int maximum)
{
    FILE *file = fopen(filename, "r");
    char ch, next_ch;

    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }

    int id = 0;
    int local = 0;

    char num_buffer[32] = "";  // Buffer to hold multi-digit numbers
    int num_buffer_pos = 0;

    ch = fgetc(file);
    while (ch != EOF)
    {
        if(is_digit(ch))
        {
            num_buffer[num_buffer_pos++] = ch;
            next_ch = fgetc(file);
            while (isdigit(next_ch))  // Read multiple digits
            {
                num_buffer[num_buffer_pos++] = next_ch;
                next_ch = fgetc(file);
            }

            num_buffer[num_buffer_pos] = '\0';
            ungetc(next_ch, file);

            lines[id][local] = atoi(num_buffer);  // Convert using atoi
            num_buffer[0] = '\0'; //Empting the char array num_buffer
            num_buffer_pos = 0;
            local++;
        }
        else if (ch != '\n' && ch != '\r' && ch != ' ' && ch != '#')
        {
            lines[id][local] = ctoi(ch);
            local++;
        }

        // Check for new line and increment count
        if (ch == '\n')
        {
            if (local < maximum)
            {
                for (int i = local; i < maximum; i++)
                {
                    lines[id][i] = 0;
                }
            }
            local = 0;
            // reverse(0, max_lines-1, lines[id]);
            id++;
        }

        // Check for '#' at the beginning of a line
        if (ch == '#' && fgetc(file) == '\n')
        {
            break;
        }

        // Read the next character
        ch = fgetc(file);
    }

    id = 0;
    local = 0;
    num_buffer_pos = 0;

    ch = fgetc(file);
    while (ch != EOF)
    {
        if(is_digit(ch))
        {
            num_buffer[num_buffer_pos++] = ch;
            next_ch = fgetc(file);
            while (isdigit(next_ch))  // Read multiple digits
            {
                num_buffer[num_buffer_pos++] = next_ch;
                next_ch = fgetc(file);
            }

            num_buffer[num_buffer_pos] = '\0';
            ungetc(next_ch, file);

            columns[id][local] = atoi(num_buffer);  // Convert using atoi
            num_buffer[0] = '\0'; //Empting the char array num_buffer
            num_buffer_pos = 0;
            local++;
        }
        else if (ch != '\n' && ch != '\r' && ch != ' ' && ch != '#')
        {
            columns[id][local] = ctoi(ch);
            local++;
        }

        // Check for new line and increment count
        if (ch == '\n')
        {
            if (local < maximum)
            {
                for (int i = local; i < maximum; i++)
                {
                    columns[id][i] = 0;
                }
            }
            local = 0;
            // reverse(0, max_lines-1, lines[id]);
            id++;
        }

        // Check for '#' at the beginning of a line
        if (ch == '#' && fgetc(file) == '\n')
        {
            break;
        }

        // Read the next character
        ch = fgetc(file);
    }
}