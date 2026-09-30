#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"
#include "board.h"
#include "player.h"
#include "game.h"

int main()
{
    printf("\nMONOPOLY-LK Simulation\n");
    printf("\n");
    printf("Player 1: Aggressive Investor\n");
    printf("Player 2: Conservative Banker\n");
    printf("Player 3: Risk Taker\n");
    printf("Player 4: Opportunistic Trader\n");
    printf("\n");
    printf("Each player starts with LKR 30,000.\n");

    Property board[BOARD_SIZE];
    Player players[MAX_PLAYERS];

    srand(time(NULL));

    initializeBoard(board);
    initializePlayers(players);

    int order[MAX_PLAYERS];
    determinePlayerOrder(players, order);
    startGame(board, players, order);

    return 0;
}
