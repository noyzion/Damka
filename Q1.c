#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "projectDamka.h"

//Q1
//The function return tree of all the optional moves for a given source position on the board. 
SINGLE_SOURCE_MOVES_TREE* findSingleSourceMoves(Board board, CHECKERS_POS* src)
{
    int intRow = src->row - 'A'; //convert to int
    int intCol = atoi(&src->col) - 1;
    bool left = true, right = true, first = true;
    SINGLE_SOURCE_MOVES_TREE* tree = (SINGLE_SOURCE_MOVES_TREE*)malloc(sizeof(SINGLE_SOURCE_MOVES_TREE));
    if (tree == NULL)
        exit(1);
    if (board[intRow][intCol] != 'T' && board[intRow][intCol] != 'B') //if not player - no tree
        return NULL;
    else if (board[intRow][intCol] == 'T') //the player is T
        tree->source = findSingleSourceMovesHelperT(board, intRow, intCol, 0, src, left, right, first);
    else //The player is B
        tree->source = findSingleSourceMovesHelperB(board, intRow, intCol, 0, src, left, right, first);
    return tree;
}

//Recursive helper function for finding single source moves for player 'T'.
SINGLE_SOURCE_MOVES_TREE_NODE* findSingleSourceMovesHelperT(Board board, int row, int col, unsigned short total_capture, CHECKERS_POS* src, bool left, bool right, bool first)
{
    Player T = 'T', B = 'B';
    SINGLE_SOURCE_MOVES_TREE_NODE* root;

    if (!ifPlayerOrEnd(row, col, board, T, src)) //if next is player or next index is not legal
        return NULL;
    if (!isFirst(row, col, board, T, src)) //if there is ' ' on the left and on the right of the player - create the tree and return
    {
        root = createTreeNode(board, row, col, total_capture, NULL);
        if (col != 7) //end of board
            root->nextMove[0] = createTreeNode(board, row + 1, col - 1, total_capture, NULL);
        if (col != 0) //end of board
            root->nextMove[1] = createTreeNode(board, row + 1, col + 1, total_capture, NULL);
        return root;
    }
    else if (board[row][col] == ' ')
    {
        if (first == true)
        {
            root = createTreeNode(board, row, col, total_capture, NULL);
            first = false;
            return root;
        }
        root = createTreeNode(board, row, col, total_capture, NULL);
        if (row + 1 < BOARD_SIZE && col - 1 < BOARD_SIZE) //left- if next is player or next index is not legal
        {
            if (board[row + 1][col - 1] == B) //the next
                root->nextMove[0] = findSingleSourceMovesHelperT(board, row + 1, col - 1, total_capture, src, true, false, false);
        }
        if (row + 1 < BOARD_SIZE && col + 1 < BOARD_SIZE) // right-if next is player or next index is not legal
        {
            if (board[row + 1][col + 1] == B) //the next
                root->nextMove[1] = findSingleSourceMovesHelperT(board, row + 1, col + 1, total_capture, src, false, true, false);

        }
        return root;

    }
    else if (board[row][col] == B)
    {
        if (row + 1 < BOARD_SIZE && col - 1 < BOARD_SIZE && left == true) //if next is player or next index is not legal - left
        {
            if (board[row + 1][col - 1] == ' ') // the next
            {
                total_capture++;
                root = findSingleSourceMovesHelperT(board, row + 1, col - 1, total_capture, src, true, false, false);
                return root;
            }

        }
        if (row + 1 < BOARD_SIZE && col + 1 < BOARD_SIZE && right == true) //if next is player or next index is not legal - right
        {
            if (board[row + 1][col + 1] == ' ') //the next
            {
                total_capture++;
                root = findSingleSourceMovesHelperT(board, row + 1, col + 1, total_capture, src, false, true, false);
                return root;
            }
        }
        return NULL;
    }
    else //from the root
    {
        root = createTreeNode(board, row, col, total_capture, NULL);
        root->nextMove[0] = findSingleSourceMovesHelperT(board, row + 1, col - 1, total_capture, src, true, false, true);
        root->nextMove[1] = findSingleSourceMovesHelperT(board, row + 1, col + 1, total_capture, src, false, true, true);
        return root;
    }
}

