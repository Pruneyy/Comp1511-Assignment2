//A program that finds the closest petrol station to the buyer
//Written 17 May 2017
//By Pranav Singh z3461857 
//For COMP1511 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trader_bot.h"
#include "functions.h"

int buyer_petrol (struct bot *b) {

    struct location  *buy = b->location;    //Buyer location

    int counter = 0;                        //Counter used for loops
    int forward = 0;                        //Forward distance to petrol station from buyer
    int backward = 0;                       //Backward distance from buyer to petrol station
    int distance = 0;                       //Best distance (forward or backward)

    int buyer = find_buyer(b);              //Distance to buyer

    //Move buy to buyer location
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
        
    //Checking forward distance for nearest petrol station to buyer
    for(forward = 0; buy->type != LOCATION_PETROL_STATION; forward++) {
        buy = buy->next;
    }

    //Reset buy to buyer location
    buy = b->location;
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

    //Checking backward distance for nearest petrol station to buyer
    for(backward = 0; buy->type != LOCATION_PETROL_STATION; backward--) {
        buy = buy->previous;
    }

    //Finding the shortest distance (forward or backward)
    if(forward <= (-1*backward)) {
        distance = forward;
    } else {
        distance = backward;
    }

    return distance;
}

