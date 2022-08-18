#include <stdio.h>
#include <stdlib.h>

#include "sudoku.h"

int** SetBoard()
{
    int i, j;
    int** puzzleBoard;
    int board[9][9] = {9, 0, 6,  9, 1, 3,  0, 0, 8,
                       0, 5, 8,  0, 0, 0,  0, 9, 0,
                       0, 3, 0,  0, 0, 0,  0, 1, 0,
                       
                       0, 6, 0,  8, 0, 0,  9, 2, 0,
                       0, 0, 3,  4, 0, 9,  1, 0, 0,
                       0, 4, 9,  0, 0, 6,  0, 3, 0,
                       
                       0, 9, 0,  0, 0, 0,  0, 8, 0,
                       0, 1, 0,  0, 0, 0,  6, 7, 0,
                       4, 0, 0,  9, 6, 0,  3, 0, 1};

    puzzleBoard = (int**)malloc(sizeof(int*) * 9);

    for(i = 0; i <= 8; i++)
    {
        puzzleBoard[i] = (int*)malloc(sizeof(int*) * 9); 
        for(j = 0; j <= 8; j++)
        {
            puzzleBoard[i][j] = board[i][j];
        }
    }
    return puzzleBoard;
}

void PrintBoard(int** board)
{
    int i, j, k;
    char positions[] = " 0 | 1  2  3 | 4  5  6 | 7  8  9 | x\n";
    printf("\n");
    printf("%s", positions);
    printf(" ---------------------------------\n");
    
    for (i = 0, k = 1; i <= 8; i++, k++)
    {
        for(j = 0; j <= 8; j++)
        {
            if (j == 0){
                printf(" %d |", k);
            }
            else if ((j) % 3 == 0){
                printf("|");
            }
            printf(" %d ", board[i][j]);
            if (j == 8){
                printf("|");
            }
        }
        printf("\n");
        if ((i + 1) % 3 == 0){
            printf(" ---------------------------------\n");
        }
    }
    printf(" y\n");
}

int isAvailable(int** board, int* row, int* col)
{
    int i, j;
    for(i = 0; i <= 8; i++)
    {
        for(j = 0; j <= 8; j++)
        {
            if(board[i][j] == 0){
                *row = i;
                *col = j;
                return 1;
            }
        }
    }
    return 0;
}

int isCorrect(int** board, int row, int col, int input)
{
    int i, j, srow, scol;

    for(i = 0; i <= 8; i++)
    {
        if(board[i][col] == input){
            return 0;
        }
    }

    for(j = 0; j <= 8; j++)
    {
        if(board[row][j] == input){
            return 0;
        }
    }

    srow = row - row % 3;
    scol = col - col % 3;

    for(i = 0; i <= 2; i++)
    {
        for(j = 0; j <= 2; j++)
        {
            if(board[srow + i][scol + j] == input){
                return 0;
            }
        }
    }
        
    return 1;
}

int solution(int** board)
{
    int i, j, input;

    if(!isAvailable(board, &i, &j)){
        return 1;
    }

    for(input = 1; input <= 9; input++)
    {
        if(isCorrect(board, i, j, input)){
            board[i][j] == input;
            if(solution(board)){
                return 1;
            }
            else{
                board[i][j] == 0;
            }
        }
    }
    return 0;
}

int** copyBoard(int** board)
{
    int i, j;
    int** newBoard;

    newBoard = (int**)malloc(sizeof(int*) * 9);
    for (i = 0; i < 9; i++)
    {
        newBoard[i] = (int*)malloc(sizeof(int) * 9);
        for(j = 0; j < 9; j++)
        {
            newBoard[i][j] = board[i][j];
        }
    }
    return newBoard;
}

void player(int** playerBoard, int** tempBoard) {
    int i, j, x, y, uinput;
    char option;

    while (1) {
        if (!isAvailable(playerBoard, &i, &j)) {
            printf("\n Sudoku Board Completed! Congrats :)");
        }

        while (1) {
            printf("\nPress Enter to continue. Press \"q\" to Quit.\n");
            option = getchar();
            if ((option == 'q') || (option == 'Q')) {
                getchar();
                solution(playerBoard);
                printf("\nSOLVED PUZZLE:\n");
                PrintBoard(playerBoard);
                return;
            } else if ((option != '\n') && (option != 'q')) {
                getchar();
            } else {
                break;
            }
        }

        printf("\nEnter a coordinate for the square you want to insert the value to in the following format \"x y\":\n");
        scanf("%d %d", &x, &y);
        while (1) {
            if ((x > 9) || (x < 1) || (y > 9) || (y < 1) || (playerBoard[y - 1][x - 1] != 0)) {
                printf("\nInvalid coordinate, please pick a new coordinate\n");
                scanf("%d %d", &x, &y);
            } else {
                x -= 1;
                y -= 1;
                break;
            }
        }

        printf("\nInsert a value from 1 to 9\n");
        scanf("%d", &uinput);

        while (1) {
            if ((uinput > 9) || (uinput < 1)) {
                printf("\nInvalid value, try again:\n");
                scanf("%d", &uinput);
            } else {
                break;
            }
        }

        if (isCorrect(playerBoard, y, x, uinput)) {
            playerBoard[y][x] = uinput;
        } else {
            printf("\nincorrect value for the x = %d y = %d coordinate, please try again\n", x + 1, y + 1);
        }

        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                tempBoard[i][j] = playerBoard[i][j];
            }
        }

        if (!solution(tempBoard)) {
            printf("\nincorrect value for the X = %d Y = %d coordinate, please try again\n", x + 1, y + 1);
            playerBoard[y][x] = 0;
        }
        getchar();
        PrintBoard(playerBoard);

        return;
    }
}



