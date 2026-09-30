#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "finance.h"
#include "event.h"
#include "types.h"
#include "player.h"

static int getPlayerID(Player player)
{
    if (strcmp(player.name, "Aggressive Investor") == 0) return 0;
    if (strcmp(player.name, "Conservative Banker") == 0) return 1;
    if (strcmp(player.name, "Risk Taker") == 0) return 2;
    if (strcmp(player.name, "Opportunistic Trader") == 0) return 3;
    return -1;
}

/////////////////////////////////////////////////////property related functions////////////////////////////////////////////////////////////////

void buyProperty(Property *property, Player *player, int playerID)
{
    if(property->owner == -1)
    {
        if(player->money >= property->price)
        {
            player->money -= property->price;
            property->owner = playerID;
            property->isLoanLocked = 0;
            if (property->type == RAILWAY)
            {
                player->railwayOwned++;
            }
            else if (property->type == UTILITY)
            {
                player->utilityOwned++;
            }
            else
            {
                player->propertiesOwned++;
            }
            printf("%s bought %s for LKR %d\n", player->name, property->name, property->price);
            printf("Remaining Balance: LKR %d\n", player->money);
        }
        else
        {
            printf("%s cannot afford %s\n", player->name, property->name);
        }
    }
}

//calculate property rent
int calculateRent(Property property, int round)
{
    int rent = 0;
    int multiplier = 1;

    if(property.type != PROPERTY || property.owner == -1)
    {
        return 0;
    }

    if(property.hotel == 1)
    {
        multiplier = 10;
        if(isTourismHypeActive(round))
        {
            multiplier *= 2;
        }
        else if(isFestivalSeasonActive(round))
        {
            multiplier = (multiplier * 15) / 10;
        }
    }
    else
    {
        switch(property.houses)
        {
            case 1: multiplier = 2; break;
            case 2: multiplier = 3; break;
            case 3: multiplier = 5; break;
            case 4: multiplier = 7; break;
            default: multiplier = 1; break;
        }
    }

    rent = property.rent * multiplier;
    return rent;
}

void payRent(Property *property, Player players[], int currentPlayer, int dice, int round)
{
    int owner = property->owner;
    int rent = 0;

    if(owner == -1 || owner == currentPlayer)
    {
        return;
    }

    if(players[owner].bankrupt == 1)
    {
        printf("Owner %s is bankrupt. Property reverts to the bank.\n", players[owner].name);
        property->owner = -1;
        property->houses = 0;
        property->hotel = 0;
        property->mortgaged = 0;
        property->isLoanLocked = 0;
        property->insurance = NO_INSURANCE;
        property->insuranceExpiry = 0;
        return;
    }

    /* Cannot collect rent if property is mortgaged */
    if(property->mortgaged)
    {
        printf("Property is mortgaged. No rent collected.\n");
        return;
    }

    // Normal property
    if(property->type == PROPERTY)
    {
        rent = calculateRent(*property, round);
    }
    // Railway
    else if(property->type == RAILWAY)
    {
        rent = calculateRailwayRent(players[owner], round);
    }
    // Utility
    else if(property->type == UTILITY)
    {
        rent = calculateUtilityRent(players[owner], dice, round);
    }

    if(players[currentPlayer].money >= rent)
    {
        players[currentPlayer].money -= rent;
        players[owner].money += rent;
    }
    else
    {
        int available = players[currentPlayer].money;
        players[currentPlayer].money = 0;
        players[owner].money += available;
    }

    printf("Rent Paid : LKR %d\n", rent);
    printf("Owner : %s\n", players[owner].name);
}

// Build houses & hotels   and check monopoly
int hasMonopoly(Property board[], Player player, PropertyGroup group)
{
    int i;
    int count = 0;
    int totalPropertiesInGroup = 0;
    int pID = getPlayerID(player);

    if(group == NONE || pID == -1)
    {
        return 0;
    }

    // Count total properties in the group
    for(i = 0; i < BOARD_SIZE; i++)
    {
        if(board[i].group == group && board[i].type == PROPERTY)
        {
            totalPropertiesInGroup++;
        }
    }

    // Count properties owned by the player in the group
    for(i = 0; i < BOARD_SIZE; i++)
    {
        if(board[i].group == group && board[i].type == PROPERTY && board[i].owner == pID)
        {
            count++;
        }
    }
    return (count == totalPropertiesInGroup && totalPropertiesInGroup > 0);
}

