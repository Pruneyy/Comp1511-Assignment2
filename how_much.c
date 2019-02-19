//A program that calculates how much of a commodity to buy based on weight, volume and price
//Written 18 May 2017
//By Pranav Singh z3461857 
//For COMP1511 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trader_bot.h"
#include "functions.h"

int how_much (struct bot *b) {

    struct location  *sell = b->location;   //Seller location
    struct location  *buy = b->location;    //Buyer location

    int counter = 0;                        //Counter variable to move to seller and buyer
    int botQuantity = 0;                    //Maximum quantity of a commodity that the bot can hold based on its weight and volume restrictions
    int maxCommodityQuantity = 0;           //Maximum amount of commodity that can be bought (based on weight and volume)

    int buyer = find_buyer(b);              //Distance from Start -> Buyer
    int seller = find_seller(b);            //Distance from Start -> Seller

    //Moves 'sell' to seller location
    if (seller >= 0) {
        while (counter < seller) {
            sell = sell->next;
            counter++;
        }
    } else {
        while (counter > seller) {
            sell = sell->previous;
            counter--;
        }
    }

    //Moves 'buy' to buyer location
    counter = 0;
    if (buyer >= 0) {
        while (counter < buyer) {
            buy = buy->next;
            counter++;
        }
    } else {
        while (counter > buyer) {
            buy = buy->previous;
            counter--;
        }
    }

    //Calculation for profit
    botQuantity = fmin((b->maximum_cargo_weight/sell->commodity->weight), (b->maximum_cargo_volume/sell->commodity->volume));
    maxCommodityQuantity = fmin(fmin(fmin(botQuantity, sell->quantity), buy->quantity), b->cash / sell->price);

    return maxCommodityQuantity;
}

