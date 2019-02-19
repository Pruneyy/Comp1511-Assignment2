//A program that finds the closest petrol station to the seller
//Written 17 May 2017
//By Pranav Singh z3461857 
//For COMP1511 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trader_bot.h"
#include "functions.h"

#define INITIAL 10000                       //Initialisation number for forward and backward (can be any number other than 0)

int seller_petrol (struct bot *b) {

    struct location  *cur = b->location;    //Current location

    int counter = 0;                        //Counter for loops
    int forward = 0;                        //Forward direction counter to petrol station from seller
    int backward = 0;                       //Backward direction counter to petrol station from seller
    int distance = 0;                       //Final distance to petrol station from seller

    int seller = find_seller(b);            //Output distance to seller from find_seller function
    int worldCount = world_count(b);        //Total amount of locations in the world

    forward = INITIAL;                      //Initialising forward variable to something other than 0
    backward = -1 * INITIAL;                //Initialising backward variable to something other than 0

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

    //Find closest petrol station to seller
    counter = 0;
    while (counter < worldCount) {
        if (cur->type == LOCATION_PETROL_STATION) {
            if (cur->quantity != 0) {
                forward = counter;
                break;
            }
        }
        counter++;
        cur = cur->next;
    }

    //Resetting cur to seller location
    counter = 0;
    cur = b->location;
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

    //Counting backward distance from seller to nearest petrol station
    counter = 0;
    while (counter > (-1 * worldCount)) {
        if (cur->type == LOCATION_PETROL_STATION) {
            if (cur->quantity != 0) {
                backward = counter;
                break;
            }
        }
        counter--;
        cur = cur->previous;
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

    return distance;
}