void buildHouse(Property board[], Property *property, Player *player, int round)
{
    if (isLabourStrikeActive(round))
    {
        printf("\nConstruction suspended due to Labour Strike.\n");
        return;
    }

    if (hasMonopoly(board, *player, property->group) == 1)
    {
        if (property->houses < 4 && property->hotel == 0)
        {
            int cost = property->houseCost;
            if (isHousingSubsidyActive(round))
            {
                cost = (cost * 70) / 100;
            }

            if(player->money >= cost)
            {
                player->money -= cost;
                property->houses++;
                printf("\n========== BUILDING ==========\n");
                printf("%s built a house on %s for LKR %d\n", player->name, property->name, cost);
                printf("Number of houses on %s: %d\n", property->name, property->houses);
                printf("Remaining money: LKR %d\n", player->money);
                printf("==============================\n");
            }
            else
            {
                printf("\n%s cannot build a house.\n", player->name);
                printf("Not enough money.\n");
            }
        }
        else if (property->houses == 4 && property->hotel == 0)
        {
            buildHotel(property, player);
        }
    }
}

void buildHotel(Property *property, Player *player)
{
    if(property->houses == 4 && property->hotel == 0)
    {
        if (player->money >= property->hotelCost)
        {
            player->money -= property->hotelCost;
            property->houses = 0;
            property->hotel = 1;
            player->hotels++;
            printf("\n========== HOTEL ==========\n");
            printf("%s built a hotel on %s for LKR %d\n", player->name, property->name, property->hotelCost);
            printf("Remaining money: LKR %d\n", player->money);
            printf("==============================\n");
        }
        else
        {
            printf("Need 4 houses before hotel.\n");
        }
    }
}
 
//rent calculate railway and utility
int calculateRailwayRent(Player player, int round)
{
    int rent = 0;
    switch (player.railwayOwned)
    {
        case 1: rent = 250; break;
        case 2: rent = 500; break;
        case 3: rent = 1000; break;
        case 4: rent = 2000; break;
    }
    if (isFuelShortageActive(round))
    {
        rent *= 2;
    }
    return rent;
}

int calculateUtilityRent(Player player, int dice, int round)
{
    int rent = 0;
    if(player.utilityOwned == 2)
    {
        rent = dice * 10;
    }
    else if(player.utilityOwned == 1)
    {
        rent = dice * 4;
    }
    if (isPowerFailureActive(round))
    {
        rent /= 2;
    }
    return rent;
}

//////////////////////////////////////////////////// Bank and Loan Management (Rule-LK 1 to 7) ////////////////////////////////////////////////

void processBank(Player *player, Property board[], int playerID)
{
    printf("\n%s reached Commercial Bank\n", player->name);

    if(player->hasLoan == 0 && player->money < 5000)
    {
        obtainLoan(player, board, playerID);
    }
    else if(player->hasLoan == 1 && player->money > player->loan)
    {
        repayFullLoan(player, board, playerID);
    }
    else
    {
        printf("No bank action required.\n");
    }
}

