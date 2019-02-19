//A program that counts all the locations in the randomly generated world
//Written 17 May 2017
//By Pranav Singh z3461857 
//For COMP1511 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trader_bot.h"
#include "functions.h"

#define FLAG 1000                           //Flag for loop

int world_count (struct bot *b) {

    struct location  *cur = b->location;    //Current location

    int x = 0;                              //Flag variable for loop
    int totalLocations = 0;                 //Total locations counted in world

    //Simple loop to count number of locations in the world
    while (x == 0 || cur != b->location) {
        totalLocations++;
        x = FLAG;
        cur = cur->next;
    }

    return totalLocations;
}



