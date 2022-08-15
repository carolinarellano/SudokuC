#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main()
{
    int** board = SetBoard();
    int** playerBoard = copyBoard(board);
    int** tempBoard = copyBoard(board);
    printf("RULES:\n\n");
    printf("1. The objective of Sudoku is to fill a 9x9 grid made of small squares so that each row, each column, and each full 3x3 squares use the numbers 1-9.\n");
    printf("2. While solving the sudoku puzzle you can only use each number one time in the square, column, and row.\n");
    printf("3. You can only insert numbers in the squares that have value \"0\"\n");
    printf("4. If you give up and want to see a solved puzzle please press \"q\" key.\n\n");
    printf("GOOD LUCK!\n");
    PrintBoard(playerBoard);
    player(playerBoard,tempBoard);
    free(board);
    free(playerBoard);
    free(tempBoard);
}