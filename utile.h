// #############################################################################
// # File utile.h
// # UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#ifndef H_UTIL
#define H_UTIL

void table_content(int *tab, int n);

/* Initialiazing everything to DEFAULT (nothing) */
void initialize1D(int *tab, int n);

/* Initialiazing everything on a 2D table to DEFAULT (nothing) */
void initialize2D(int **table, int rows, int cols);

/* Returns the max of two numbers */
int max(int x, int y);

/* Caracter to int */
int ctoi(int c);

/* Reverses an array of numbers */
void reverse(int l, int h, int *arr);

/* Returns if a charcater is a digit (number) or not */
bool is_digit(char ch);

/* For debugging purposes */
void print_line(int *tab, int n);

#endif