//Recursive helper function for finding single source moves for player 'B'.
SINGLE_SOURCE_MOVES_TREE_NODE* findSingleSourceMovesHelperB(Board board, int row, int col, unsigned short total_capture, CHECKERS_POS* src, bool left, bool right, bool first)
{
    Player T = 'T', B = 'B';
    SINGLE_SOURCE_MOVES_TREE_NODE* root;

    if (!ifPlayerOrEnd(row, col, board, B, src)) //if next is player or next index is not legal
        return NULL;
    if (!isFirst(row, col, board, B, src)) //if there is ' ' on the left and on the right of the player - create the tree and return
    {
        root = createTreeNode(board, row, col, total_capture, NULL);
        if (col != H) //end of board
            root->nextMove[0] = createTreeNode(board, row - 1, col - 1, total_capture, NULL);

        if (col != A) //end of board
            root->nextMove[1] = createTreeNode(board, row - 1, col + 1, total_capture, NULL);
        return root;
    }
    else if (board[row][col] == ' ')
    {
        if (first == true)
        {
            root = createTreeNode(board, row, col, total_capture, NULL);
            first = false;
            return root;
        }
        root = createTreeNode(board, row, col, total_capture, NULL);
        if (row - 1 < BOARD_SIZE && col - 1 < BOARD_SIZE) //right - checking if the next is in legal index
        {
            if (board[row - 1][col - 1] == T) //the next
                root->nextMove[0] = findSingleSourceMovesHelperB(board, row - 1, col - 1, total_capture, src, true, false, false);
        }
        if (row - 1 < BOARD_SIZE && col + 1 < BOARD_SIZE) //left - checking if the next is in legal index
        {
            if (board[row - 1][col + 1] == T) //the next
                root->nextMove[1] = findSingleSourceMovesHelperB(board, row - 1, col + 1, total_capture, src, false, true, false);
        }
        return root;
    }
    else if (board[row][col] == T)
    {
        if (row - 1 < BOARD_SIZE && col + 1 < BOARD_SIZE && right == true) //left - checking if the next is in legal index
        {
            if (board[row - 1][col + 1] == ' ') //the next
            {
                total_capture++;
                root = findSingleSourceMovesHelperB(board, row - 1, col + 1, total_capture, src, false, true, false);
                return root;
            }
        }
        if (row - 1 < BOARD_SIZE && col - 1 < BOARD_SIZE && left == true) //right - checking if the next is in legal index
        {
            if (board[row - 1][col - 1] == ' ') //the next
            {
                total_capture++;
                root = findSingleSourceMovesHelperB(board, row - 1, col - 1, total_capture, src, true, false, false);
                return root;
            }
        }
        return NULL;
    }
    else //from the root
    {
        root = createTreeNode(board, row, col, total_capture, NULL);
        root->nextMove[0] = findSingleSourceMovesHelperB(board, row - 1, col - 1, total_capture, src, true, false, true);
        root->nextMove[1] = findSingleSourceMovesHelperB(board, row - 1, col + 1, total_capture, src, false, true, true);
        return root;
    }
}

//The function checks if the next move is a player or an invalid index.
bool ifPlayerOrEnd(int row, int col, Board board, Player gamer, CHECKERS_POS* src)
{
    int intRow = src->row - 'A';
    int intCol = atoi(&src->col) - 1;
    if (intRow == row && intCol == col) //if first
        return true;
    else if (board[row][col] == gamer) //if the next is the same player
        return false;
    else if (row == -1 || row == 8 || col == -1 || col == 8) //cant move right or left
        return false;
    return true;
}

//The function checkes if the player has ' ' on each side on the first iteration 
bool isFirst(int row, int col, Board board, Player gamer, CHECKERS_POS* src)
{
    int intRow = src->row - 'A';
    int intCol = atoi(&src->col);
    if (intRow == row && intCol == col) //if first
    {
        if ((board[row + 1][col - 1] == ' ' && board[row + 1][col + 1] == ' ' && gamer == 'T') ||
            (board[row - 1][col - 1] == ' ' && board[row - 1][col + 1] == ' ' && gamer == 'B'))
            return false; //end of function - build tree and return
    }
    return true;
}

//The function creates new tree node
SINGLE_SOURCE_MOVES_TREE_NODE* createTreeNode(Board board, char row, char col, unsigned short total_capture, SINGLE_SOURCE_MOVES_TREE_NODE* nextMove[2])
{
    SINGLE_SOURCE_MOVES_TREE_NODE* res = (SINGLE_SOURCE_MOVES_TREE_NODE*)malloc(sizeof(SINGLE_SOURCE_MOVES_TREE_NODE));
    if (res == NULL)
        exit(1);

    memcpy(res->board, board, sizeof(Board)); //copy the board

    res->pos = (CHECKERS_POS*)malloc(sizeof(CHECKERS_POS));
    if (res->pos == NULL)
        exit(1);

    res->pos->col = col;
    res->pos->row = row;
    res->total_captures_so_far = total_capture;

    // Initialize pointers
    res->nextMove[0] = NULL;
    res->nextMove[1] = NULL;

    if (nextMove != NULL) // alloccate memory and assign nextMove nodes
    {
        res->nextMove[0] = createTreeNode(nextMove[0]->board, nextMove[0]->pos->row, nextMove[0]->pos->col, nextMove[0]->total_captures_so_far, nextMove[0]->nextMove);
        res->nextMove[1] = createTreeNode(nextMove[1]->board, nextMove[1]->pos->row, nextMove[1]->pos->col, nextMove[1]->total_captures_so_far, nextMove[1]->nextMove);
    }
    return res;
}
