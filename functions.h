//A header file for all the functions used in this assignment
//Written 19 May 2017 (edited daily)
//By Pranav Singh z3461857 
//For COMP1511 Assignment 2

//Finds the most profitable seller in the world
int find_seller (struct bot *b);

//Finds the most profitable buyer (after finding the seller) in the world
int find_buyer (struct bot *b);

//Finds the nearest petrol station to the seller
int check_fuel (struct bot *b);

//Finds the nearest petrol station to the buyer
int check_fuel_buy (struct bot *b);

//Calculates how much of a commodity to buy based on weight, volume and price
int how_much (struct bot *b);

//Finds distance from seller -> nearest petrol station to seller
int seller_petrol (struct bot *b);

//Finds distance from seller -> buyer
int seller_buyer (struct bot *b);

//Finds distance from buyer -> nearest petrol station to buyer
int buyer_petrol (struct bot *b);

//Finds distance from nearest petrol station to seller -> buyer
int petrol_buyer (struct bot *b);

//Finds distance from nearest petrol station to buyer -> seller
int petrol_seller (struct bot *b);

//Calculates how many turns it will take for one full cycle of buying and selling a commodity
int turns_remaining (struct bot *b);

//Calculates total amount of fuel in the world (sum of available fuel at all petrol stations)
int fuel_amount (struct bot *b);

//Calculates the amount of locations in the world
int world_count (struct bot *b);

//Finds average petrol price in the world
int petrol_price (struct bot *b);

//Calculates profit whilst accounting for petrol
int petrol_profit (struct bot *b);
