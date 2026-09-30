#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

void initializePlayers(Player players[]);
int rollDice();
void movePlayer(Player *player, int dice);
void printPlayer(Player player);
void printAllPlayers(Player players[]);
void releaseBankruptProperties(Player *player, Property board[], int playerID);
int calculateNetWorth(Property board[], Player players[], int playerID);
int updateBankruptcyState(Player players[], Property board[], int playerID);
int checkWinner(Player players[]);
void determinePlayerOrder(Player players[], int order[]);

int shouldBuyProperty(Player *player, Property *property);
int getMaximumBid(Player *player, Property *property);
InsuranceType chooseInsurance(Player *player, Property *property);
int handleJail(Player *player);

#endif
