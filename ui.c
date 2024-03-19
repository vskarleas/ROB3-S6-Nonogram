// #############################################################################
// # File ui.c
// # UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <ncurses.h>

#include "constants.h"
#include "ui.h"

/* Gives a user the choice of the exercise */
int menu_mode()
{
    char userInput[20];
    char *msg[1] = {"Choose an option (1.2, 1.3, 2, automatic). Your choice: "};
    char *msg_attention[1] = {"You can only choose from 1.2 or 1.3, 2, or automatic."};

    while (true)
    {
        printf("\n%s ", msg[0]);
        scanf("%s", userInput);

        // Convert input to lowercase for case-insensitive comparison and returns
        for (int i = 0; i < strlen(userInput); i++)
        {
            userInput[i] = tolower(userInput[i]);
        }

        if (strcmp(userInput, "lalala") == 0)
        {
            return 1;
        }
        else if (strcmp(userInput, "1.2") == 0)
        {
            return 2;
        }
        else if (strcmp(userInput, "1.3") == 0)
        {
            return 3;
        }
        else if (strcmp(userInput, "2") == 0)
        {
            return 4;
        }
        else if (strcmp(userInput, "automatic") == 0)
        {
            return 5;
        }
        else if (strcmp(userInput, "exo4-v2") == 0)
        {
            return 6;
        }
        else
        {
            printf("\n\033[0;33mATTENTION!\033[1;0m: %s\n", msg_attention[0]);
        }
    }
    return 0;
}

//DEPRECATED
/* Printing the different arrays for testing purposes */
void print_table(int *tab, int n)
{
    int i;
    for (i = 0; i < n - 1; i++)
    {
        if (tab[i] == BLACK)
        {
            printf("\e[40m  \e[0m");
        }
        else if (tab[i] == WHITE)
        {
            printf("\e[47m  \e[0m");
        }
        else if (tab[i] == DEFAULT) // default case
        {
            printf("? ");
        }
    }
    if (tab[n - 1] == BLACK)
    {
        printf("\e[40m  \e[0m");
    }
    else if (tab[n - 1] == WHITE)
    {
        printf("\e[47m  \e[0m");
    }
    else if (tab[i] == DEFAULT) // default case
    {
        printf("? ");
    }
}

void print_table_v2(int *tab, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (tab[i] == BLACK)
        {
            printf("\e[1;30m#\e[0m ");
        }
        else if (tab[i] == WHITE)
        {
            printf("\e[1;37m#\e[0m ");
        }
        else if (tab[i] == DEFAULT) // default case
        {
            printf("? ");
        }
    }
}

/* Clearing the terminal screen for more optimised visualisations */
void clearScreen()
{
    // const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    // write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
    printf("\e[1;1H\e[2J");
}

/* Time counting decision menu */
int midle_menu()
{
    char userInput[20];

    while (true)
    {
        printf("\nDo you want time counting or not ? (Yes or No) \n");
        scanf("%s", userInput);

        // Convert input to lowercase for case-insensitive comparison and returns
        for (int i = 0; i < strlen(userInput); i++)
        {
            userInput[i] = tolower(userInput[i]);
        }

        if (strcmp(userInput, "yes") == 0)
        {
            return 1;
        }
        else if (strcmp(userInput, "no") == 0)
        {
            return 2;
        }
        else
        {
            clearScreen();
            printf("\n\033[0;33mATTENTION!\033[1;0m: You can choose between Yes or No\n");
        }
    }
}

/* Simple printing function for visualisations puproses */
void printing_grid(int **grid, int lines, int columns, int mode)
{
    if (mode == 1)
    {
        for (int i = 0; i < lines; i++)
        {
            for (int j = 0; j < columns - 1; j++)
            {
                printf("%d | ", grid[i][j]);
            }
            printf("%d \n", grid[i][columns - 1]);
        }
    }
    else if (mode == 2)
    {
        for (int i = 0; i < lines; i++)
        {
            print_table(grid[i], columns);
            printf("\n");
        }
    }
    else if (mode == 3)
    {
        clearScreen();
        printf("In progress...\n\nLines: %d  |  Columns: %d\n\n", lines, columns);
        for (int i = 0; i < lines; i++)
        {
            print_table_v2(grid[i], columns);
            printf("\n");
        }
    }
    else if (mode == 4)
    {
        printf("Lines: %d  |  Columns: %d\n\n", lines, columns);
        for (int i = 0; i < lines; i++)
        {
            print_table_v2(grid[i], columns);
            printf("\n");
        }
    }
    else
    {
        printf("\nAn error occured!\n");
    }
}