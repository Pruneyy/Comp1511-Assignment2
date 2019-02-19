//A program that runs a bot buy and sell commodities
//Written 17 May 2017 (edited daily)
//By Pranav Singh z3461857 
//For COMP1511 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trader_bot.h"
#include "functions.h"

#define FLAG 1000                                                   //Flag for loops

char *get_bot_name(void);

void get_action(struct bot *b, int *action, int *n) {

    struct location  *loc = b->location;                            //Starting location

    int k = 0;                                                      //Dummy variable to run a cycle of selling and buying once before accounting for fuel checks in profitability
    int fuelLost = b->fuel_tank_capacity - b->fuel;                 //Total fuel - remaining fuel

    int amount = how_much(b);                                       //How much can be bought
    int turns = turns_remaining(b);                                 //Turns from start to buyer
    int startBuyer = find_buyer(b);                                 //Start->buyer
    int fuelAmount = fuel_amount(b);                                //Amount of fuel in World
    int worldCount = world_count(b);                                //How many locations there are in the world
    int startSeller = find_seller(b);                               //Start->seller
    int startPetrol = nearest_fuel(b);                              //Start->petrol
    int sellerBuyer = seller_buyer(b);                              //Seller->buyer
    int petrolBuyer = petrol_buyer(b);                              //Petrol->buyer
    int petrolPrice = petrol_price(b);                              //Average petrol price
    int sellerPetrol = seller_petrol(b);                            //Seller->petrol
    int petrolProfit = petrol_profit(b);                            //Profit minus petrol price
    int petrolSeller = petrol_seller(b);                            //Petrol->seller
    int startSellerPetrol = check_fuel(b);                          //Start->seller->petrol
    int sellerBuyerPetrol = check_fuel_buy(b);                      //Seller->buyer->petrol


    //If no commodities in bot (either go to seller [1], go to petrol station [2], buy from seller [3] or buy from petrol station [4]
    if (b->cargo == NULL) {
        if (petrolProfit > 0 || k == 0) {  
            if (startPetrol == 0 && ((abs(startSeller) + abs(sellerBuyer)) > b->fuel) && loc->type != LOCATION_PETROL_STATION) {
                *n = 0;
                *action = ACTION_MOVE;
            //If the distance to the seller + the nearest petrol from seller is MORE than the amount of petrol remaining and we ARE NOT at a petrol station- move to the petrol station [2]
            } else if (startSellerPetrol > b->fuel && startSeller != 0 && loc->type != LOCATION_PETROL_STATION) {
                *n = startPetrol;
                *action = ACTION_MOVE;
                //Ensure we can only move the maximum move
                if (*n >= 0) {
                    if (*n >= b->maximum_move) {
                        *n = b->maximum_move;
                    }
                } else if (*n < 0) {
                    if (*n <= -1 * b->maximum_move) {
                        *n = -1 * b->maximum_move;
                    }
                }
            //If the distance to the seller + the nearest petrol from seller is MORE than the amount of petrol remaining and we ARE at a petrol station - buy fuel to capacity [4]        
            } else if (startSellerPetrol > b->fuel && startSeller != 0 && loc->type == LOCATION_PETROL_STATION) {
                *n = fmin(loc->quantity, fuelLost);
                *action = ACTION_BUY;
            //If the distance to the seller + the nearest petrol from seller is LESS than the amount of petrol remaining and we ARE NOT at the seller - move to the seller [1]
            } else if (startSellerPetrol <= b->fuel && startSeller != 0) {
                *n = startSeller;
                *action = ACTION_MOVE;
                //Ensure we can only move the maximum move
                if (*n >= 0) {
                    if (*n >= b->maximum_move) {
                        *n = b->maximum_move;
                    }
                } else if (*n < 0) {
                    if (*n <= -1 * b->maximum_move) {
                        *n = -1 * b->maximum_move;
                    }
                }
            //If the distance to the seller + the nearest petrol from seller is LESS than the amount of petrol remaining and we ARE at the seller - buy commodities [3]
            } else if (startSellerPetrol <= b->fuel && startSeller == 0) {
                if (b->turns_left < 4) {
                    *n = 0;
                    *action = ACTION_BUY;
                } else {                 
                    *n = amount;
                    *action = ACTION_BUY;
                }            
            }
        //If profit will be <=0 with petrol prices considered, just don't do anything        
        } else {
            *n = 0;
            *action = ACTION_MOVE;
        }

    //If there ARE commodities in bot (either go to buyer [1], go to petrol station [2], sell to buyer [3] or buy from petrol station [4]
    } else if (b->cargo != NULL) {
        k = FLAG;
        //If already at buyer, just sell everything
        if (startBuyer == 0) {
            *n = b->cargo->quantity;
            *action = ACTION_SELL;            

        //If the distance to the buyer + the nearest petrol from buyer is MORE than the amount of petrol remaining and we ARE NOT at a petrol station- move to the petrol station [2]
        } else if (sellerBuyerPetrol > b->fuel && startBuyer != 0 && loc->type != LOCATION_PETROL_STATION && fuelAmount != 0) {
            *n = startPetrol;
            *action = ACTION_MOVE;
            //Ensure we can only move the maximum move
            if (*n >= 0) {
                if (*n >= b->maximum_move) {
                    *n = b->maximum_move;
                }
            } else if (*n < 0) {
                if (*n <= -1 * b->maximum_move) {
                    *n = -1 * b->maximum_move;
                }
            }
        //If the distance to the buyer + the nearest petrol from buyer is MORE than the amount of petrol remaining and we ARE at a petrol station - buy fuel to capacity [4]        
        } else if (sellerBuyerPetrol > b->fuel && startBuyer != 0 && loc->type == LOCATION_PETROL_STATION) {
            *n = fmin(loc->quantity, fuelLost);
            *action = ACTION_BUY;

        //If the distance to the buyer + the nearest petrol from buyer is LESS than the amount of petrol remaining and we ARE NOT at the buyer - move to the buyer [1]
        } else if ((sellerBuyerPetrol <= b->fuel && startBuyer != 0) || (fuelAmount == 0 && startBuyer != 0)) {
            *n = startBuyer;
            *action = ACTION_MOVE;
            //Ensure we can only move the maximum move
            if (*n >= 0) {
                if (*n >= b->maximum_move) {
                    *n = b->maximum_move;
                }
            } else if (*n < 0) {
                if (*n <= -1 * b->maximum_move) {
                    *n = -1 * b->maximum_move;
                }
            }
        //If the distance to the buyer + the nearest petrol from buyer is LESS than the amount of petrol remaining and we ARE at the buyer - sell commodities [3]
        } else if (startBuyer == 0) {
            *n = b->cargo->quantity;
            *action = ACTION_SELL;            
        }    
    } else {
        *n = 0;
        *action = ACTION_MOVE;
    }
}

char *get_bot_name(void) {
    return "Yaoi";
}


