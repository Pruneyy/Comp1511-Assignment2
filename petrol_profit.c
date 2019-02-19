//A program that finds the profit of a trade with petrol costs included
//Written 01 June 2017
//By Pranav Singh z3461857 
//For COMP1511 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trader_bot.h"
#include "functions.h"

int petrol_profit (struct bot *b) {

    struct location  *cur = b->location;    //Current location

    int profit = 0;                         //Final profit calculation including petrol price
    int counter = 0;                        //Counter for loops
    int distance = 0;                       //Distance needed to travel
    int commodityPrice = 0;                 //Price of commodity

    int quantity = how_much(b);             //How much can be bought
    int startSeller = find_seller(b);       //Start->seller
    int sellerBuyer = seller_buyer(b);      //Seller->buyer
    int petrolBuyer = petrol_buyer(b);      //Petrol->buyer
    int petrolPrice = petrol_price(b);      //Average fuel cost
    int sellerPetrol = seller_petrol(b);    //Seller->petrol

    //Move cur to seller location
    if (startSeller >= 0) {
        while (counter < startSeller) {
            cur = cur->next;
            counter++;
        }
    } else {
        while (counter > startSeller) {
            cur = cur->previous;
            counter--;
        }
    }

    //Take commodity price from seller location
    commodityPrice = cur->price;

    //Conditional check to find total travel distance

    //First condition -> If there is not enough fuel to go straight from seller to buyer
    if ((startSeller + sellerBuyer) < b->fuel) {
        distance = abs(startSeller) + abs(sellerPetrol) + abs(petrolBuyer);

    //Second condition -> If there is enough fuel to go from seller to buyer without needing to fill up on fuel
    } else {
        distance = abs(startSeller) + abs(sellerBuyer);
    }

    //Basic profit calculation
    profit = quantity * commodityPrice - distance * petrolPrice;

    return profit;
}

