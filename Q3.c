#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "projectDamka.h"


//Q3
//The function finds all possible moves for a player on the board.
MULTIPLE_SOURCE_MOVES_LIST* findAllPossiblePlayerMoves(Board board, Player player)
{
    int i, j;
    MULTIPLE_SOURCE_MOVES_LIST* res = (MULTIPLE_SOURCE_MOVES_LIST*)malloc(sizeof(MULTIPLE_SOURCE_MOVES_LIST));
    SINGLE_SOURCE_MOVES_LIST* data;
    SINGLE_SOURCE_MOVES_TREE* boardTree;
    CHECKERS_POS pos;

    if (res == NULL)
        exit(1);
    makeEmptyMultiList(res);
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == player) //if found player on the board
            {
                pos.col = j + '0' + 1;
                pos.row = i + 'A';
                boardTree = findSingleSourceMoves(board, &pos); //build tree of all the optional moves
                data = findSingleSourceOptimalMove(boardTree); //find the best move from the tree and make list
                freeTree(boardTree);
                if (data != NULL)
                    insertMultipleToEndList(res, data); //insert to the new list
            }
        }
    }
    return res;

}

//list functions
//The function inserts a new single source moves list to the end of the multiple source moves list.
void insertMultipleToEndList(MULTIPLE_SOURCE_MOVES_LIST* res, SINGLE_SOURCE_MOVES_LIST* data)
{

    MULTIPLE_SOURCE_MOVES_LIST_CELL* newTail;
    newTail = createMultipleNewNode(data, NULL);
    insertNodeMultiToEndList(res, newTail);
}

//The function inserts a new node at the end of a multiple source moves list.
void insertNodeMultiToEndList(MULTIPLE_SOURCE_MOVES_LIST* res, MULTIPLE_SOURCE_MOVES_LIST_CELL* newTail)
{
    if (isEmptyMultiList(res))
        res->head = res->tail = newTail;
    else
    {
        res->tail->next = newTail;
        res->tail = newTail;
    }
    newTail->next = NULL;
}

//the function make empty list
void makeEmptyMultiList(MULTIPLE_SOURCE_MOVES_LIST* lst)
{
    lst->head = lst->tail = NULL;
}

//The function checkes if list is empty
bool isEmptyMultiList(MULTIPLE_SOURCE_MOVES_LIST* res)
{
    if (res->head == NULL)
        return true;
    else
        return false;
}

//The function creates a new node for a multiple source moves list.
MULTIPLE_SOURCE_MOVES_LIST_CELL* createMultipleNewNode(SINGLE_SOURCE_MOVES_LIST* data, MULTIPLE_SOURCE_MOVES_LIST_CELL* next)
{
    MULTIPLE_SOURCE_MOVES_LIST_CELL* newNode = (MULTIPLE_SOURCE_MOVES_LIST_CELL*)malloc(sizeof(MULTIPLE_SOURCE_MOVES_LIST_CELL));
    if (newNode == NULL)
        exit(1);

    newNode->single_source_moves_list = data;
    newNode->next = next;

    return newNode;
}

//The function free tree
void freeTree(SINGLE_SOURCE_MOVES_TREE* boardTree)
{
    freeHelper(boardTree->source);
    boardTree->source = NULL;
}

//recursive helper
void freeHelper(SINGLE_SOURCE_MOVES_TREE_NODE* root)
{
    if (root == NULL)
        return;
    else
    {
        freeHelper(root->nextMove[0]);
        freeHelper(root->nextMove[1]);
        free(root->pos);
        free(root);

    }
}