void obtainLoan(Player *player, Property board[], int playerID)
{
    int maxLoan = 0;
    int collateral = 0;
    int rate = getCurrentBaseInterestRate() + getLoanInterestRateModifier();
    int i;

    if(player->hasLoan == 1)
    {
        printf("You already have an active loan.\n");
        return;
    }

    for(i = 0; i < BOARD_SIZE; i++)
    {
        if(board[i].owner == playerID && board[i].mortgaged == 0 && board[i].isLoanLocked == 0)
        {
            if(board[i].type == PROPERTY || board[i].type == RAILWAY || board[i].type == UTILITY)
            {
                collateral += board[i].mortgage;
            }
        }
    }

    maxLoan = (int)(collateral * 0.75);

    if(maxLoan <= 0)
    {
        printf("No collateral available.\n");
        return;
    }

    for(i = 0; i < BOARD_SIZE; i++)
    {
        if(board[i].owner == playerID && board[i].mortgaged == 0 && board[i].isLoanLocked == 0)
        {
            if(board[i].type == PROPERTY || board[i].type == RAILWAY || board[i].type == UTILITY)
            {
                board[i].isLoanLocked = 1;
            }
        }
    }

    player->loan = maxLoan;
    player->money += maxLoan;
    player->hasLoan = 1;
    player->loanRounds = 20;

    printf("\n%s obtained a secured loan.\n", player->name);
    printf("Loan Amount : LKR %d\n", maxLoan);
    printf("Collateral :\n");
    for(i = 0; i < BOARD_SIZE; i++)
    {
        if(board[i].owner == playerID && board[i].isLoanLocked == 1)
        {
            printf("%s\n", board[i].name);
        }
    }
    printf("Interest Rate : %d%%\n", rate);
    printf("Duration : 20 Rounds\n");
}

void repayLoan(Player *player, Property board[], int playerID, int amount)
{
    int i;

    if(player->hasLoan == 0)
    {
        printf("No active loan.\n");
        return;
    }

    if(amount > player->money) amount = player->money;
    if(amount > player->loan) amount = player->loan;
    if(amount <= 0) return;

    player->money -= amount;
    player->loan -= amount;

    printf("%s repaid LKR %d.\n", player->name, amount);
    printf("Outstanding Balance :\n");

    if(player->loan <= 0)
    {
        player->loan = 0;
        player->hasLoan = 0;
        player->loanRounds = 0;
        printf("None.\n");

        for(i = 0; i < BOARD_SIZE; i++)
        {
            if(board[i].owner == playerID)
            {
                board[i].isLoanLocked = 0;
            }
        }
    }
    else
    {
        printf("LKR %d\n", player->loan);
    }
}

void repayFullLoan(Player *player, Property board[], int playerID)
{
    if(player->hasLoan == 0)
    {
        printf("No active loan.\n");
        return;
    }

    if(player->money >= player->loan)
    {
        repayLoan(player, board, playerID, player->loan);
    }
    else
    {
        printf("Insufficient money to fully repay loan.\n");
    }
}

void refinanceLoan(Player *player)
{
    if(player->hasLoan == 0)
    {
        printf("No loan to refinance.\n");
        return;
    }
    printf("Loan refinanced.\n");
}

void increaseLoan(Player *player, Property board[], int playerID)
{
    int collateral = 0;
    int newLimit;
    int i;

    for(i = 0; i < BOARD_SIZE; i++)
    {
        if(board[i].owner == playerID && board[i].mortgaged == 0)
        {
            collateral += board[i].mortgage;
        }
    }

    newLimit = (int)(collateral * 0.75);

    if(newLimit > player->loan)
    {
        int extra = newLimit - player->loan;
        player->loan += extra;
        player->money += extra;
        printf("Additional loan: %d\n", extra);
    }
    else
    {
        printf("Cannot increase loan.\n");
    }
}

void checkLoanDefault(Player *player, Property board[], int playerID)
{
    int i;

    if(player->bankrupt == 1 || player->hasLoan == 0)
    {
        return;
    }

    if(player->loanRounds <= 0)
    {
        printf("\n=========================================\n");
        printf("%s has defaulted.\n", player->name);
        printf("Collateral has been foreclosed.\n");
        printf("Outstanding debt cleared.\n");
        printf("=========================================\n");

        for(i = 0; i < BOARD_SIZE; i++)
        {
            if(board[i].owner == playerID && board[i].isLoanLocked == 1)
            {
                board[i].owner = -1;
                board[i].houses = 0;
                board[i].hotel = 0;
                board[i].mortgaged = 0;
                board[i].isLoanLocked = 0;
                board[i].insurance = NO_INSURANCE;
                board[i].insuranceExpiry = 0;

                if(board[i].type == PROPERTY && player->propertiesOwned > 0) player->propertiesOwned--;
                if(board[i].type == RAILWAY && player->railwayOwned > 0) player->railwayOwned--;
                if(board[i].type == UTILITY && player->utilityOwned > 0) player->utilityOwned--;
            }
        }

        player->loan = 0;
        player->hasLoan = 0;
        player->loanRounds = 0;

        if(player->propertiesOwned == 0 && player->railwayOwned == 0 && player->utilityOwned == 0 && player->money <= 0)
        {
            player->bankrupt = 1;
            printf("%s possesses no remaining assets and is declared bankrupt.\n", player->name);
        }
    }
}

