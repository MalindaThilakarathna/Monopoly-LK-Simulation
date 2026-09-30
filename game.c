#include <stdio.h>

#include "game.h"
#include "player.h"
#include "finance.h"
#include "event.h"
#include "types.h"

void startGame(Property board[], Player players[], int order[])
{
    int round = 1;
    //int turn = 1;
    int i;
    int dice;
    int currentPlayer;
    int canMove;
    //int playerPassedGo[MAX_PLAYERS]={0,0,0,0};
    

    while(round <= 500)
    {
        printf("\n==============================\n");
        printf("            ROUND %d        \n", round);
        printf("==============================\n");

        for(i = 0; i < MAX_PLAYERS; i++)
        {
            currentPlayer = order[i];

            if(players[currentPlayer].bankrupt == 1)
            {
                continue;
            }

            printf("\n%s TURN (round %d)\n", players[currentPlayer].name,round);

            // Check player in jail
            canMove = handleJail(&players[currentPlayer]);

            if(canMove == 1 || players[currentPlayer].jailTurns == 0)
            {
                dice = rollDice();
                printf("Rolled : %d\n", dice);
                //int oldPos =players[currentPlayer].position;
                movePlayer(&players[currentPlayer], dice);
                /*int newPos =players[currentPlayer].position;

                      // Track when player passes GO
                if (newPos < oldPos)
                {
                    playerPassedGo[currentPlayer] = 1;
                }                                                       */

                checkSquare(board, players, currentPlayer, dice, round);
            }
            else
            {
                printf("%s remains in jail this turn\n", players[currentPlayer].name);
            }
            
            updateBankruptcyState(players, board, currentPlayer);
            if(checkWinner(players) != -1)
            {
                return;
            }
            printf("\n-------------------------------------------------\n");
        }

        /*     // Check if ALL active players have completed their lap around the 40 squares
        int allPassed =1;
        for (i=0; i < MAX_PLAYERS; i++)
        {
            if(players[i].bankrupt == 0 && playerPassedGo[i] == 0)
            {
                allPassed = 0;
                turn +=1;
                break;
            }
        }

        // Complete Round only finishes when all active players have passed the 40 squares
        if(allPassed == 1)
        {
            printf("\n=================================================\n");
            printf("   ALL PLAYERS COMPLETED 40 SQUARES: ROUND %d END   \n", round);
            printf("=================================================\n");                */

            // Trigger Inflation and Market Boom every 10 rounds 
            if(round % 10 == 0)
            {
                applyInflation(board, round);
                updatePropertyMarket(board, round);
            }
            // Trigger Regional Development Cards every 15 rounds 
            if (round % 15 == 0)
            {
                drawRegionalDevelopmentCard(board, round);
            }
            //Government regulations
            if (round % 20 == 0)
            {
                triggerGovernmentRegulation(board, players, round);
            }

            // Compounding loan interest and default checking at round end 
            addLoanInterest(players, board);
            //check property age
            processPropertyDepreciation(board);
            // Insurance checks and event expiry
            checkInsuranceExpiry(players, board, round);
            applyExpiredEventEffects(board, players, round);

            printf("\n========== Round %d Completed ==========\n\n", round);

            printf("\n========== Round %d Summary ==========\n", round);
            
            for(i = 0; i < MAX_PLAYERS; i++)
            {
                int calNetworth= calculateNetWorth(board,players,i);
                players[i].networth = calNetworth;
                printPlayer(players[i]);
            }
            /*
            // Reset circuit flags for all players for the next round
            for(i = 0; i < MAX_PLAYERS; i++)
            {
                playerPassedGo[i] = 0;
            }  */
            round++;
            
            //turn = 1;
        //}
    }

    // Determine winner after 500 rounds by highest net worth
    int highestWorth = -1;
    int winner = -1;
    for(i = 0; i < MAX_PLAYERS; i++)
    {
        if(players[i].bankrupt == 0)
        {
            int worth = calculateNetWorth(board, players, i);
            if(worth > highestWorth)
            {
                highestWorth = worth;
                winner = i;
            }
        }
    }
    if(winner != -1)
    {
        printf("\n========================================\n");
        printf("GAME OVER\n");
        printf("Winner (500 Rounds Completed): %s\n", players[winner].name);
        printf("Total Cash : LKR %d\n",players[winner].money);
        printf("Outstanding Loans : LKR %d\n",players[winner].loan);
        printf("Net Worth: LKR %d\n", highestWorth);
        printf("========================================\n\n");
    }
}

void checkSquare(Property board[], Player players[], int currentPlayer, int dice, int round)
{
    int position = players[currentPlayer].position;
    Property *square = &board[position];
    int previousPosition = position - dice;
    
    if(previousPosition < 0)
    {
        previousPosition += BOARD_SIZE;
    }
    printf("\n%s moves from square %d to square %d\n", players[currentPlayer].name, previousPosition, position);
    printf("%s landed on %s\n\n", players[currentPlayer].name, square->name);

    if(square->type == PROPERTY || square->type == RAILWAY || square->type == UTILITY)
    {
        if(square->owner == -1)
        {
            if(shouldBuyProperty(&players[currentPlayer], square))
            {
                buyProperty(square, &players[currentPlayer], currentPlayer);
            }
            else
            {
                auctionProperty(square, players);
            }
        }
        else if(square->owner != currentPlayer)
        {
            payRent(square, players, currentPlayer, dice, round);
        }
        else
        {
            printf("Already owned by %s\n", players[currentPlayer].name);
            // Check property is depreciated
            if (square->depreciation > 0)
            {
                renovateProperty(square, &players[currentPlayer]);
            }
        }
        
        if (square->type == PROPERTY && square->owner == currentPlayer)
        {
            buildHouse(board, square, &players[currentPlayer], round);
        }
    }
    else if(square->type == TAX)
    {
        int tax= players[currentPlayer].money*0.15;
        printf("Paying tax of LKR %d\n",tax);
        players[currentPlayer].money -= tax;
    }
    else if(square->type == EVENT)
    {
        drawEventCard(board, players, currentPlayer, round);
    }
    else if(square->type == INSURANCE)
    {
        InsuranceType type = chooseInsurance(&players[currentPlayer], &board[position]);
        if(type != NO_INSURANCE)
        {
            buyInsurance(&players[currentPlayer], &board[position], type, round);
        }
    }
    else if(square->type == BANK)
    {
        processBank(&players[currentPlayer], board, currentPlayer);
    }
    else if(square->type == JAIL)
    {
        printf("Just visiting Jail.\n");
    }
    else if(square->type == FREE_PARKING)
    {
        printf("............Free Parking............\n");
    }
    else if(square->type == GO_TO_JAIL)
    {
        printf("%s is sent to Jail!\n", players[currentPlayer].name);
        players[currentPlayer].position = 10;
        players[currentPlayer].jailTurns = 3;
        printf("Player will be in jail for up to 3 turns. Can pay LKR 300 bail or wait 3 turns\n");
    }
}
