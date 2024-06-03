//Dana Reshef 314652439 Noy Zion 212198766 - Project Damka

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "projectDamka.h"

int main()
{
    Board board;
    Player starting_player;
    printf("Please enter player: ");
    scanf("%c", &starting_player);
    playGame(board, starting_player);

}









