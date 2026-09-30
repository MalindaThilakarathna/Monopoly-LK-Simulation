#ifndef FINANCE_H
#define FINANCE_H

#include "types.h"

// Property related functions
void buyProperty(Property *property, Player *player, int playerID);
void payRent(Property *property, Player players[], int currentPlayer, int dice, int round);
void buildHouse(Property board[], Property *property, Player *player, int round);
void buildHotel(Property *property, Player *player);
int hasMonopoly(Property board[], Player player, PropertyGroup group);

int calculateRent(Property property, int round);
int calculateRailwayRent(Player player, int round);
int calculateUtilityRent(Player player, int dice, int round);

// Bank and Loan Management (Rule-LK 1 to 7)
void processBank(Player *player, Property board[], int playerID);
void obtainLoan(Player *player, Property board[], int playerID);
void repayLoan(Player *player, Property board[], int playerID, int amount);
void repayFullLoan(Player *player, Property board[], int playerID);
void refinanceLoan(Player *player);
void increaseLoan(Player *player, Property board[], int playerID);
void addLoanInterest(Player players[], Property board[]);
void checkLoanDefault(Player *player, Property board[], int playerID);

// Insurance related functions
void buyInsurance(Player *player, Property *property, InsuranceType type, int round);
void checkInsuranceExpiry(Player players[], Property board[], int round);

// Auction
void auctionProperty(Property *property, Player players[]);
int getMaximumBid(Player *player, Property *property);

// Property Depreciation & Renovation 
void processPropertyDepreciation(Property board[]);
void renovateProperty(Property *property, Player *player);

#endif
