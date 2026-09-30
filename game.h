#ifndef GAME_H
#define GAME_H

#include "types.h"

void startGame(Property board[], Player players[], int order[]);
void checkSquare(Property board[], Player players[], int currentPlayer, int dice, int round);

#endif
