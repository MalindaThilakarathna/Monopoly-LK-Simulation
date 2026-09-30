#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "types.h"

//////////////////////////////////////// Event Actions //////////////////////////////////////////
          
// IDs of the 20 event cards
int cardID[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

// Active event round expiration trackers
static int tourismHypeExpiry = 0;
static int fuelShortageExpiry = 0;
static int politicalRallyExpiry = 0;
static int stockMarketRiseExpiry = 0;
static int economicDowntownExpiry = 0;
static int housingSubsidyExpiry = 0;
static int interestRateCutExpiry = 0;
static int interestRateIncreaseExpiry = 0;
static int powerFailureExpiry = 0;
static int foreignFundingExpiry = 0;
static int portExpansionExpiry = 0;
static int festivalSeasonExpiry = 0;
static int labourStrikeExpiry = 0;
static int insuranceDiscountExpiry = 0;
static int PropertyRevaluationExpiry = 0;
static int currencyDepreciationExpiry = 0;
static int loanInterestRateModifier = 0;


int getLoanInterestRateModifier(void)
{
    return loanInterestRateModifier;
}

int getInsurancePremiumReductionPercent(void)
{
    return (insuranceDiscountExpiry > 0) ? 20 : 0;
}

int isTourismHypeActive(int round)
{
    return (round < tourismHypeExpiry);
}

int isFuelShortageActive(int round)
{
    return (round < fuelShortageExpiry);
}

int isPowerFailureActive(int round)
{
    return (round < powerFailureExpiry);
}

int isFestivalSeasonActive(int round)
{
    return (round < festivalSeasonExpiry);
}

int isLabourStrikeActive(int round)
{
    return (round < labourStrikeExpiry);
}

int isHousingSubsidyActive(int round)
{
    return (round < housingSubsidyExpiry);
}

// Function to actually execute the effect based on the card ID
void nationalEventCard(int currentCardID, Property board[], Player players[], int currentPlayer, int round) 
{
    int i, randomIndex;
    (void)currentPlayer;

    printf("\n--- NATIONAL EVENT CARD DRAWN ---\n");

    switch (currentCardID) 
    {
        case 0:
            printf("Card: Tourism Hype\n");
            printf("Effect: Hotels earn double rent for 5 rounds\n");
            tourismHypeExpiry = round + 5;
            printf("Event expired in round %d",round+5);
            break;

        case 1:
            printf("Card: Fuel Shortage\n");
            printf("Effect: Railway rent doubles for 5 rounds\n");
            fuelShortageExpiry = round + 5;
            printf("Event expired in round %d",round+5);
            break;

        case 2: {
            printf("Card: Heavy Floods\n");
            printf("Effect: Random coastal property damaged\n");
            int coastalCount = 0;
            int coastalIndices[BOARD_SIZE];
            for(i = 0; i < BOARD_SIZE; i++)
            {
                if(board[i].owner != -1 && (board[i].houses > 0 || board[i].hotel > 0))
                {
                    coastalIndices[coastalCount++] = i;
                }
            }
            if(coastalCount > 0)
            {
                int target = coastalIndices[rand() % coastalCount];
                printf("%s is damaged by flood.\n", board[target].name);
            }
            break;
        }

        case 3: {
            printf("Card: Political Rally\n");
            printf("Effect: One random property closed for 2 rounds\n");
            int ownedCount = 0;
            int ownedIndices[BOARD_SIZE];
            for(i = 0; i < BOARD_SIZE; i++)
            {
                if(board[i].owner != -1)
                {
                    ownedIndices[ownedCount++] = i;
                }
            }
            if(ownedCount > 0)
            {
                int target = ownedIndices[rand() % ownedCount];
                printf("%s is closed for 2 rounds due to political rally.\n", board[target].name);
            }
            politicalRallyExpiry = round+2;
            printf("Event expired in round %d",round+2);
            break;
        }
        
        case 4:
            printf("Card: Stock Market Rise\n");
            printf("Effect: All property values increase by 10%%\n");
            for(i = 0; i < BOARD_SIZE; i++)
            {
                if(board[i].type == PROPERTY)
                {
                    board[i].price = board[i].price * 110 / 100;
                }
            }
            stockMarketRiseExpiry = round + 15;
            printf("Event expired in round %d",round+15);
            break;
            
        case 5:
            printf("Card: Economic Downturn\n");
            printf("Effect: Property values decrease by 15%%\n");
            for(i = 0; i < BOARD_SIZE; i++)
            {
                if(board[i].type == PROPERTY)
                {
                    board[i].price = board[i].price * 85 / 100;
                }
            }
            economicDowntownExpiry = round + 15;
            printf("Event expired in round %d",round+15);
            break;

        case 6:
            printf("Card: Housing Subsidy\n");
            printf("Effect: House construction cost reduced by 30%% for 5 rounds\n");
            housingSubsidyExpiry = round + 15;
            printf("Event expired in round %d",round+15);
            break;
        
        case 7:
            printf("Card: Interest Rate Cut\n");
            printf("Effect: Loan interest reduced by 2%%\n");
            loanInterestRateModifier -= 2;
            interestRateCutExpiry = round + 15;
            printf("Event expired in round %d",round+15);
            break;
        
        case 8:
            printf("Card: Interest Rate Increase\n");
            printf("Effect: Loan interest increased by 2%%\n");
            loanInterestRateModifier += 2;
            interestRateIncreaseExpiry = round + 15;
            printf("Event expired in round %d",round+15);
            break;

        case 9:
            printf("Card: Tax Amnesty\n");
            printf("Effect: Each player receives LKR 2,000\n");
            for(i = 0; i < MAX_PLAYERS; i++)
            {
                if(!players[i].bankrupt)
                {
                    players[i].money += 2000;
                    printf("%s receives LKR 2,000\n", players[i].name);
                }
            }
            break;
        
        case 10:
            printf("Card: Power Failure\n");
            printf("Effect: Utility income halved for 3 rounds\n");
            powerFailureExpiry = round + 3;
            printf("Event expired in round %d",round+3);
            break;
        
        case 11:
            printf("Card: Foreign Funding\n");
            printf("Effect: Commercial property values increase by 15%%\n");
            foreignFundingExpiry = round + 15;
            printf("Event expired in round %d",round+15);
            break;
        
        case 12:
            printf("Card: Port Expansion\n");
            printf("Effect: All RAILWAY values increase by 20%%\n");
            for(i = 0; i < BOARD_SIZE; i++)
            {
                if(board[i].type == RAILWAY)
                {
                    board[i].price = board[i].price * 120 / 100;
                }
            }
            portExpansionExpiry = round + 15;
            printf("Event expired in round %d",round+15);
            break;
        
        case 13:
            printf("Card: Festival Season\n");
            printf("Effect: Hotels receive 50%% additional rent for 5 rounds\n");
            festivalSeasonExpiry = round + 15;
            printf("Event expired in round %d",round+15);
            break;
        
        case 14:
            printf("Card: Labour Strike\n");
            printf("Effect: Construction suspended for 2 rounds\n");
            labourStrikeExpiry = round + 2;
            printf("Event expired in round %d",round+2);
            break;
        
        case 15:
            printf("Card: Insurance Discount\n");
            printf("Effect: Premiums reduced by 20%% for 5 rounds\n");
            insuranceDiscountExpiry = round + 15;
            printf("Event expired in round %d",round+15);
            break;
            
        case 16: {
            printf("Card: Property Revaluation\n");
            printf("Effect: Random property group appreciates by 15%%\n");
            PropertyGroup randomGroup = (PropertyGroup)((rand() % 8) + 1);
            for(i = 0; i < BOARD_SIZE; i++)
            {
                if(board[i].type == PROPERTY && board[i].group == randomGroup)
                {
                    board[i].price = board[i].price * 115 / 100;
                    printf("%s appreciated by 15%%\n", board[i].name);
                }
            }
            PropertyRevaluationExpiry = round + 15;
            printf("Event expired in round %d",round+15);
            break;
        }

        case 17:
            printf("Card: Currency Depreciation\n");
            printf("Effect: Construction costs increase by 10%%\n");
            for(i = 0; i < BOARD_SIZE; i++)
            {
                if(board[i].type == PROPERTY)
                {
                    board[i].houseCost = board[i].houseCost * 110 / 100;
                    board[i].hotelCost = board[i].hotelCost * 110 / 100;
                }
            }
            currencyDepreciationExpiry = round +15;
            printf("Event expired in round %d",round+15);
            break;

        case 18:
            printf("Card: Government Grant\n");
            printf("Effect: Random non-bankrupt player receives LKR 5,000\n");
            randomIndex = rand() % MAX_PLAYERS;
            while(players[randomIndex].bankrupt)
            {
                randomIndex = rand() % MAX_PLAYERS;
            }
            players[randomIndex].money += 5000;
            printf("%s receives LKR 5,000 government grant\n", players[randomIndex].name);
            break;
            
        case 19: {
            printf("Card: National Disaster\n");
            printf("Effect: Random developed property damaged\n");
            int devCount = 0;
            int devIndices[BOARD_SIZE];
            for(i = 0; i < BOARD_SIZE; i++)
            {
                if(board[i].owner != -1 && (board[i].houses > 0 || board[i].hotel > 0))
                {
                    devIndices[devCount++] = i;
                }
            }
            if(devCount > 0)
            {
                int target = devIndices[rand() % devCount];
                printf("%s is damaged by disaster.\n", board[target].name);
            }
            break;
        }

        default:
            printf("Error: Unknown card drawn.\n");
            break;
    }
}

// Check and print expired event notifications
void applyExpiredEventEffects(Property board[], Player players[], int round)
{
    (void)board;
    (void)players;

    if(tourismHypeExpiry > 0 && round >= tourismHypeExpiry)
    {
        printf("[Event Expired] Tourism Hype has ended. Hotel rent returned to normal.\n");
        tourismHypeExpiry = 0;
    }
    if(fuelShortageExpiry > 0 && round >= fuelShortageExpiry)
    {
        printf("[Event Expired] Fuel Shortage has ended. Railway rent returned to normal.\n");
        fuelShortageExpiry = 0;
    }
    if(powerFailureExpiry > 0 && round >= powerFailureExpiry)
    {
        printf("[Event Expired] Power Failure resolved. Utility rent returned to normal.\n");
        powerFailureExpiry = 0;
    }
    if(festivalSeasonExpiry > 0 && round >= festivalSeasonExpiry)
    {
        printf("[Event Expired] Festival Season has ended.\n");
        festivalSeasonExpiry = 0;
    }
    if(labourStrikeExpiry > 0 && round >= labourStrikeExpiry)
    {
        printf("[Event Expired] Labour Strike has ended. Construction is resumed.\n");
        labourStrikeExpiry = 0;
    }
    if(housingSubsidyExpiry > 0 && round >= housingSubsidyExpiry)
    {
        printf("[Event Expired] Housing Subsidy discount period has expired.\n");
        housingSubsidyExpiry = 0;
    }
    if(insuranceDiscountExpiry > 0 && round >= insuranceDiscountExpiry)
    {
        printf("[Event Expired] Insurance Discount period has ended.\n");
        insuranceDiscountExpiry = 0;
    }
    if(politicalRallyExpiry > 0 && round >= politicalRallyExpiry)
    {
        printf("[Event Expired] Political Rally has ended. Closed property now opened.");
        politicalRallyExpiry = 0;
    }
    if(stockMarketRiseExpiry > 0 && round >= stockMarketRiseExpiry)
    {
        printf("[Event Expired] Stock Market Rise ended. All property values return to normal.");
        stockMarketRiseExpiry = 0;
    }
    if(economicDowntownExpiry > 0 && round >= economicDowntownExpiry)
    {
        printf("[Event Expired] Economic Downturn ended. All property values return to normal.");
        economicDowntownExpiry = 0;
    }
    if(interestRateCutExpiry > 0 && round >= interestRateCutExpiry)
    {
        printf("[Event Expired] Interest Rate Cut ended. Loan interest return to normal.");
        interestRateCutExpiry = 0;
    }
    if(interestRateIncreaseExpiry > 0 && round >=  interestRateIncreaseExpiry)
    {
        printf("[Event Expired] Interest Rate Increase ended. Loan interest return to normal.");
        interestRateIncreaseExpiry = 0;
    }
    if(foreignFundingExpiry > 0 && round >= foreignFundingExpiry)
    {
        printf("[Event Expired] Foreign Funding ended. Commercial Property values return to normal.");
        foreignFundingExpiry = 0;
    }
    if(portExpansionExpiry > 0 && round >= portExpansionExpiry)
    {
        printf("[Event Expired] Port Expansion ended. Railway station values return to normal.");
        portExpansionExpiry = 0;
    }
    if(PropertyRevaluationExpiry > 0 && round >= PropertyRevaluationExpiry)
    {
        printf("[Event Expired] Property Revaluation expired.");
        PropertyRevaluationExpiry = 0;
    }
    if(currencyDepreciationExpiry > 0 && round >= currencyDepreciationExpiry)
    {
        printf("[Event Expired] Currency Depreciation ended. Construction cost return to noraml.");
        currencyDepreciationExpiry = 0;
    }

}  


// Function to draw the card and cycle the deck
void drawEventCard(Property board[], Player players[], int currentPlayer, int round) 
{
    int drawnCardID = cardID[0];
    nationalEventCard(drawnCardID, board, players, currentPlayer, round);

    for (int i = 0; i < 19; i++) 
    {
        cardID[i] = cardID[i + 1];
    }

    cardID[19] = drawnCardID;
}

////////////////////////////////////////// Inflation //////////////////////////////////////////

static int currentInflationRate = 0;
static int currentBaseInterestRate = 8; // Default 8% (Stable Economy)

int getCurrentInflationRate(void)
{
    return currentInflationRate;
}

int getCurrentBaseInterestRate(void)
{
    return currentBaseInterestRate;
}

void applyInflation(Property board[], int round)
{
    int rates[] = {-3, 0, 2, 5, 8, 12};
    int randomIndex = rand() % 6;
    int rate = rates[randomIndex];
    int i;

    currentInflationRate = rate;

    // Adjust base loan interest rate based on Inflation (Table 9)
    if (rate <= 0)
    {
        currentBaseInterestRate = 5;  // Economic Boom / Deflation
    }
    else if (rate <= 2)
    {
        currentBaseInterestRate = 8;  // Stable Economy
    }
    else if (rate <= 5)
    {
        currentBaseInterestRate = 10; // Moderate Inflation
    }
    else
    {
        currentBaseInterestRate = 12; // High Inflation
    }

    // Apply percentage change to all properties (Rule-LK 13 & 14)
    for(i = 0; i < BOARD_SIZE; i++)
    {
        if(board[i].type == PROPERTY)
        {
            board[i].price += (board[i].price * rate) / 100;
            board[i].houseCost += (board[i].houseCost * rate) / 100;
            board[i].hotelCost += (board[i].hotelCost * rate) / 100;
            board[i].rent += (board[i].rent * rate) / 100;
            board[i].mortgage += (board[i].mortgage * rate) / 100;

            if(board[i].price < 500) board[i].price = 500;
            if(board[i].rent < 50) board[i].rent = 50;
            if(board[i].houseCost < 200) board[i].houseCost = 200;
            if(board[i].hotelCost < 800) board[i].hotelCost = 800;
        }
    }

    printf("\n=========================================\n");
    printf("        INFLATION UPDATE (Round %d)\n", round);
    printf("=========================================\n");
    if (rate >= 0)
    {
        printf("Inflation Rate: +%d%%\n", rate);
    }
    else
    {
        printf("Inflation Rate: %d%% (Deflation)\n", rate);
    }
    printf("Current Base Loan Interest Rate: %d%%\n", currentBaseInterestRate);
    printf("=========================================\n");
}

/////////////////////////////////// Dynamic Property Market ///////////////////////////////////

static const char* getGroupName(PropertyGroup group)
{
    switch(group)
    {
        case BROWN: 
            return "(Brown)";
        case LIGHT_BLUE:
            return "(Light Blue)";
        case PINK: 
            return "(Pink)";
        case ORANGE: 
            return "(Orange)";
        case RED: 
            return "(Red)";
        case YELLOW: 
            return "(Yellow)";
        case GREEN: 
            return "(Green)";
        case DARK_BLUE: 
            return "(Dark Blue)";
        default: 
            return "None";
    }
}
/*
// 30-round cooldown tracker for Boom and Decline (Rule-LK 33)
static int lastBoomRound []= {-30, -30, -30, -30, -30, -30, -30, -30, -30};
static int lastDeclineRound []= {-30, -30, -30, -30, -30, -30, -30, -30, -30};
*/
void updatePropertyMarket(Property board[], int round)
{
    /*
    int eligibleGroups[]={};
    int eligibleCount = 0;
    int i;

    // 1. Check which groups have passed the 30-round cooldown (Rule-LK 33)
    for (i = 1; i <= 8; i++)
    {
        if (round - lastBoomRound[i] >= 30 && round - lastDeclineRound[i] >= 30)
        {
            eligibleGroups[eligibleCount++] = i;
        }
    }

    //need at least 2 eligible groups to pick one for Boom and one for Decline
    if (eligibleCount >= 2)
    {
        //Pick different random groups for Boom and Decline
        int boomIndex = eligibleGroups[rand() % eligibleCount];
        int declineIndex = eligibleGroups[rand() % eligibleCount];

        //Ensure declineIndex is DIFFERENT from boomIndex
        while (declineIndex == boomIndex)
        {
            declineIndex = eligibleGroups[rand() % eligibleCount];
        }

        PropertyGroup boomGroup = (PropertyGroup)boomIndex;
        PropertyGroup declineGroup = (PropertyGroup)declineIndex;

        // Record cooldown rounds
        lastBoomRound[boomIndex] = round;
        lastDeclineRound[declineIndex] = round;
    */
   
    //this part add because above part not working well
    int i;
    int boomIndex;
    int declineIndex;

    do {
        boomIndex = rand() % 8;
        declineIndex = rand() % 8;
    } while (boomIndex == declineIndex); 

    PropertyGroup boomGroup = (PropertyGroup)boomIndex;
    PropertyGroup declineGroup = (PropertyGroup)declineIndex;
    //........

        // 3. Apply Market Boom (Rule-LK 31)
        for (i = 0; i < BOARD_SIZE; i++)
        {
            if (board[i].type == PROPERTY && board[i].group == boomGroup)
            {
                board[i].price += (board[i].price * 15) / 100;
                board[i].rent += (board[i].rent * 25) / 100;
                board[i].mortgage += (board[i].mortgage * 15) / 100;
                board[i].houseCost += (board[i].houseCost * 10) / 100;
                board[i].hotelCost += (board[i].hotelCost * 10) / 100;
            }
        }

        printf("\n=========================================\n");
        printf("       MARKET BOOM ACTIVATED (Round %d)\n", round);
        printf("=========================================\n");
        printf("Booming Region: %s\n", getGroupName(boomGroup));
        printf("Effects for 10 Rounds:\n");
        printf("- Rental Income: +25%%\n");
        printf("- Property Values & Mortgages: +15%%\n");
        printf("- Construction Costs: +10%%\n");
        printf("=========================================\n");

        // 4. Apply Market Decline (Rule-LK 32)
        for (i = 0; i < BOARD_SIZE; i++)
        {
            if (board[i].type == PROPERTY && board[i].group == declineGroup)
            {
                board[i].price -= (board[i].price * 15) / 100;
                board[i].rent -= (board[i].rent * 20) / 100;       // -20% Rent (Rule-LK 32)
                board[i].mortgage -= (board[i].mortgage * 10) / 100; // -10% Mortgage (Rule-LK 32)
            }
        }

        printf("=========================================\n");
        printf("     MARKET DECLINE ACTIVATED (Round %d)\n", round);
        printf("=========================================\n");
        printf("Declining Region: %s\n", getGroupName(declineGroup));
        printf("Effects for 10 Rounds:\n");
        printf("- Rental Income: -20%%\n");
        printf("- Property Values: -15%%\n");
        printf("- Mortgage Values: -10%%\n");
        printf("=========================================\n\n");
    //}
}

///////////////////////////////// Regional Development Cards /////////////////////////////////

static int activeRegionalCard = -1;
static int regionalCardExpiry = 0;

int getActiveRegionalCard(void)
{
    return activeRegionalCard;
}

int getRegionalRoundsRemaining(int round)
{
    if (round < regionalCardExpiry)
    {
        return regionalCardExpiry - round;
    }
    return 0;
}

void drawRegionalDevelopmentCard(Property board[], int round)
{
    int card = rand() % 12; // 12 Regional Cards (Table 4)
    activeRegionalCard = card;
    regionalCardExpiry = round + 15; // Active for 15 rounds (Rule-LK 35)

    printf("\n==================================================\n");
    printf("     REGIONAL DEVELOPMENT CARD DRAWN (Round %d)\n", round);
    printf("==================================================\n");

    switch(card)
    {
        case 0:
            printf("Card: Southern Tourism Boom\n");
            printf("Effect: Galle Fort, Unawatuna and Hikkaduwa rent +40%% for 15 rounds.\n");
            // Squares 26, 27, 29
            board[26].rent += (board[26].rent * 40) / 100;
            board[27].rent += (board[27].rent * 40) / 100;
            board[29].rent += (board[29].rent * 40) / 100;
            break;

        case 1:
            printf("Card: Port City Expansion\n");
            printf("Effect: Pettah, Maradana and Colombo Fort Station values +25%%.\n");
            // Squares 1, 3, 5
            board[1].price += (board[1].price * 25) / 100;
            board[3].price += (board[3].price * 25) / 100;
            board[5].price += (board[5].price * 25) / 100;
            break;

        case 2:
            printf("Card: IT Industry Growth\n");
            printf("Effect: Maharagama, Nugegoda and Kottawa values +20%%.\n");
            // Squares 11, 13, 14
            board[11].price += (board[11].price * 20) / 100;
            board[13].price += (board[13].price * 20) / 100;
            board[14].price += (board[14].price * 20) / 100;
            break;

        case 3:
            printf("Card: Northern Development Programme\n");
            printf("Effect: Jaffna Town, Nallur and Trincomalee values +30%%.\n");
            // Squares 31, 32, 34
            board[31].price += (board[31].price * 30) / 100;
            board[32].price += (board[32].price * 30) / 100;
            board[34].price += (board[34].price * 30) / 100;
            break;

        case 4:
            printf("Card: Tea Export Boom\n");
            printf("Effect: Nuwara Eliya value +35%%.\n");
            // Square 37
            board[37].price += (board[37].price * 35) / 100;
            break;

        case 5:
            printf("Card: Airport Expansion\n");
            printf("Effect: Negombo, Katunayake and Ja-Ela rents +30%% for 15 rounds.\n");
            // Squares 16, 18, 19
            board[16].rent += (board[16].rent * 30) / 100;
            board[18].rent += (board[18].rent * 30) / 100;
            board[19].rent += (board[19].rent * 30) / 100;
            break;

        case 6:
            printf("Card: University City Growth\n");
            printf("Effect: Peradeniya and Kandy City values +20%%.\n");
            // Squares 21, 23
            board[21].price += (board[21].price * 20) / 100;
            board[23].price += (board[23].price * 20) / 100;
            break;

        case 7:
            printf("Card: Beach Pollution\n");
            printf("Effect: Southern coastal rents -30%% for 15 rounds.\n");
            // Squares 26, 27, 29
            board[26].rent -= (board[26].rent * 30) / 100;
            board[27].rent -= (board[27].rent * 30) / 100;
            board[29].rent -= (board[29].rent * 30) / 100;
            break;

        case 8:
            printf("Card: Flood Damage\n");
            printf("Effect: Low-lying coastal properties lose 20%% value.\n");
            // Wellawatte (8), Mount Lavinia (9), Galle Fort (26), Unawatuna (27), Hikkaduwa (29)
            board[8].price -= (board[8].price * 20) / 100;
            board[9].price -= (board[9].price * 20) / 100;
            board[26].price -= (board[26].price * 20) / 100;
            board[27].price -= (board[27].price * 20) / 100;
            board[29].price -= (board[29].price * 20) / 100;
            break;

        case 9:
            printf("Card: Transport Strike\n");
            printf("Effect: Railway revenue reduced by 40%% for 15 rounds.\n");
            break;

        case 10:
            printf("Card: Electricity Tariff Increase\n");
            printf("Effect: Utility rent +25%% for 15 rounds.\n");
            break;

        case 11:
            printf("Card: Water Shortage\n");
            printf("Effect: Water utility revenue +20%%; surrounding properties -10%%.\n");
            board[28].price += (board[28].price * 20) / 100; // Water Board
            board[27].price -= (board[27].price * 10) / 100; //Unawatuna
            board[29].price -= (board[29].price * 10) / 100; //Hikkaduwa
            break;
    }
    printf("Expired in round %d\n",regionalCardExpiry);
    printf("==================================================\n\n");

}

void applyExpiredRegionalDevelopmentCards(Property board[], Player players[], int round)
{
    (void)players;

    // Check if the 15 rounds of Regional Development have elapsed (Rule-LK 35)
    if (activeRegionalCard != -1 && round >= regionalCardExpiry)
    {
        printf("\n==================================================\n");
        printf("[REGIONAL EVENT EXPIRED] 15 Rounds Completed!\n");
        printf("Regional property values and rents have returned to normal.\n");
        printf("==================================================\n");

        // Revert prices and rents back to normal per Rule-LK 35
        switch(activeRegionalCard)
        {
            case 0: 
                board[26].rent = (board[26].rent * 100) / 140;
                board[27].rent = (board[27].rent * 100) / 140;
                board[29].rent = (board[29].rent * 100) / 140;
                break;

            case 1:
                board[1].price = (board[1].price * 100) / 125;
                board[3].price = (board[3].price * 100) / 125;
                board[5].price = (board[5].price * 100) / 125;
                break;

            case 2: 
                board[11].price = (board[11].price * 100) / 120;
                board[13].price = (board[13].price * 100) / 120;
                board[14].price = (board[14].price * 100) / 120;
                break;

            case 3: 
                board[31].price = (board[31].price * 100) / 130;
                board[32].price = (board[32].price * 100) / 130;
                board[34].price = (board[34].price * 100) / 130;
                break;

            case 4: 
                board[37].price = (board[37].price * 100) / 135;
                break;

            case 5: 
                board[16].rent = (board[16].rent * 100) / 130;
                board[18].rent = (board[18].rent * 100) / 130;
                board[19].rent = (board[19].rent * 100) / 130;
                break;

            case 6: 
                board[21].price = (board[21].price * 100) / 120;
                board[23].price = (board[23].price * 100) / 120;
                break;

            case 7: 
                board[26].rent = (board[26].rent * 100) / 70;
                board[27].rent = (board[27].rent * 100) / 70;
                board[29].rent = (board[29].rent * 100) / 70;
                break;

            case 8: 
                board[8].price  = (board[8].price * 100) / 80;
                board[9].price  = (board[9].price * 100) / 80;
                board[26].price = (board[26].price * 100) / 80;
                board[27].price = (board[27].price * 100) / 80;
                board[29].price = (board[29].price * 100) / 80;
                break;

            case 11: 
                board[28].price = (board[28].price * 100) / 120;
                board[27].price = (board[27].price * 100) / 90;
                board[29].price = (board[29].price * 100) / 90;
                break;

            default:
                break;
        }
        // Reset so no regional card is active
        activeRegionalCard = -1;
        regionalCardExpiry = 0;
    }
}

///////////////////////////////// Government Regulations (Rule-LK 24) /////////////////////////////////

void triggerGovernmentRegulation(Property board[], Player players[], int round)
{
    int reg = rand() % 8; // 8 Regulations 

    printf("=========================================\n");
    printf("Government Regulation\n");
    printf("=========================================\n");

    switch(reg)
    {
        case 0:
            printf("Property Tax Increased.\n");
            printf("Income Tax increases by 50%%.\n");
            break;

        case 1:
            printf("Reduce Loan Interest Introduced.\n");
            printf("Interest decreases by 2%%.\n");
            break;

        case 2:
            printf("Housing Subsidy Introduced.\n");
            printf("Construction costs reduced by 30%%.\n");
            break;

        case 3: {
            printf("Luxury Property Tax\n");
            printf("Hotels incur a maintenance tax of 25%%.\n");
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                if (board[i].owner != -1 && board[i].hotel > 0)
                {
                    int ownerID = board[i].owner;
                    int luxuryTax = (board[i].price * 25) / 100;
                    if (players[ownerID].money >= luxuryTax)
                    {
                        players[ownerID].money -= luxuryTax;
                        printf("- %s paid LKR %d luxury tax for hotel on %s.\n",players[ownerID].name, luxuryTax, board[i].name);
                    }
                }
            }
            break;
        }

        case 4:
            printf("Railway Modernization.\n");
            printf("Railway rents increase by 25%%.\n");
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                if (board[i].type == RAILWAY)
                {
                    board[i].rent += (board[i].rent * 25) / 100;
                }
            }
            break;
            break;

        case 5:
            printf("Electricity Tariff Revision.\n");
            printf("Utility rents increase by 20%%.\n");
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                if (board[i].type == UTILITY)
                {
                    board[i].price += (board[i].price * 20) / 100;
                }
            }
            break;

        case 6:
            printf("Insurance Regulation.\n");
            printf("Insurance premiums decrease by 15%%.\n");
            break;

        case 7:
            printf("Anti-Speculation Act Introduced.\n");
            printf("Players may own at most three undeveloped properties.\n");
            break;
    }
    printf("=========================================\n");
}