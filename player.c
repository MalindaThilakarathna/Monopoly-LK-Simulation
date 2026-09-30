#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "player.h"
#include "types.h"

void initializePlayers(Player players[])
{
    int i;
    const char *playerNames[MAX_PLAYERS] =
    {
        "Aggressive Investor",
        "Conservative Banker",
        "Risk Taker",
        "Opportunistic Trader"
    };

    for(i = 0; i < MAX_PLAYERS; i++)
    {
        strcpy(players[i].name, playerNames[i]);

        players[i].position = 0;
        players[i].money = 30000;
        players[i].jailTurns = 0;
        players[i].bankrupt = 0;
        players[i].propertiesOwned = 0;
        players[i].railwayOwned = 0;
        players[i].utilityOwned = 0;
        players[i].loan = 0;
        players[i].hasLoan = 0;
        players[i].loanRounds = 0;
        players[i].hotels = 0;
    }

    /* Aggressive Investor */
    players[0].strategy.type = AGGRESSIVE_INVESTOR;
    players[0].strategy.auctionAlways = 1;
    players[0].strategy.maximumBidPercent = 120;
    players[0].strategy.purchaseCashPercent = 0;
    players[0].strategy.aggressiveDevelopment = 1;
    players[0].strategy.earlyHotels = 1;
    players[0].strategy.maximumLoan = 1;
    players[0].strategy.refinance = 0;
    players[0].strategy.basicInsurance = 1;
    players[0].strategy.comprehensiveInsurance = 1;
    players[0].strategy.avoidHotelsWithLoan = 0;
    players[0].strategy.renovationThreshold = 0;
    players[0].strategy.sellWhenBankruptcy = 1;
    players[0].strategy.sellLowValue = 0;

    /* Conservative Banker */
    players[1].strategy.type = CONSERVATIVE_BANKER;
    players[1].strategy.auctionAlways = 0;
    players[1].strategy.maximumBidPercent = 100;
    players[1].strategy.purchaseCashPercent = 50;
    players[1].strategy.aggressiveDevelopment = 0;
    players[1].strategy.earlyHotels = 0;
    players[1].strategy.maximumLoan = 0;
    players[1].strategy.refinance = 0;
    players[1].strategy.basicInsurance = 0;
    players[1].strategy.comprehensiveInsurance = 1;
    players[1].strategy.avoidHotelsWithLoan = 1;
    players[1].strategy.renovationThreshold = 10;
    players[1].strategy.sellWhenBankruptcy = 1;
    players[1].strategy.sellLowValue = 0;

    /* Risk Taker */
    players[2].strategy.type = RISK_TAKER;
    players[2].strategy.auctionAlways = 1;
    players[2].strategy.maximumBidPercent = 0;
    players[2].strategy.purchaseCashPercent = 0;
    players[2].strategy.aggressiveDevelopment = 1;
    players[2].strategy.earlyHotels = 1;
    players[2].strategy.maximumLoan = 1;
    players[2].strategy.refinance = 1;
    players[2].strategy.basicInsurance = 0;
    players[2].strategy.comprehensiveInsurance = 0;
    players[2].strategy.avoidHotelsWithLoan = 0;
    players[2].strategy.renovationThreshold = 0;
    players[2].strategy.sellWhenBankruptcy = 1;
    players[2].strategy.sellLowValue = 1;

    /* Opportunistic Trader */
    players[3].strategy.type = OPPORTUNISTIC_TRADER;
    players[3].strategy.auctionAlways = 0;
    players[3].strategy.maximumBidPercent = 100;
    players[3].strategy.purchaseCashPercent = 0;
    players[3].strategy.aggressiveDevelopment = 0;
    players[3].strategy.earlyHotels = 0;
    players[3].strategy.maximumLoan = 0;
    players[3].strategy.refinance = 0;
    players[3].strategy.basicInsurance = 0;
    players[3].strategy.comprehensiveInsurance = 1;
    players[3].strategy.avoidHotelsWithLoan = 0;
    players[3].strategy.renovationThreshold = 15;
    players[3].strategy.sellWhenBankruptcy = 1;
    players[3].strategy.sellLowValue = 0;
}

int rollDice()
{
    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;

    return dice1 + dice2;
}

