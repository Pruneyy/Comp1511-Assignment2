//A program that finds the distance from the nearest petrol station at start to the seller
//Written 17 May 2017
//By Pranav Singh z3461857 
//For COMP1511 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trader_bot.h"
#include "functions.h"

int petrol_seller (struct bot *b) {

    struct location  *cur = b->location;    //Current location
    struct location  *sell = b->location;   //Seller location

    int counter = 0;                        //Counter used for loops
    int forward = 0;                        //Forward distance to petrol station from buyer
    int backward = 0;                       //Backward distance from buyer to petrol station
    int distance = 0;                       //Best distance (forward or backward)

    int seller = find_seller(b);            //Distance to seller from start
    int petrol = nearest_fuel(b);           //Distance to nearest petrol station from start

    //Move cur to nearest petrol station from start
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

    //Move sell to seller location
    counter = 0;
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

    //Checking forward direction for seller from petrol station
    for(forward = 0; strcmp(cur->name, sell->name) != 0; forward++) {
        cur = cur->next;
    }

    //Reset cur to petrol station location
    cur = b->location;
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

    //Checking backward direction for seller from petrol station
    for(backward = 0; strcmp(cur->name, sell->name) != 0; backward--) {
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

