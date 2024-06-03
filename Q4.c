#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "projectDamka.h"


//Q4
//the function find the best the best move from the multiple source moves to the player and change the board according to this move
void turn(Board board, Player player)
{
    Player nowPlayerT = 'T', nowPlayerB = 'B';
    SINGLE_SOURCE_MOVES_LIST* max = (SINGLE_SOURCE_MOVES_LIST*)malloc(sizeof(SINGLE_SOURCE_MOVES_LIST));
    MULTIPLE_SOURCE_MOVES_LIST* res;
    if (max == NULL)
        exit(1);
    makeEmptyList(max);
    int movesT = 0, movesB = 0, capturesT = 0, capturesB = 0, maxCapT = 0, maxCapB = 0;
    bool winT = false, winB = false;
    printBoard(board); //standart board

    while (!winB && !winT)
    {
        if (player == nowPlayerT)
        {
            res = findAllPossiblePlayerMoves(board, player);
            max = findBestMoveOptionT(board, res, &winT);
            if (max == NULL)
                winB = true;
            else
            {
                removeMaxFromBoardT(board, max, player, &capturesT);
                if (maxCapT < capturesT)
                    maxCapT = capturesT;
                printf("T's turn:\n");
                convertAndPrint(board, max);
                movesT++;
            }
            freeMult(res); //max is part of res and the function free both of them
            player = nowPlayerB;
        }
        else //turn B
        {
            res = findAllPossiblePlayerMoves(board, player);
            max = findBestMoveOptionB(board, res, &winB);
            if (max == NULL)
                winT = true;
            else
            {
                removeMaxFromBoardB(board, max, player, &capturesB);
                if (maxCapB < capturesB)
                    maxCapB = capturesB;
                printf("B's turn:\n");
                convertAndPrint(board, max);
                movesB++;

            }
            freeMult(res); //max is part of res and the function free both of them
            player = nowPlayerT;
        }
    }
    printWinner(winB, winT, maxCapB, maxCapT, movesT, movesB);
}

//The function print the winner and the max captures
void printWinner(bool winB, bool winT, int maxCapB, int maxCapT, int movesT,int movesB)
{
    if (winB)
    {
        printf("B wins!\n");
        printf("B performed %d moves.\n", movesB);

    }
    else //T wins
    {
        printf("T wins!\n");
        printf("T performed %d moves.\n", movesT);
    }
    if (maxCapB > maxCapT)
        printf("B performed the highest number of captures in a single move - %d\n", maxCapB);
    else
        printf("T performed the highest number of captures in a single move - %d\n", maxCapT);

}
//The function convert thr src and print the move and board
void convertAndPrint(Board board, SINGLE_SOURCE_MOVES_LIST* max)
{
    char charRowHead, charRowTail;
    int intColHead, intColTail;

    charRowHead = max->head->position->row + 'A';
    intColHead = (int)max->head->position->col + 1;
    charRowTail = max->tail->position->row + 'A';
    intColTail = (int)max->tail->position->col + 1;
    printf("%c%d->%c%d\n", charRowHead, intColHead, charRowTail, intColTail);
    printBoard(board);


}

//The function change the board according to the best move - for player T
void removeMaxFromBoardT(Board board, SINGLE_SOURCE_MOVES_LIST* max, Player player, int* capturesT)
{

    SINGLE_SOURCE_MOVES_LIST_CELL* curr = max->head->next;
    SINGLE_SOURCE_MOVES_LIST_CELL* prev = max->head;
    *capturesT = 0;
    while (curr != NULL)
    {
        if (curr->captures > 0)
        {
            if (prev->position->col < curr->position->col)
            {
                board[prev->position->row + 1][prev->position->col + 1] = ' ';
                (*capturesT) += 1;
            }
            else
            {
                board[prev->position->row + 1][prev->position->col - 1] = ' ';
                (*capturesT) += 1;
            }
        }
        prev = curr;
        curr = curr->next;

    }
    board[max->head->position->row][max->head->position->col] = ' ';
    board[max->tail->position->row][max->tail->position->col] = player;

}

//The function change the board according to the best move - for player B
void removeMaxFromBoardB(Board board, SINGLE_SOURCE_MOVES_LIST* max, Player player, int* capturesB)
{
    *capturesB = 0;
    SINGLE_SOURCE_MOVES_LIST_CELL* curr = max->head->next;
    SINGLE_SOURCE_MOVES_LIST_CELL* prev = max->head;


    while (curr != NULL)
    {
        if (curr->captures > 0)
        {
            if (prev->position->col < curr->position->col)
            {
                board[prev->position->row - 1][prev->position->col + 1] = ' ';
                (*capturesB) += 1;
            }
            else
            {
                board[prev->position->row - 1][prev->position->col - 1] = ' ';
                (*capturesB) += 1;
            }

        }
        prev = curr;
        curr = curr->next;

    }
    board[max->head->position->row][max->head->position->col] = ' ';
    board[max->tail->position->row][max->tail->position->col] = player;

}