void movePlayer(Player *player, int dice)
{
    player->position += dice;

    if(player->position >= BOARD_SIZE)
    {
        player->position -= BOARD_SIZE;
        player->money += 2000;

        printf("\n%s passed GO.\n", player->name);
        printf("Collected LKR 2000.\n");
        printf("Current Balance: LKR %d\n", player->money);
        
    }
}

void printPlayer(Player player)
{
    printf("Name : %s\n", player.name);
    printf("Position : %d\n", player.position);
    printf("Cash : LKR %d\n", player.money);
    printf("Net Worth : LKR %d\n",player.networth);
    printf("Properties : %d\n", player.propertiesOwned);
    printf("Railways : %d\n", player.railwayOwned);
    printf("Utilities : %d\n", player.utilityOwned);
    printf("Hotels : %d\n",player.hotels);
    printf("Outstanding Loan : %d\n", player.loan);
    printf("-------------------------\n");
}

void printAllPlayers(Player players[])
{
    int i;

    for(i = 0; i < MAX_PLAYERS; i++)
    {
        printPlayer(players[i]);
    }
}

void releaseBankruptProperties(Player *player, Property board[], int playerID)
{
    int i;

    for(i = 0; i < BOARD_SIZE; i++)
    {
        if(board[i].owner == playerID)
        {
            printf("%s's %s returns to the bank.\n", player->name, board[i].name);
            board[i].owner = -1;
            board[i].houses = 0;
            board[i].hotel = 0;
            board[i].mortgaged = 0;
            board[i].isLoanLocked = 0;
            board[i].insurance = NO_INSURANCE;
            board[i].insuranceExpiry = 0;
        }
    }

    player->propertiesOwned = 0;
    player->railwayOwned = 0;
    player->utilityOwned = 0;

    if(player->hasLoan == 1)
    {
        printf("%s's outstanding loan of LKR %d is now due.\n", player->name, player->loan);
        player->loan = 0;
        player->hasLoan = 0;
        player->loanRounds = 0;
    }
}

int calculateNetWorth(Property board[], Player players[], int playerID)
{
    int i;
    int worth = players[playerID].money;

    for(i = 0; i < BOARD_SIZE; i++)
    {
        if(board[i].owner == playerID)
        {
            worth += board[i].price;
            worth += board[i].houses * board[i].houseCost;
            if(board[i].hotel > 0)
            {
                worth += board[i].hotelCost;
            }
        }
    }

    worth -= players[playerID].loan;
    return worth;
}

int updateBankruptcyState(Player players[], Property board[], int playerID)
{
    Player *player = &players[playerID];
    int worth = calculateNetWorth(board, players, playerID);

    if(player->money <= 0 && worth <= 0)
    {
        if(player->bankrupt == 0)
        {
            printf("\n%s is bankrupt. Cash: LKR %d, Net worth: LKR %d\n",
                   player->name, player->money, worth);
            releaseBankruptProperties(player, board, playerID);
            player->bankrupt = 1;
            player->money = 0;
            return 1;
        }

        player->bankrupt = 1;
        player->money = 0;
        return 1;
    }

    return 0;
}

int checkWinner(Player players[])
{
    int i;
    int activePlayers = 0;
    int winner = -1;

    for(i = 0; i < MAX_PLAYERS; i++)
    {
        if(players[i].bankrupt == 0)
        {
            activePlayers++;
            winner = i;
        }
    }

    if(activePlayers == 1)
    {
        printf("\n========================================\n");
        printf("GAME OVER\n");
        printf("Winner: %s\n", players[winner].name);
        printf("Total Cash : LKR %d\n",players[winner].money);
        printf("Outstanding Loans : LKR %d\n",players[winner].loan);
        printf("Net Worth: LKR %d\n",players[winner].networth);
        printf("========================================\n\n");
        return winner;
    }
    return -1;
}

