//A program that finds the distance from start to buyer to petrol station
//Written 21 May 2017
//By Pranav Singh z3461857 
//For COMP1511 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trader_bot.h"
#include "functions.h"

#define INITIAL 10000                       //Initialisation number for forward and backward (can be any number other than 0)

int check_fuel_buy (struct bot *b) {

    struct location  *buy = b->location;    //Buyer location

    int total = 0;                          //Total distance from buyer to nearest petrol station
    int counter = 0;                        //Counter used for loops
    int forward = 0;                        //Forward distance to petrol station from buyer
    int backward = 0;                       //Backward distance from buyer to petrol station
    int distance = 0;                       //Best distance (forward or backward)

    int buyer = find_buyer(b);              //Distance to buyer
    int worldCount = world_count(b);        //Total amount of locations in the world

    forward = INITIAL;                      //Initialising forward variable to something other than 0
    backward = -1 * INITIAL;                //Initialising backward variable to something other than 0

    //Move 'buy' to buyer location
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

    //Check for petrol station closest to buyer in forward direction
    counter = 0;
    while (counter < worldCount) {
        if (buy->type == LOCATION_PETROL_STATION) {
            if (buy->quantity != 0) {
                forward = counter;
                break;
            }
        }
        counter++;
        buy = buy->next;
    }

    //Reset 'buy' to buyer location
    counter = 0;
    buy = b->location;
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

    //Check for petrol station closest to buyer in backward direction
    counter = 0;
    while (counter > (-1 * worldCount)) {
        if (buy->type == LOCATION_PETROL_STATION) {
            if (buy->quantity != 0) {
                backward = counter;
                break;
            }
        }
        counter--;
        buy = buy->previous;
    }

    //Finding the shortest distance
    if(forward <= (-1*backward)) {
        distance = forward;
    } else {
        distance = backward;
    }

    //Checking to make sure forward and backward are not at their initial values - if they are, set distance to 0
    if (distance > 1000) {
        distance = 0;
    } else if (distance < -1000) {
        distance = 0;
    }

    total =  abs(buyer) + abs(distance);

    return total;
}

