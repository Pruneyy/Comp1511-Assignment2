//A program that finds the distance from the closest petrol station (from seller) to the buyer
//Written 17 May 2017
//By Pranav Singh z3461857 
//For COMP1511 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trader_bot.h"
#include "functions.h"

int petrol_buyer (struct bot *b) {

    struct location  *cur = b->location;    //Current location
    struct location  *buy = b->location;    //Buyer location

    int counter = 0;                        //Counter used for loops
    int forward = 0;                        //Forward distance to petrol station from buyer
    int backward = 0;                       //Backward distance from buyer to petrol station
    int distance = 0;                       //Best distance (forward or backward)
    
    int buyer = find_buyer(b);              //Distance to buyer from start
    int seller = find_seller(b);            //Distance to seller from start
    int petrol = seller_petrol(b);          //Distance to petrol station from seller

    //Move cur to seller location
    if (seller >= 0) {
        while (counter < seller) {
            cur = cur->next;
            counter++;
        }
    } else {
        while (counter > seller) {
            cur = cur->previous;
            counter--;
        }
    }

    //Move cur from seller location to petrol station
    counter = 0;
    if (petrol >= 0) {
        while (counter < petrol) {
            cur = cur->next;
            counter++;
        }
    } else {
        while (counter > petrol) {
            cur = cur->previous;
            counter--;
        }
    }
       
    //Move buy to buyer location
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

    //Checking forward direction for buyer from petrol station
    for(forward = 0; strcmp(cur->name, buy->name) != 0; forward++) {
        cur = cur->next;
    }

    //Resetting cur to seller location
    cur = b->location;
    counter = 0;
    if (seller >= 0) {
        while (counter < seller) {
            cur = cur->next;
            counter++;
        }
    } else {
        while (counter > seller) {
            cur = cur->previous;
            counter--;
        }
    }

    //Moving cur to petrol station
    counter = 0;
    if (petrol >= 0) {
        while (counter < petrol) {
            cur = cur->next;
            counter++;
        }
    } else {
        while (counter > petrol) {
            cur = cur->previous;
            counter--;
        }
    }

    //Checking backward direction for buyer from petrol station
    for(backward = 0; strcmp(cur->name, buy->name) != 0; backward--) {
        cur = cur->previous;
    }

    //Finding the shortest distance
    if(forward <= (-1*backward)) {
        distance = forward;
    } else {
        distance = backward;
    }

    return distance;
}