void determinePlayerOrder(Player players[], int order[])
{
    int rolls[MAX_PLAYERS];
    int i, j;
    printf("\n===== Determining Player Order =====\n");

    // Initial dice rolls
    for(i = 0; i < MAX_PLAYERS; i++)
    {
        rolls[i] = rollDice();
        printf("%s rolled %d\n", players[i].name, rolls[i]);
        order[i] = i;
    }

    // Resolve ties
    for(i = 0; i < MAX_PLAYERS; i++)
    {
        for(j = i + 1; j < MAX_PLAYERS; j++)
        {
            while(rolls[i] == rolls[j])
            {
                printf("\nTie between %s and %s\n", players[i].name, players[j].name);

                rolls[i] = rollDice();
                rolls[j] = rollDice();

                printf("%s rolled %d again\n", players[i].name, rolls[i]);
                printf("%s rolled %d again\n", players[j].name, rolls[j]);
            }
        }
    }

    // Sort players by highest dice
    for(i = 0; i < MAX_PLAYERS - 1; i++)
    {
        for(j = i + 1; j < MAX_PLAYERS; j++)
        {
            if(rolls[i] < rolls[j])
            {
                int temp = rolls[i];
                rolls[i] = rolls[j];
                rolls[j] = temp;

                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    printf("\n===== Final Turn Order =====\n");

    for(i = 0; i < MAX_PLAYERS; i++)
    {
        printf("%d. %s (%d)\n", i + 1, players[order[i]].name, rolls[i]);
    }
}

int shouldBuyProperty(Player *player, Property *property)
{
    int remainingMoney = player->money - property->price;

    if (player->strategy.type == AGGRESSIVE_INVESTOR)
    {
        if (remainingMoney >= property->rent)
        {
            return 1;
        }
        return 0;
    }

    if(player->strategy.type == CONSERVATIVE_BANKER)
    {
        if(remainingMoney >= player->money / 2)
        {
            return 1;
        }
        return 0;
    }

    if(player->strategy.type == RISK_TAKER)
    {
        if(player->money >= property->price)
        {
            return 1;
        }
        return 0;
    }

    if(player->strategy.type == OPPORTUNISTIC_TRADER)
    {
        if(player->money >= property->price)
        {
            return 1;
        }
        return 0;
    }

    return 0;
}

int getMaximumBid(Player *player, Property *property)
{
    if (player->strategy.type == AGGRESSIVE_INVESTOR)
    {
        return property->price * 120 / 100;
    }
    if (player->strategy.type == CONSERVATIVE_BANKER)
    {
        return property->price;
    }
    if (player->strategy.type == RISK_TAKER)
    {
        return player->money;
    }
    if (player->strategy.type == OPPORTUNISTIC_TRADER)
    {
        return property->price;
    }
    return 0;
}

InsuranceType chooseInsurance(Player *player, Property *property)
{
    if(property->insurance != NO_INSURANCE)
    {
        return NO_INSURANCE;
    }
    
    if(property->type != PROPERTY)
    {
        return NO_INSURANCE;
    }
    
    if(player->strategy.type == AGGRESSIVE_INVESTOR)
    {
        if(property->hotel > 0)
            return COMPREHENSIVE_INSURANCE;

        if(property->houses > 0)
            return BASIC_INSURANCE;
    }
    if(player->strategy.type == CONSERVATIVE_BANKER)
    {
        if(property->houses > 0 || property->hotel > 0)
        {
            return COMPREHENSIVE_INSURANCE;
        }
    }
    if(player->strategy.type == RISK_TAKER)
    {
        return NO_INSURANCE;
    }
    if(player->strategy.type == OPPORTUNISTIC_TRADER)
    {
        if(property->hotel > 0)
            return COMPREHENSIVE_INSURANCE;
    }

    return NO_INSURANCE;
}

int handleJail(Player *player)
{
    if(player->jailTurns == 0)
    {
        return 0;
    }

    printf("\n%s is in JAIL for %d more turns\n", player->name, player->jailTurns);

    if(player->strategy.type == AGGRESSIVE_INVESTOR || player->strategy.type == CONSERVATIVE_BANKER)
    {
        if(player->money >= 300)
        {
            printf("%s pays LKR 300 bail to leave jail\n", player->name);
            player->money -= 300;
            player->jailTurns = 0;
            return 1;
        }
    }

    if(player->strategy.type == RISK_TAKER)
    {
        printf("%s chooses to stay in jail and try rolling doubles\n", player->name);
        player->jailTurns--;
        if(player->jailTurns == 0)
        {
            printf("%s has served time and is released from jail\n", player->name);
        }
        return 0;
    }

    if(player->strategy.type == OPPORTUNISTIC_TRADER)
    {
        printf("%s chooses to stay in jail\n", player->name);
        player->jailTurns--;
        if(player->jailTurns == 0)
        {
            printf("%s has served time and is released from jail\n", player->name);
        }
        return 0;
    }

    return 0;
}