//The function find the best move from the multiple source moves to player T
SINGLE_SOURCE_MOVES_LIST* findBestMoveOptionT(Board board, MULTIPLE_SOURCE_MOVES_LIST* res, bool* win)
{
    SINGLE_SOURCE_MOVES_LIST* max = res->head->single_source_moves_list;
    MULTIPLE_SOURCE_MOVES_LIST_CELL* curr = res->head->next;
    while (curr != NULL)
    {
        if (max->tail->captures < curr->single_source_moves_list->tail->captures)
            max = curr->single_source_moves_list;
        else if (max->tail->captures == curr->single_source_moves_list->tail->captures)
        {
            if (max->head->position->row < curr->single_source_moves_list->head->position->row)
                max = curr->single_source_moves_list;
            else if (max->head->position->row == curr->single_source_moves_list->head->position->row)
            {
                if (max->head->position->col < curr->single_source_moves_list->head->position->col)
                    max = curr->single_source_moves_list;
            }
        }
        if (curr->single_source_moves_list->tail->position->row == H) // end of game
        {
            max = curr->single_source_moves_list;
            *win = true;
            return max;
        }
        if (max->tail->position->row == H) // end of game
        {
            *win = true;
            return max;
        }
        curr = curr->next;
    }
    *win = false;
    return max;

}

//The function find the best move from the multiple source moves to player B
SINGLE_SOURCE_MOVES_LIST* findBestMoveOptionB(Board board, MULTIPLE_SOURCE_MOVES_LIST* res, bool* win)
{
    SINGLE_SOURCE_MOVES_LIST* max = res->head->single_source_moves_list;
    MULTIPLE_SOURCE_MOVES_LIST_CELL* curr = res->head->next;

    while (curr != NULL)
    {

        if (max->tail->captures < curr->single_source_moves_list->tail->captures)
            max = curr->single_source_moves_list;
        else if (max->tail->captures == curr->single_source_moves_list->tail->captures)
        {
            if (max->head->position->row > curr->single_source_moves_list->head->position->row)
                max = curr->single_source_moves_list;
            else if (max->head->position->row == curr->single_source_moves_list->head->position->row)
            {
                if (max->head->position->col > curr->single_source_moves_list->head->position->col)
                    max = curr->single_source_moves_list;
            }
        }
        if (curr->single_source_moves_list->tail->position->row == A) // end of game
        {
            max = curr->single_source_moves_list;
            *win = true;
            return max;
        }
        if (max->tail->position->row == A) // end of game
        {
            *win = true;
            return max;
        }
        curr = curr->next;
    }
    *win = false;
    return max;

}

//The function print the board
void printBoard(Board gameBoard)
{
    int i, j;
    char row = 'A';
    printf("+-+-+-+-+-+-+-+-+-+\n");
    printf("+ |1|2|3|4|5|6|7|8|\n");
    printf("+-+-+-+-+-+-+-+-+-+\n");
    for (i = 0; i < BOARD_SIZE; i++)
    {
        printf("|%c|", row + i);

        for (j = 0; j < BOARD_SIZE; j++)
        {
            printf("%c|", gameBoard[i][j]);
        }
        printf("\n+-+-+-+-+-+-+-+-+-+\n");

    }

}

//the function free multiple list
void freeMult(MULTIPLE_SOURCE_MOVES_LIST* lst)
{
    MULTIPLE_SOURCE_MOVES_LIST_CELL* curr = lst->head;
    MULTIPLE_SOURCE_MOVES_LIST_CELL* saver;
    if (lst->head == NULL)
        return;
    while (curr != NULL)
    {
        saver = curr->next;
        freeList(curr->single_source_moves_list);
        free(curr);
        curr = saver;
    }
}

//the function free list
void freeList(SINGLE_SOURCE_MOVES_LIST* lst)
{

    SINGLE_SOURCE_MOVES_LIST_CELL* curr = lst->head;
    SINGLE_SOURCE_MOVES_LIST_CELL* saver;
    if (lst->head == NULL)
        return;
    while (curr != NULL)
    {
        saver = curr->next;
        free(curr);
        curr = saver;
    }

}