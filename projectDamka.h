#ifndef __PROJECT__DAMKA
#define __PROJECT__DAMKA
#include "structs.h"

//Q1
SINGLE_SOURCE_MOVES_TREE* findSingleSourceMoves(Board board, CHECKERS_POS* src);
SINGLE_SOURCE_MOVES_TREE_NODE* findSingleSourceMovesHelperT(Board board, int row, int col, unsigned short total_capture, CHECKERS_POS* src, bool left, bool right, bool first);
SINGLE_SOURCE_MOVES_TREE_NODE* findSingleSourceMovesHelperB(Board board, int row, int col, unsigned short total_capture, CHECKERS_POS* src, bool left, bool right, bool first);
bool ifPlayerOrEnd(int row, int col, Board board, Player gamer, CHECKERS_POS* src);
SINGLE_SOURCE_MOVES_TREE_NODE* createTreeNode(Board board, char row, char col, unsigned short total_capture, SINGLE_SOURCE_MOVES_TREE_NODE* nextMove[2]);
bool isFirst(int row, int col, Board board, Player gamer, CHECKERS_POS* src);

//Q2
void makeEmptyList(SINGLE_SOURCE_MOVES_LIST* list);
SINGLE_SOURCE_MOVES_LIST* findSingleSourceOptimalMove(SINGLE_SOURCE_MOVES_TREE* moves_tree);
void findSingleSourceOptimalMoveHelperA(SINGLE_SOURCE_MOVES_TREE_NODE* root, SINGLE_SOURCE_MOVES_LIST* res, unsigned short* saver_cap, SINGLE_SOURCE_MOVES_LIST_CELL* saverLst, int counter, bool right);
void findSingleSourceOptimalMoveHelperB(SINGLE_SOURCE_MOVES_TREE_NODE* root, SINGLE_SOURCE_MOVES_LIST* res, unsigned short* saver_cap, SINGLE_SOURCE_MOVES_LIST_CELL* saverLst, int counter, bool left);
void freeNode(SINGLE_SOURCE_MOVES_LIST_CELL* node);
void freeTillHead(SINGLE_SOURCE_MOVES_LIST* lst);
void insertMovesToEndList(SINGLE_SOURCE_MOVES_LIST* res, CHECKERS_POS* pos, unsigned short total_cap);
SINGLE_SOURCE_MOVES_LIST_CELL* createNewNode(CHECKERS_POS* pos, unsigned short total_cap, SINGLE_SOURCE_MOVES_LIST_CELL* next);
void insertNodeToEndList(SINGLE_SOURCE_MOVES_LIST* res, SINGLE_SOURCE_MOVES_LIST_CELL* newTail);
bool isEmptyList(SINGLE_SOURCE_MOVES_LIST* res);

//Q3
MULTIPLE_SOURCE_MOVES_LIST* findAllPossiblePlayerMoves(Board board, Player player);
void insertMultipleToEndList(MULTIPLE_SOURCE_MOVES_LIST* res, SINGLE_SOURCE_MOVES_LIST* data);
void insertNodeMultiToEndList(MULTIPLE_SOURCE_MOVES_LIST* res, MULTIPLE_SOURCE_MOVES_LIST_CELL* newTail);
void makeEmptyMultiList(MULTIPLE_SOURCE_MOVES_LIST* lst);
bool isEmptyMultiList(MULTIPLE_SOURCE_MOVES_LIST* res);
MULTIPLE_SOURCE_MOVES_LIST_CELL* createMultipleNewNode(SINGLE_SOURCE_MOVES_LIST* data, MULTIPLE_SOURCE_MOVES_LIST_CELL* next);
void freeTree(SINGLE_SOURCE_MOVES_TREE* boardTree);
void freeHelper(SINGLE_SOURCE_MOVES_TREE_NODE* root);

//Q4
void turn(Board board, Player player);
SINGLE_SOURCE_MOVES_LIST* findBestMoveOptionT(Board board, MULTIPLE_SOURCE_MOVES_LIST* res, bool* win);
SINGLE_SOURCE_MOVES_LIST* findBestMoveOptionB(Board board, MULTIPLE_SOURCE_MOVES_LIST* res, bool* win);
void removeMaxFromBoardB(Board board, SINGLE_SOURCE_MOVES_LIST* max, Player player, int* capturesB);
void removeMaxFromBoardT(Board board, SINGLE_SOURCE_MOVES_LIST* max, Player player, int* capturesT);
void convertAndPrint(Board board, SINGLE_SOURCE_MOVES_LIST* max);
void printWinner(bool winB, bool winT, int maxCapB, int maxCapT, int movesT, int movesB);
void printBoard(Board gameBoard);
void freeMult(MULTIPLE_SOURCE_MOVES_LIST* lst);
void freeList(SINGLE_SOURCE_MOVES_LIST* lst);

//Q5
void playGame(Board board, Player starting_player);
void makeBoard(Board gameBoard);


#endif //__PROJECT__DAMKA