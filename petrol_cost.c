//A program that calculates the average petrol price in the world
//Written 17 May 2017
//By Pranav Singh z3461857 
//For COMP1511 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trader_bot.h"
#include "functions.h"

int petrol_price (struct bot *b) {

    struct location  *cur = b->location;    //Current location

    int counter = 0;                        //Counter for loop
    int totalPetrolPrice = 0;               //Total petrol price
    int averagePetrolPrice = 0;             //Average petrol price
    int amountPetrolStations = 0;           //Amount of petrol stations in world

    int worldCount = world_count(b);        //Total locations in the world

    //Loop to find petrol stations 
    while (counter < worldCount) {
        if (cur->type == LOCATION_PETROL_STATION) {
            //Adds prices at petrol stations to a running total
            totalPetrolPrice = totalPetrolPrice + cur->price;
            amountPetrolStations++;
        }
        cur = cur->next;
        counter++;
    }

    //Calculation for average petrol price
    averagePetrolPrice = totalPetrolPrice / amountPetrolStations;

    return averagePetrolPrice;
}