void addLoanInterest(Player players[], Property board[])
{
    int i;
    int rate = getCurrentBaseInterestRate() + getLoanInterestRateModifier();
    if(rate < 2) rate = 2;

    for(i = 0; i < MAX_PLAYERS; i++)
    {
        if(players[i].bankrupt == 0 && players[i].hasLoan == 1)
        {
            int interest = players[i].loan * rate / 100;
            players[i].loan += interest;
            players[i].loanRounds--;
            printf("%s's loan compounded by LKR %d interest (%d%%). Rounds left: %d\n", 
                   players[i].name, interest, rate, players[i].loanRounds);

            checkLoanDefault(&players[i], board, i);
        }
    }
}

//////////////////////////////////////////////////////////insurance related functions//////////////////////////////////////////////////////////
void buyInsurance(Player *player, Property *property, InsuranceType type, int round)
{
    int premium;

    /* Cannot buy insurance if already has one */
    if(property->insurance != NO_INSURANCE)
    {
        printf("\n%s already has insurance on %s. Cannot buy duplicate insurance.\n", player->name, property->name);
        return;
    }

    /* Can only buy insurance on actual properties */
    if(property->type != PROPERTY)
    {
        printf("\nCannot buy insurance on %s. Only properties can have insurance.\n", property->name);
        return;
    }

    if(type == BASIC_INSURANCE)
    {
        premium = property->price * 5 / 100;
    }
    else if(type == COMPREHENSIVE_INSURANCE)
    {
        premium = property->price * 10 / 100;
    }
    else if(type == BUSINESS_INSURANCE)
    {
        premium = property->price * 15 / 100;
    }
    else
    {
        return;
    }

    if(getInsurancePremiumReductionPercent() > 0)
    {
        premium = (premium * 80) / 100;
    }

    if(player->money < premium)
    {
        printf("\n%s does not have enough money for insurance on %s. Need: LKR %d, Have: LKR %d\n", player->name, property->name, premium, player->money);
        return;
    }

    player->money -= premium;
    property->insurance = type;
    property->insuranceExpiry = round + 20;

    printf("\n%s bought insurance for %s.\n", player->name, property->name);
    printf("Premium: LKR %d\n", premium);
    printf("Expires: Round %d\n", property->insuranceExpiry);
}

void checkInsuranceExpiry(Player players[], Property board[], int round)
{
    int i;
    int owner;

    for(i = 0; i < BOARD_SIZE; i++)
    {
        if(board[i].insurance == NO_INSURANCE)
        {
            continue;
        }
        owner = board[i].owner;
        if(owner < 0 || owner >= MAX_PLAYERS)
        {
            continue;
        }

        if(round == board[i].insuranceExpiry - 3)
        {
            printf("\nInsurance policy on %s expires in 3 rounds.\n", board[i].name);
        }

        if(round >= board[i].insuranceExpiry)
        {
            printf("\n%s's insurance on %s has expired.\n", players[owner].name, board[i].name);
            board[i].insurance = NO_INSURANCE;
            board[i].insuranceExpiry = 0;
        }
    }
}

