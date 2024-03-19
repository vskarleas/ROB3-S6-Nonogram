// #############################################################################
// # File utile.c
// # UE Infomatics for Robotics - Polytech Sorbonne - 2023/2024 - S6
// # Authors: Yanis Sadoun, Vasileios Filippos Skarleas - All rights reserved.
// #############################################################################

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "utile.h"
#include "constants.h"

void table_content(int *tab, int n)
{
    int i;
    for (i = 0; i < n - 1; i++)
    {
        printf(" %d |", tab[i]);
    }
    printf(" %d ", tab[n - 1]);
}

/* Initialiazing everything to DEFAULT (nothing) */
void initialize1D(int *tab, int n)
{
    for (int i = 0; i < n; i++)
    {
        tab[i] = DEFAULT;
    }
}

/* Initialiazing everything on a 2D table to DEFAULT (nothing) */
void initialize2D(int **table, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            table[i][j] = DEFAULT;
        }
    }
}

/* Returns the max of two numbers */
int max(int x, int y)
{
    if (x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

/* Caracter to int */
int ctoi(int c)
{
    return c - '0';
}

/* Reverses an array of numbers */
void reverse(int l, int h, int *arr)
{
    if (l >= h)
    {
        return;
    }
    int temp;
    temp = arr[l];
    arr[l] = arr[h];
    arr[h] = temp;
    reverse(l + 1, h - 1, arr); // recursive call
}

/* Returns if a charcater is a digit (number) or not */
bool is_digit(char ch)
{
    if (ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9')
    {
        return true;
    }
    else
    {
        return false;
    }
    //It can be replaved fro the C function isDigir directly
}

/* For debugging purposes */
void print_line(int *tab, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
}