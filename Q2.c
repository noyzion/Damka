#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "projectDamka.h"


//Q2
//The function finds the optimal move from a single source moves tree - the longest or the most right best move
SINGLE_SOURCE_MOVES_LIST* findSingleSourceOptimalMove(SINGLE_SOURCE_MOVES_TREE* moves_tree)
{
    Player T = 'T', B = 'B';
    bool right = false;
    bool left = false;
    if (moves_tree->source->nextMove[0] == NULL && moves_tree->source->nextMove[1] == NULL)
        return NULL;
    int counter = 0;
    unsigned short saver_cap = 0;
    SINGLE_SOURCE_MOVES_LIST* res = (SINGLE_SOURCE_MOVES_LIST*)malloc(sizeof(SINGLE_SOURCE_MOVES_LIST));
    if (res == NULL)
        exit(1);
    makeEmptyList(res);
    if (moves_tree->source->board[moves_tree->source->pos->row][moves_tree->source->pos->col] == T)
        findSingleSourceOptimalMoveHelperA(moves_tree->source, res, &saver_cap, NULL, counter, right);
    else
        findSingleSourceOptimalMoveHelperB(moves_tree->source, res, &saver_cap, NULL, counter, left);

    return res;

}

//The function recursive helper function for finding the optimal move. - for player T
void findSingleSourceOptimalMoveHelperA(SINGLE_SOURCE_MOVES_TREE_NODE* root, SINGLE_SOURCE_MOVES_LIST* res, unsigned short* saver_cap, SINGLE_SOURCE_MOVES_LIST_CELL* saverLst, int counter, bool right)
{
    if (root == NULL)
        return;
    else if (root->total_captures_so_far > *saver_cap) //find longer
    {
        if (counter == 1 && right)
            freeTillHead(res);
        *saver_cap = root->total_captures_so_far;
        insertMovesToEndList(res, root->pos, root->total_captures_so_far);
        saverLst = res->tail;
    }
    else if (root->total_captures_so_far == *saver_cap)
    {
        if (counter != 1) // checks if the list include only the root - and if this is the case it dont free it
        { //because the root is always in the list
            freeNode(res->tail); //free the end of the list
            res->tail = saverLst; //put new end - the saver
        }
        insertMovesToEndList(res, root->pos, root->total_captures_so_far);
        saverLst = res->tail;
    }
    findSingleSourceOptimalMoveHelperA(root->nextMove[0], res, saver_cap, saverLst, counter + 1, false);
    findSingleSourceOptimalMoveHelperA(root->nextMove[1], res, saver_cap, saverLst, counter + 1, true);
}

//The function free the list except the head
void freeTillHead(SINGLE_SOURCE_MOVES_LIST* lst)
{
    SINGLE_SOURCE_MOVES_LIST_CELL* curr = lst->head->next;
    SINGLE_SOURCE_MOVES_LIST_CELL* saver;

    while (curr != NULL)
    {
        saver = curr->next;
        free(curr);
        curr = saver;
    }
    lst->head->next = NULL;
    lst->tail = lst->head;
}

//The function recursive helper function for finding the optimal move. - for player B
void findSingleSourceOptimalMoveHelperB(SINGLE_SOURCE_MOVES_TREE_NODE* root, SINGLE_SOURCE_MOVES_LIST* res, unsigned short* saver_cap, SINGLE_SOURCE_MOVES_LIST_CELL* saverLst, int counter, bool left)
{
    if (root == NULL)
        return;
    else if (root->total_captures_so_far > *saver_cap) //find longer
    {
        if (counter == 1 && left) //find more captures on the other side
            freeTillHead(res);
        *saver_cap = root->total_captures_so_far;
        insertMovesToEndList(res, root->pos, root->total_captures_so_far);
        saverLst = res->tail;
    }
    else if (root->total_captures_so_far == *saver_cap)
    {
        if (counter != 1) // checks if the list include only the root - and if this is the case it dont free it
        { //because the root is always in the list
            freeNode(res->tail); //free the end of the list
            res->tail = saverLst; //put new end - the saver
        }
        insertMovesToEndList(res, root->pos, root->total_captures_so_far);
        saverLst = res->tail;
    }
    findSingleSourceOptimalMoveHelperB(root->nextMove[1], res, saver_cap, saverLst, counter + 1, false);
    findSingleSourceOptimalMoveHelperB(root->nextMove[0], res, saver_cap, saverLst, counter + 1, true);

}

//the function make empty list
void makeEmptyList(SINGLE_SOURCE_MOVES_LIST* list)
{
    list->head = list->tail = NULL;
}

//the function free node from the list
void freeNode(SINGLE_SOURCE_MOVES_LIST_CELL* node)
{
    if (node == NULL)
        return;
    free(node->position);
    free(node);

}

//The function inserts a new move to the end of the single source moves list.
void insertMovesToEndList(SINGLE_SOURCE_MOVES_LIST* res, CHECKERS_POS* pos, unsigned short total_cap)
{
    SINGLE_SOURCE_MOVES_LIST_CELL* newTail;
    newTail = createNewNode(pos, total_cap, NULL);
    insertNodeToEndList(res, newTail);
}

//The function inserts a new node to the end of the single source moves list.
void insertNodeToEndList(SINGLE_SOURCE_MOVES_LIST* res, SINGLE_SOURCE_MOVES_LIST_CELL* newTail)
{
    if (isEmptyList(res))
        res->head = res->tail = newTail;
    else
    {
        res->tail->next = newTail;
        res->tail = newTail;
    }
    newTail->next = NULL;
}

//Thr function checkes if list is empty
bool isEmptyList(SINGLE_SOURCE_MOVES_LIST* res)
{
    if (res->head == NULL)
        return true;
    else
        return false;
}

//The function creates a new node for the single source moves list.
SINGLE_SOURCE_MOVES_LIST_CELL* createNewNode(CHECKERS_POS* pos, unsigned short total_cap, SINGLE_SOURCE_MOVES_LIST_CELL* next)
{
    SINGLE_SOURCE_MOVES_LIST_CELL* newNode = (SINGLE_SOURCE_MOVES_LIST_CELL*)malloc(sizeof(SINGLE_SOURCE_MOVES_LIST_CELL));
    if (newNode == NULL)
        exit(1);

    newNode->captures = total_cap;
    newNode->position = (CHECKERS_POS*)malloc(sizeof(CHECKERS_POS));
    if (newNode->position == NULL)
        exit(1);
    newNode->position->col = pos->col;
    newNode->position->row = pos->row;
    newNode->next = next;

    return newNode;
}
