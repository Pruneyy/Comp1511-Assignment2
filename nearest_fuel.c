//A program that calculates the minimum distance to travel to a petrol station
//Written 19 May 2017
//By Pranav Singh z3461857 
//For COMP1511 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trader_bot.h"
#include "functions.h"

#define INITIAL 10000                       //Initialisation number for forward and backward (can be any number other than 0)

int nearest_fuel(struct bot *b) {

    struct location  *cur = b->location;    //Current location

    int counter = 0;                        //Counter for loops
    int forward = 0;                        //Forward direction counter to petrol station from seller
    int backward = 0;                       //Backward direction counter to petrol station from seller
    int distance = 0;                       //Final distance to petrol station from seller   

    int worldCount = world_count(b);        //Total amount of locations in the world

    forward = INITIAL;                      //Initialising forward variable to something other than 0
    backward = -1 * INITIAL;                //Initialising backward variable to something other than 0

    //Loop around the world
    while (counter < worldCount) {
        //Checks if the current location is a petrol station
        if (cur->type == LOCATION_PETROL_STATION) {
            //Ensures there is petrol at the petrol station
            if (cur->quantity != 0) {
                forward = counter;
                break;
            }
        }
        counter++;
        cur = cur->next;
    }

    //Reset counter and cur in order to find closest petrol station behind us
    counter = 0;
    cur = b->location;
    //Loop around the world
    while (counter > (-1 * worldCount)) {
        //Checks if the current location is a petrol station
        if (cur->type == LOCATION_PETROL_STATION) {
            //Ensures there is petrol at the petrol station
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
