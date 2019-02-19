//A program that finds the distance from start to seller to petrol station
//Written 20 May 2017
//By Pranav Singh z3461857 
//For COMP1511 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trader_bot.h"
#include "functions.h"

#define INITIAL 10000                       //Initialisation number for forward and backward (can be any number other than 0)

int check_fuel (struct bot *b) {

    struct location  *cur = b->location;    //Current location

    int total = 0;                          //Total distance to petrol station from start->seller->petrol
    int counter = 0;                        //Counter used for loops
    int forward = 0;                        //Forward direction to petrol station
    int backward = 0;                       //Backward direction to petrol station
    int distance = 0;                       //Final distance (forward or backward) from seller to petrol station

    int seller = find_seller(b);            //Distance to seller from start
    int worldCount = world_count(b);        //Total locations in the world

    forward = INITIAL;                      //Initialising forward variable to something other than 0
    backward = -1 * INITIAL;                //Initialising backward variable to something other than 0

    //Move cur to seller
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

    //Loop to find closest petrol station to seller in forward direction
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

    //Resets cur to seller location
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

    //Loop to find closest petrol station in a backward direction
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

    total =  abs(seller) + abs(distance);

    return total;
}