//auction
void auctionProperty(Property *property, Player players[])
{
    int active[MAX_PLAYERS];
    int i;

    int currentBid = property->price / 2; // Opening bid at 50%
    int highestBidder = -1;

    int activePlayers = 0;
    printf("Reject purchase %s and create an auction.\n", property->name);
    printf("\n==================================================\n");
    printf("AUCTION: %s\n", property->name);
    printf("====================================================\n");
    printf("\nOpening Bid : LKR %d\n", currentBid);
    
    for(i = 0; i < MAX_PLAYERS; i++)
    {
        if(players[i].bankrupt == 0 && players[i].money >= currentBid + 250)
        {
            active[i] = 1;
            activePlayers++;
        }
        else
        {
            active[i] = 0;
        }
    }

    while(activePlayers > 1)
    {
        int someoneBid = 0;
        
        for(i = 0; i < MAX_PLAYERS; i++)
        {
            if(active[i] == 1)
            {
                int nextBid = currentBid + 250;
                int maximumBid = getMaximumBid(&players[i], property);

                if(players[i].money < nextBid)
                {
                    printf("%s cannot bid LKR %d\n", players[i].name, nextBid);
                    active[i] = 0;
                    activePlayers--;
                    continue;
                }
                if(nextBid <= maximumBid)
                {
                    currentBid = nextBid;
                    highestBidder = i;
                    someoneBid = 1;
                    printf("%s bids LKR %d\n", players[i].name, currentBid);
                }
                else
                {
                    printf("%s passes\n", players[i].name);

                    active[i] = 0;
                    activePlayers--;

                    if (activePlayers == 1)
                    {
                        break;
                    }
                }
            }
        }
        if(someoneBid == 0)
        {
            break;
        }
    }

    if(highestBidder != -1)
    {
        players[highestBidder].money -= currentBid;
        property->owner = highestBidder;
        property->isLoanLocked = 0;
        if(property->type == PROPERTY)
        {
            players[highestBidder].propertiesOwned++;
        }
        else if(property->type == RAILWAY)
        {
            players[highestBidder].railwayOwned++;
        }
        else if(property->type == UTILITY)
        {
            players[highestBidder].utilityOwned++;
        }

        printf("\n%s won the auction!\n", players[highestBidder].name);
        printf("Final bid: LKR %d\n", currentBid);
    }
    else
    {
        printf("\nNo player bid for %s.\n", property->name);
    }
}

/*Process Depreciation at the End of Every Round (Rule-LK 15 & 16) */
void processPropertyDepreciation(Property board[])
{
    int i;

    for (i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i].type == PROPERTY && board[i].owner != -1)
        {
            board[i].age++; 

            // Properties older than 50 rounds depreciate 1% every 5 rounds, max 30% 
            if (board[i].age > 50)
            {
                if (board[i].age % 5 == 0)
                {
                    if (board[i].depreciation < 30)
                    {
                        board[i].depreciation += 1;
                        
                        // Reduce current price and rent by the depreciation percentage
                        int valueLoss = (board[i].price * 1) / 100;
                        board[i].price -= valueLoss;
                        printf("-------------------------------------------------------\n");
                        printf("Property\n%s\nhas depreciated by %d%%.\nCurrent Value\nLKR %d.\n",board[i].name, board[i].depreciation, board[i].price);
                        printf("-------------------------------------------------------\n");
                    }
                }
            }
        }
    }
}

// Renovate Property when Landing on Own Square 
void renovateProperty(Property *property, Player *player)
{
    // Renovation cost is 10% of current market value
    int renovationCost = (property->price * 10) / 100;

    if (player->money >= renovationCost && property->depreciation > 0)
    {
        player->money -= renovationCost;
        
        // Restore depreciated value back
        property->price += (property->price * property->depreciation) / (100 - property->depreciation);
        
        property->age = 0;          // Reset age 
        property->depreciation = 0; // Clear depreciation

        printf("\n===================================================\n");
        printf("%s renovated %s for LKR %d.\n", player->name, property->name, renovationCost);
        printf("Property value and rent restored to 100%%!\n");
        printf("Remaining Balance: LKR %d\n", player->money);
        printf("====================================================\n\n");
    }
}
