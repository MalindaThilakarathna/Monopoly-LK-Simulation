#ifndef EVENT_H
#define EVENT_H

#include "types.h"

// National Event Cards 
void nationalEventCard(int currentCardID, Property board[], Player players[], int currentPlayer, int round);
void drawEventCard(Property board[], Player players[], int currentPlayer, int round);
void applyExpiredEventEffects(Property board[], Player players[], int round);

// Inflation Engine 
void applyInflation(Property board[], int round);
int getCurrentInflationRate(void);
int getCurrentBaseInterestRate(void);

// Dynamic Property Market 
void updatePropertyMarket(Property board[], int round);

// Event State
int getLoanInterestRateModifier(void);
int getInsurancePremiumReductionPercent(void);
int isTourismHypeActive(int round);
int isFuelShortageActive(int round);
int isPowerFailureActive(int round);
int isFestivalSeasonActive(int round);
int isLabourStrikeActive(int round);
int isHousingSubsidyActive(int round);

// Regional Development Cards 
void drawRegionalDevelopmentCard(Property board[], int round);
int getActiveRegionalCard(void);
int getRegionalRoundsRemaining(int round);
void applyExpiredRegionalDevelopmentCards(Property board[], Player players[], int round);

//Government Regulations
void triggerGovernmentRegulation(Property board[], Player players[], int round);

#endif
