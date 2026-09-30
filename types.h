#ifndef TYPES_H
#define TYPES_H

#define BOARD_SIZE 40
#define MAX_PLAYERS 4

// Types of board squares 
typedef enum
{
    GO,
    PROPERTY,
    RAILWAY,
    UTILITY,
    TAX,
    EVENT,
    INSURANCE,
    BANK,
    JAIL,
    FREE_PARKING,
    GO_TO_JAIL
} SquareType;

// Property colour groups
typedef enum
{
    NONE,
    BROWN,
    LIGHT_BLUE,
    PINK,
    ORANGE,
    RED,
    YELLOW,
    GREEN,
    DARK_BLUE
} PropertyGroup;

typedef enum 
{
    NO_INSURANCE,
    BASIC_INSURANCE,
    COMPREHENSIVE_INSURANCE,
    BUSINESS_INSURANCE
} InsuranceType;

// Board square 
typedef struct
{
    char name[50];
    SquareType type;
    PropertyGroup group;

    int price;
    int rent;
    int houseCost;
    int hotelCost;
    int mortgage;
    int owner;
    int houses;
    int hotel;
    int mortgaged;

    InsuranceType insurance;
    int insuranceExpiry;

    int isLoanLocked;

    int age;
    int depreciation; // Depreciation percentage (0% up to 30%)
} Property;

// Player 
typedef enum
{
    AGGRESSIVE_INVESTOR,
    CONSERVATIVE_BANKER,
    RISK_TAKER,
    OPPORTUNISTIC_TRADER
} StrategyType;

typedef struct
{
    StrategyType type;
    int auctionAlways;
    int maximumBidPercent;
    int purchaseCashPercent;
    int aggressiveDevelopment;
    int earlyHotels;
    int maximumLoan;
    int refinance;
    int basicInsurance;
    int comprehensiveInsurance;
    int avoidHotelsWithLoan;
    int renovationThreshold;
    int sellWhenBankruptcy;
    int sellLowValue;
} Strategy;

typedef struct
{
    char name[30];
    int position;
    int money;
    int jailTurns;
    int bankrupt;
    int propertiesOwned;
    int railwayOwned;
    int utilityOwned;
    int loan;
    int hasLoan;
    int loanRounds;
    int networth;
    int hotels;
    Strategy strategy;
} Player;

#endif
