#include <stdio.h>
#include <string.h>

#include "board.h"

void initializeBoard(Property board[])
{
    int i;
    // Default values 
    for(i = 0; i < BOARD_SIZE; i++)
    {
        strcpy(board[i].name, "");
        board[i].type = GO;
        board[i].group = NONE;
        board[i].price = 0;
        board[i].rent = 0;
        board[i].houseCost = 0;
        board[i].hotelCost = 0;
        board[i].mortgage = 0;
        board[i].owner = -1;
        board[i].houses = 0;
        board[i].hotel = 0;
        board[i].mortgaged = 0; 
        board[i].insurance = NO_INSURANCE;
        board[i].insuranceExpiry = 0;
        board[i].isLoanLocked = 0;
        board[i].age = 0;
        board[i].depreciation = 0;
    }

    // Square 0  
    strcpy(board[0].name, "GO");
    board[0].type = GO;

    // Square 1 
    strcpy(board[1].name, "Pettah");
    board[1].type = PROPERTY;
    board[1].group = BROWN;
    board[1].price = 1500;
    board[1].rent = 100;
    board[1].houseCost = 500;
    board[1].hotelCost = 2000;
    board[1].mortgage = 750;

    // Square 2
    strcpy(board[2].name, "Community Development Fund");
    board[2].type = EVENT;

    // Square 3 
    strcpy(board[3].name, "Maradana");
    board[3].type = PROPERTY;
    board[3].group = BROWN;
    board[3].price = 1800;
    board[3].rent = 120;
    board[3].houseCost = 500;
    board[3].hotelCost = 2000;
    board[3].mortgage = 750;

    // Square 4
    strcpy(board[4].name, "Income Tax");
    board[4].type = TAX;

    // Square 5
    strcpy(board[5].name, "Colombo Fort Railway");
    board[5].type = RAILWAY;
    board[5].price = 1500;
    board[5].mortgage = 750;
    board[5].owner = -1;

    // Square 6
    strcpy(board[6].name, "Bambalapitiya");
    board[6].type = PROPERTY;
    board[6].group = LIGHT_BLUE;
    board[6].price = 2500;
    board[6].rent = 180;
    board[6].houseCost = 750;
    board[6].hotelCost = 3000;
    board[6].mortgage = 1250;

    // Square 7
    strcpy(board[7].name, "National Event Card");
    board[7].type = EVENT;

    // Square 8
    strcpy(board[8].name, "Wellawatte");
    board[8].type = PROPERTY;
    board[8].group = LIGHT_BLUE;
    board[8].price = 2700;
    board[8].rent = 200;
    board[8].houseCost = 750;
    board[8].hotelCost = 3000;
    board[8].mortgage = 1250;

    // Square 9
    strcpy(board[9].name, "Mount Lavinia");
    board[9].type = PROPERTY;
    board[9].group = LIGHT_BLUE;
    board[9].price = 3000;
    board[9].rent = 220;
    board[9].houseCost = 750;
    board[9].hotelCost = 3000;
    board[9].mortgage = 1250;

    // Square 10
    strcpy(board[10].name, "Jail / Just Visiting");
    board[10].type = JAIL;

    // Square 11
    strcpy(board[11].name, "Nugegoda");
    board[11].type = PROPERTY;
    board[11].group = PINK;
    board[11].price = 3500;
    board[11].rent = 260;
    board[11].houseCost = 1000;
    board[11].hotelCost = 4000;
    board[11].mortgage = 1750;

    // Square 12
    strcpy(board[12].name, "Ceylon Electricity Board");
    board[12].type = UTILITY; 
    board[12].price = 1500;
    board[12].mortgage = 750;
    board[12].owner = -1; 

    // Square 13
    strcpy(board[13].name, "Maharagama");
    board[13].type = PROPERTY;
    board[13].group = PINK;
    board[13].price = 3800;
    board[13].rent = 280;
    board[13].houseCost = 1000;
    board[13].hotelCost = 4000;
    board[13].mortgage = 1750;

    // Square 14
    strcpy(board[14].name, "Kottawa");
    board[14].type = PROPERTY;
    board[14].group = PINK;
    board[14].price = 4000;
    board[14].rent = 300;
    board[14].houseCost = 1000;
    board[14].hotelCost = 4000;
    board[14].mortgage = 1750;

    // Square 15
    strcpy(board[15].name, "Kandy Railway Station");
    board[15].type = RAILWAY;
    board[15].price = 1500;
    board[15].mortgage = 750;
    board[15].owner = -1;

    // Square 16
    strcpy(board[16].name, "Negombo");
    board[16].type = PROPERTY;
    board[16].group = ORANGE;
    board[16].price = 4500;
    board[16].rent = 350;
    board[16].houseCost = 1250;
    board[16].hotelCost = 5000;
    board[16].mortgage = 2250;

    // Square 17
    strcpy(board[17].name, "Sri Lanka Insurance");
    board[17].type = INSURANCE;

    // Square 18
    strcpy(board[18].name, "Katunayake");
    board[18].type = PROPERTY;
    board[18].group = ORANGE;
    board[18].price = 4700;
    board[18].rent = 370;
    board[18].houseCost = 1250;
    board[18].hotelCost = 5000;
    board[18].mortgage = 2250;

    // Square 19
    strcpy(board[19].name, "Ja-Ela");
    board[19].type = PROPERTY;
    board[19].group = ORANGE;
    board[19].price = 5000;
    board[19].rent = 400;
    board[19].houseCost = 1250;
    board[19].hotelCost = 5000;
    board[19].mortgage = 2250;

    // Square 20
    strcpy(board[20].name, "Free Parking");
    board[20].type = FREE_PARKING;

    // Square 21
    strcpy(board[21].name, "Kandy City");
    board[21].type = PROPERTY;
    board[21].group = RED;
    board[21].price = 5500;
    board[21].rent = 450;
    board[21].houseCost = 1500;
    board[21].hotelCost = 6000;
    board[21].mortgage = 2750;

    // Square 22
    strcpy(board[22].name, "National Event Card");
    board[22].type = EVENT;

    // Square 23
    strcpy(board[23].name, "Peradeniya");
    board[23].type = PROPERTY;
    board[23].group = RED;
    board[23].price = 5800;
    board[23].rent = 480;
    board[23].houseCost = 1500;
    board[23].hotelCost = 6000;
    board[23].mortgage = 2750;

    // Square 24
    strcpy(board[24].name, "Katugastota");
    board[24].type = PROPERTY;
    board[24].group = RED;
    board[24].price = 6000;
    board[24].rent = 500;
    board[24].houseCost = 1500;
    board[24].hotelCost = 6000;
    board[24].mortgage = 2750;

    // Square 25
    strcpy(board[25].name, "Galle Railway Station");
    board[25].type = RAILWAY;
    board[25].price = 1500;
    board[25].mortgage = 750;
    board[25].owner = -1;  

    // Square 26
    strcpy(board[26].name, "Galle Fort");
    board[26].type = PROPERTY;
    board[26].group = YELLOW;
    board[26].price = 6500;
    board[26].rent = 600;
    board[26].houseCost = 2000;
    board[26].hotelCost = 8000;
    board[26].mortgage = 3250;

    // Square 27
    strcpy(board[27].name, "Unawatuna");
    board[27].type = PROPERTY;
    board[27].group = YELLOW;
    board[27].price = 6800;
    board[27].rent = 620;
    board[27].houseCost = 2000;
    board[27].hotelCost = 8000;
    board[27].mortgage = 3250;

    // Square 28
    strcpy(board[28].name, "National Water Supply and Drainage Board");
    board[28].type = UTILITY;
    board[28].price = 1500;
    board[28].mortgage = 750;
    board[28].owner = -1;

    // Square 29
    strcpy(board[29].name, "Hikkaduwa");
    board[29].type = PROPERTY;
    board[29].group = YELLOW;
    board[29].price = 7000;
    board[29].rent = 650;
    board[29].houseCost = 2000;
    board[29].hotelCost = 8000;
    board[29].mortgage = 3250;

    // Square 30
    strcpy(board[30].name, "Go To Jail");
    board[30].type = GO_TO_JAIL;

    // Square 31
    strcpy(board[31].name, "Jaffna Town");
    board[31].type = PROPERTY;
    board[31].group = GREEN;
    board[31].price = 8000;
    board[31].rent = 750;
    board[31].houseCost = 2500;
    board[31].hotelCost = 10000;
    board[31].mortgage = 4000;

    // Square 32
    strcpy(board[32].name, "Nallur");
    board[32].type = PROPERTY;
    board[32].group = GREEN;
    board[32].price = 8300;
    board[32].rent = 780;
    board[32].houseCost = 2500;
    board[32].hotelCost = 10000;
    board[32].mortgage = 4000;

    // Square 33
    strcpy(board[33].name, "Ceylon Insurance");
    board[33].type = INSURANCE;

    // Square 34
    strcpy(board[34].name, "Trincomalee");
    board[34].type = PROPERTY;
    board[34].group = GREEN;
    board[34].price = 8500;
    board[34].rent = 800;
    board[34].houseCost = 2500;
    board[34].hotelCost = 10000;
    board[34].mortgage = 4000;

    // Square 35
    strcpy(board[35].name, "Jaffna Railway Station");
    board[35].type = RAILWAY;
    board[35].price = 1500;
    board[35].mortgage = 750;
    board[35].owner = -1;

    // Square 36
    strcpy(board[36].name, "National Event Card");
    board[36].type = EVENT;

    // Square 37
    strcpy(board[37].name, "Nuwara Eliya");
    board[37].type = PROPERTY;
    board[37].group = DARK_BLUE;
    board[37].price = 10000;
    board[37].rent = 1000;
    board[37].houseCost = 3000;
    board[37].hotelCost = 12000;
    board[37].mortgage = 5000;

    // Square 38
    strcpy(board[38].name, "Bank Of Ceylon");
    board[38].type = BANK;

    // Square 39
    strcpy(board[39].name, "Galle face");
    board[39].type = PROPERTY;
    board[39].group = DARK_BLUE;
    board[39].price = 12000;
    board[39].rent = 1200;
    board[39].houseCost = 3000;
    board[39].hotelCost = 12000;
    board[39].mortgage = 5000;
}
