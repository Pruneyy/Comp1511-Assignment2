//A program that finds the most profitable buyer after finding the best seller
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

int find_buyer (struct bot *b) {

    struct location  *cur = b->location;        //Current location
    struct location  *sell = b->location;       //Seller location
    struct location  *future = b->location;     //Used to compare to cur when determing backward distance to buyer

    int i = 0;                                  //Variable used to assign elements to the array
    int j = 0;                                  //Dummy variable to account for first case in loop
    int counter = 0;                            //Counter for loops
    int forward = 0;                            //Forward distance to best buyer
    int backward = 0;                           //Backward distance to best buyer
    int distance = 0;                           //Final distance to best buyer
    int botQuantity = 0;                        //Maximum quantity of a commodity that the bot can hold based on its weight and volume restrictions
    int profitability[MAX_LEN] = {0};           //Array to hold calculated values of profit

    int seller = find_seller(b);                //Distance to seller from start

    double max = 0;                             //Variable for maximum profit in array
    double profit = 0;                          //Variable for calculated profit based on commodity price and maximum amount of commodity that can be bought


    //Move bot to seller
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

    //Finding a buyer if the bot currently has no cargo
    if (b->cargo == NULL) {

        //Loop to check if current location is a buyer -> if so, check if it buys the same commodity as the seller found above sells -> if so, calculate potential profit and stick in array
        while ((j == 0) || (cur != b->location)) {
            //Check if buyer
            if (cur->type == LOCATION_BUYER) {
                //Ensure same commodity as seller
                if (strcmp(cur->commodity->name, sell->commodity->name) == 0) {
                    //Check if you can sell as much as the store buys or if you're limited to cargo capacity
                    botQuantity = fmin((b->maximum_cargo_weight/cur->commodity->weight), (b->maximum_cargo_volume/cur->commodity->volume));
                    //(It should theoretically never hit this if statement as long as we buy the right amount, but including it just in case)
                    if (cur->quantity >= botQuantity) {
                        profit = botQuantity * cur->price;
                        profitability[i] = profit;
                    } else {
                        profit = cur->quantity * cur->price;
                        profitability[i] = profit;
                    }
                }
            }
            i++;
            cur = cur->next;
            j = FLAG;
        }

    //Finding a buyer if the bot does have cargo in it
    } else if (b->cargo != NULL) {
        //Loop to check if current location is a buyer -> if so, check if it buys the same commodity as the seller found above sells -> if so, calculate potential profit and stick in array
        while ((j == 0) || (cur != b->location)) {
            //Check if buyer
            if (cur->type == LOCATION_BUYER) {
                //Ensure same commodity as what is in bot
                if (strcmp(cur->commodity->name, b->cargo->commodity->name) == 0) {
                    //Check if you can sell as much as the store buys or limited to cargo capacity
                    botQuantity = fmin((b->maximum_cargo_weight/cur->commodity->weight), (b->maximum_cargo_volume/cur->commodity->volume));
                    //(It should theoretically never hit this if statement as long as we buy the right amount, but including it just in case)
                    if (cur->quantity >= botQuantity) {
                        profit = botQuantity * cur->price;
                        profitability[i] = profit;
                    } else {
                        profit = cur->quantity * cur->price;
                        profitability[i] = profit;
                    }
                }
            }
            i++;
            cur = cur->next;
            j = FLAG;
        }
    }

    //Finding maximum value in the array
    for (i = 0; i < MAX_LEN; i++) {
        if (profitability[i] > max) {
            max = profitability[i];
        }
    }

    //Finds forward direction distance
    while (profitability[forward] != max) {
        forward++;
    }
    counter = 0;
    cur = b->location;
    while (counter < forward) {
        cur = cur->next;
        counter++;
    }

    //Finds backward direction distance
    future = b->location;
    while (strcmp(future->name, cur->name) != 0) {
        backward--;
        future = future->previous;
    }

    //Determines if going forward or backward is better
    if(forward <= (-1*backward)) {
        distance = forward;
    } else {
        distance = backward;
    }

    return distance;
}
