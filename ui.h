// #############################################################################
// # File ui.h
// # UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#ifndef H_UI
#define H_UI

/* Gives a user the choice of the exercise */
int menu_mode();

/* Printing the different arrays for testing purposes */
void print_table(int *tab, int n);

void print_table_v2(int *tab, int n);

/* Clearing the terminal screen for more optimised visualisations */
void clearScreen();

/* Time counting decision menu */
int midle_menu();

/* Simple printing function for visualisations puproses */
void printing_grid(int **grid, int lines, int columns, int mode);

#endif