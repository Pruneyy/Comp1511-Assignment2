//A program that ATTEMPTS to calculate the total moves required from start to finish for one iteration of buying and selling commodities
//Written at 3am one day in a state of disarray fuelled by 2 V's, a Mother and about 3L of coke
//By Pranav Singh z3461857 
//For COMP1511 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "trader_bot.h"
#include "functions.h"

//Condition 1: start->seller->petrol->buyer
//Condition 2: start->seller->buyer->petrol
//Condition 3: start->seller->buyer
//Condition 4: start->petrol->seller->petrol->buyer->petrol

/*

PSA:        I'M 99% SURE THIS CODE DOESN'T WORK, PLEASE DISREGARD - ONLY KEPT BECAUSE OF THAT 1% UNCERTAINTY
            (I was tired and thought it would be a good idea and now I don't even know what's happening here)

*/

int turns_remaining (struct bot *b) {

    struct location  *cur = b->location;    //Current location

    int startSellerPetrol = 0;              //Start->seller->petrol
    int startSeller = 0;                    //Start->seller
    int startPetrol = 0;                    //Start->petrol
    int sellerPetrol = 0;                   //Seller->petrol
    int sellerBuyer = 0;                    //Seller->buyer
    int petrolBuyer = 0;                    //Petrol->buyer
    int sellerBuyerPetrol = 0;              //Seller->buyer->petrol
    int petrolSeller = 0;                   //Petrol->seller

    int rstartSellerPetrol = 0;             //Same as above but with an 'r'?            
    int rstartSeller = 0;                   //Same as above but with an 'r'?           
    int rstartPetrol = 0;                   //Same as above but with an 'r'?
    int rsellerPetrol = 0;                  //Same as above but with an 'r'?
    int rsellerBuyer = 0;                   //Same as above but with an 'r'?
    int rpetrolBuyer = 0;                   //Same as above but with an 'r'?
    int rsellerBuyerPetrol = 0;             //Same as above but with an 'r'?
    int rpetrolSeller = 0;                  //Same as above but with an 'r'? (Yes I just copied + pasted these comments, idk what these variables are for)

    int max_moves = b->maximum_move;        //Max moves as given in trader_bot.h file

    int moves = 0;                          //Counter for moves
    int actions = 0;                        //Counter for actions
    int fuel_rem = 0;                       //Fuel remaining in the bot
    int total_actions = 0;                  //Total actions (moves + actions)

    //Assigining variables to respective functions
    startSellerPetrol = check_fuel(b);              //Start->seller->petrol
    startSeller = abs(find_seller(b));              //Start->seller
    startPetrol = abs(nearest_fuel(b));             //Start->petrol
    sellerPetrol = abs(seller_petrol(b));           //Seller->petrol
    sellerBuyer = abs(seller_buyer(b));             //Seller->buyer
    petrolBuyer = abs(petrol_buyer(b));             //Petrol->buyer
    sellerBuyerPetrol = check_fuel_buy(b);          //Seller->buyer->petrol
    petrolSeller = abs(petrol_seller(b));           //Petrol->seller

    //Like don't even ask man, it looks like I' trying to convert to a double then divide and take the ceiling? Who even knows
    rstartSellerPetrol = ceil(1.0 * startSellerPetrol / max_moves);
    rstartSeller = ceil(1.0 * startSeller / max_moves);
    rstartPetrol = ceil(1.0 * startPetrol / max_moves);
    rsellerPetrol = ceil(1.0 * sellerPetrol / max_moves);
    rsellerBuyer = ceil(1.0 * sellerBuyer / max_moves);
    rpetrolBuyer = ceil(1.0 * petrolBuyer / max_moves);
    rsellerBuyerPetrol = ceil(1.0 * sellerBuyerPetrol / max_moves);
    rpetrolSeller = ceil(1.0 * petrolSeller / max_moves);

    //Fuel remaining, simple enough
    fuel_rem = b->fuel - startSeller; 

    //A piss poor attempt to count the actions necessary for each case listed way up above (below the #includes)
    if (startSellerPetrol > b->fuel) {
        if ((sellerBuyerPetrol) > (b->fuel_tank_capacity - petrolSeller)) {
            moves = rstartPetrol + rpetrolSeller + rsellerPetrol + rpetrolBuyer;
            //Actions are based of counting things in my head, like: buy from petrol + buy from seller + buy from petrol + sell to buyer = 1 + 1 + 1 + 1
            actions = 1 + 1 + 1 + 1;
        } else {
            moves = rstartPetrol + rpetrolSeller + rsellerBuyer;
            actions = 1 + 1 + 1;
        }
    } else if (startSellerPetrol <= b->fuel) {
        if ((sellerBuyerPetrol) > (b->fuel_tank_capacity - startSeller)) {
            moves = rstartSeller + rsellerPetrol + rpetrolBuyer;
            actions = 1 + 1 + 1;
        } else {
            moves = rstartSeller + rsellerBuyer;
            actions = 1 + 1;
        }
    }

    //I have no defence for this coding, it is disgraceful - but cmon, it was a good plan (I think)
    total_actions = moves + actions;

    return total_actions;
}

