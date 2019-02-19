//A program that finds the total amount of available fuel in the world
//Written 26 May 2017
//By Pranav Singh z3461857 
//For COMP1511 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trader_bot.h"
#include "functions.h"

#define FLAG 1000                           //Flag for loops

int fuel_amount (struct bot *b) {

    struct location  *loc = b->location;    //Starting location

    int i = 0;                              //Dummy variable to account for starting case in loop
    int fuel = 0;                           //Counter for total fuel in world

    //Loop around the world
    while ((i == 0) || (loc != b->location)) {
        //Checks if location is a petrol station
        if (loc->type == LOCATION_PETROL_STATION) {
            //Adds petrol station fuel quantity to fuel variable
            fuel = fuel + loc->quantity;
            loc = loc->next;
        } else {
            loc = loc->next;
        }
        i = FLAG;
    }

    return fuel;
}

