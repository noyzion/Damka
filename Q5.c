#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "projectDamka.h"


//Q5
void playGame(Board board, Player starting_player)
{
    makeBoard(board);
    turn(board, starting_player);
}


//The function make standart board
void makeBoard(Board gameBoard)
{
    Player T = 'T';
    Player B = 'B';
    int i, j, k;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        if (i != 3 && i != 4)
        {
            for (j = 0; j < BOARD_SIZE; j++)
            {
                if (i >= 0 && i < 3)
                {
                    if (i % 2 == 0 && j % 2 == 1)
                        (gameBoard)[i][j] = T;
                    else if (i % 2 == 1 && j % 2 == 0)
                        (gameBoard)[i][j] = T;
                    else
                        (gameBoard)[i][j] = ' ';
                }
                else
                {
                    if (i % 2 == 0 && j % 2 == 1)
                        (gameBoard)[i][j] = B;
                    else if (i % 2 == 1 && j % 2 == 0)
                        (gameBoard)[i][j] = B;
                    else
                        (gameBoard)[i][j] = ' ';
                }
            }
        }
        else
        {
            for (k = 0; k < BOARD_SIZE; k++)
                (gameBoard)[i][k] = ' ';
        }
    }
}