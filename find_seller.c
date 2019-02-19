//A program that finds the most profitable seller of a commodity
//Written 19 May 2017 (edited daily)
//By Pranav Singh z3461857 
//For COMP1511 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trader_bot.h"
#include "functions.h"

#define MAX_LEN 1024                            //Maximum length of array (equal to maximum possible locations)
#define FLAG 1000                               //Flag for loops

int find_seller (struct bot *b) {

    struct location  *cur = b->location;        //Current location (sellers)
    struct location  *future = b->location;     //Future location (potential buyers)

    int i = 0;                                  //Array counter
    int j = 0;                                  //Dummy variable to allow outer loop iteration through                        
    int k = 0;                                  //Dummy variable to allow inner loop iteration through
    int counter = 0;                            //Counter to determine if direction to seller is forward or backward
    int forward = 0;                            //Forward direction counter to seller
    int backward = 0;                           //Backward direction counter to seller
    int distance = 0;                           //Final distance to seller output
    int botQuantity = 0;                        //Maximum quantity of a commodity that the bot can hold based on its weight and volume restrictions
    int maxCommodityQuantity = 0;               //Maximum amount of commodity that can be bought (based on weight and volume)
    int profitability[MAX_LEN] = {0};           //Array to hold all the possible profits in the world

    double max = 0;                             //Variable for maximum profit in array
    double profit = 0;                          //Variable for calculated profit based on commodity price and maximum amount of commodity that can be bought


    //Loop to find most profitable seller
    while ((j == 0) || (cur != b->location)) {
        //Check if location is a seller
        if (cur->type == LOCATION_SELLER) {
            k = 0;
            //Nested loop to find buyer
            while ((k == 0) || (future != b->location)) {
                //Check if buyer
                if (future->type != LOCATION_BUYER) { 
                    profit = 0;
                //Check if same commodity as seller
                } else if (strcmp(cur->commodity->name, future->commodity->name) != 0) {
                    profit = 0;
                //If it is a buyer and the same commodity then calculate profit potential here
                } else {
                    //Quantity of commodity that can fit in bot
                    botQuantity = fmin((b->maximum_cargo_weight/cur->commodity->weight), (b->maximum_cargo_volume/cur->commodity->volume));
                    maxCommodityQuantity = fmin(fmin(botQuantity, cur->quantity), future->quantity);
                    //Profit calculation
                    profit = future->price * maxCommodityQuantity - cur->price * maxCommodityQuantity;
                    //Accounting for 2 or more buyers of the same commodity
                    max = profitability[i];
                    if (profit > max) {
                        profitability[i] = profit;
                    } else {
                        profitability[i] = max;
                    }                   
                }
                future = future->next;
                k = FLAG;
            }
        } else {
            profitability[i] = 0;
        }
        i++;
        cur = cur->next;
        j = FLAG;
    }

    //Finding seller who will give the maximum profit
    max = 0;
    for (i = 0; i < MAX_LEN; i++) {
        if (profitability[i] > max) {
            max = profitability[i];
        }
    }

    //Checking forward direction to seller
    while (profitability[forward] != max) {
        forward++;
    }
    cur = b->location;
    while (counter < forward) {
        cur = cur->next;
        counter++;
    }

    //Checking backward direction to seller
    future = b->location;
    while (strcmp(future->name, cur->name) != 0) {
        backward--;
        future = future->previous;
    }

    //Determining if forward or backward direction to seller is shorter
    if(forward <= (-1*backward)) {
        distance = forward;
    } else {
        distance = backward;
    }

    return distance;
}

