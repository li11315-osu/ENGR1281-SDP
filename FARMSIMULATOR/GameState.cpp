#ifndef GAMESTATE
#define GAMESTATE

#include <iostream>
#include <vector>

#include "GameState.h"
#include "FEHRandom.h"

// Inital constants and setup by Drew
#define NUMBER_OF_PLOTS 12
#define START_COINS 500
//All "chaos mode" additions made by Annie
#define CHAOS_START_COINS 400

// Written by Drew
// Simple text function that returns "Hello, World"
// as a C string. Used to test calling GameState functions
// from the UI
char* GameState::test() {
   return "Hello, World!";
}

// Written by Drew
// Constructor
// Sets of the plots to empty, the events to inactive
// and resets the local game stats.
GameState::GameState(int diff){

    // Initialize state variables
    difficulty = diff;
    coins = START_COINS;
    curr_day = 1;
    total_stats = stats{0, 0, 0, 0};

    //Check if player selected chaos mode
    if (difficulty == 1) {
       //Initialize chaos starting coin amount
       coins = CHAOS_START_COINS;
       //Loop through all of the possible events
       for (int i = 0; i < 10; i++) {
          //If the event is bad, double the monetary damage of it
          if (events[i].isPenalty) {
             events[i].moneyAmount *= 2;
          //If the event is good, halve the monetary benefit of it
          } else {
             events[i].moneyAmount /= 2;
          }
       }
    }

    // Set all boolean variables keeping track of what event has occurred
    // that day to false
    for(int i = 0; i < 10; i++) {
       event_occurred[i] = false;
    }

    // Set all of the plots to an empty
    for(int i = 0; i < NUMBER_OF_PLOTS; i++){
        plots[i] = plot{empty, false, 0};
    }

}

// Written by Drew
// begin_event generates a random event and applies
// the consequences to the farm
void GameState::begin_event(){
    // Generating random number [0, number of events]
    int pick1 = RandInt() % (int)(sizeof(events)/sizeof(events[0]));
    //Generate second random number in the case of chaos mode
    int pick2 = RandInt() % (int)(sizeof(events)/sizeof(events[0]));

    event rand_event = events[pick1];
    event_occurred[pick1] = true;

    // Deciding whether to add money or subtract it
    if(rand_event.isPenalty){
        coins -= rand_event.moneyAmount;
        //Update game statistic of total money lost
        total_stats.total_money_lost += rand_event.moneyAmount;
        //Set the coins to 0 if they are a negative value
        if (coins < 0) {
           coins = 0;
        }
    } else {
        coins += rand_event.moneyAmount;
        //Update game statistic of total money earned
        total_stats.total_money_earned += rand_event.moneyAmount;
    }

    wipeout(rand_event.wipeout_list);

   //If in chaos mode, generate a second random event (could be a repeat)
    if (difficulty == 1) {
       event rand_event2 = events[pick2];
      event_occurred[pick2] = true;

      // Deciding whether to add money or subtract it
      if(rand_event2.isPenalty){
        coins -= rand_event2.moneyAmount;
        //Update game statistic of total money lost
        total_stats.total_money_lost += rand_event2.moneyAmount;
        //Set the coins to 0 if they are a negative value
        if (coins < 0) {
           coins = 0;
         }
      } else {
         coins += rand_event2.moneyAmount;
         //Update game statistic of total money earned
         total_stats.total_money_earned += rand_event2.moneyAmount;
      }

    wipeout(rand_event2.wipeout_list);
    }
}

// Written by Drew
// wipeout takes a vector of indices and destroys the
// corresponding crops
void GameState::wipeout(std::vector<int> wl){
    for(int i = 0; i < wl.size(); i++){
        plots[wl.at(i)] = plot_raw{empty, false, 0};
    }
}

//Written by Annie
//This function takes the selected plot and selected crop type as input arguments.
//The return type is void.
//It checks the input crop type to make sure the user can afford the plant they 
//are trying to buy, and if so purchases the seed and updates the state of the
//plot that the user was trying to plant the crop on.
void GameState::plant(plot *p, crop_type *c) {
   //Check to make sure the user can afford the seeds
   if ((*c).seed_price < coins) {
      //Subtract the cost of the seeds from the user's total money
      coins -= (*c).seed_price;
      //Update game statistic of total money lost
      total_stats.total_money_lost += ((*c).seed_price + (*c).seed_price);
      //Update the state of the selected plot
      (*p).active = true;
      (*p).days_active = 0;
      (*p).type = (*c);
      //Check if planted crop was a carrot
      if ((*c).crop_id == 1) {
         //If so, update game statistic of total carrots planted
         total_stats.carrots_planted++;
      }
   }
   //If the user cannot afford the seeds, nothing should happen
}

//Written by Annie
//This function takes the selected plot as an input argument.
//The return type is void.
//It checks if the selected plot is ready to be harvested, and
//if so, it harvests the crop and updates the user stats accordingly.
void GameState::harvest(plot *p) {
   //Make sure the selected plot is ready for harvest
   if ((*p).days_active >= ((*p).type).grow_time) {
      //Add the sale price of the crop to the user's total money
      coins += ((*p).type).sale_price;
      //Update game statistic of total money earned
      total_stats.total_money_earned += ((*p).type).sale_price;
      //Update the state of the selected plot
      (*p).active = false;
      (*p).days_active = 0;
      (*p).type = empty;
   }
   //If the plot is not ready for harvest, nothing should happen
}

//Written by Annie
//This function has no arguments, and its return type is void.
//It makes sure the user still has some amount of money, and
//if so, starts the new day. The new day involves incrementing
//the day counter, incrementing the number of days that each
//active plot has been active, and cue a random event to happen.
void GameState::new_day() {
   //Make sure the user isn't dead yet
   stillAlive = (coins > 0);
   if (stillAlive) {
      //Increment the day counter
      curr_day++;
      //Update game statistic for maximum days survived if applicable
      if (curr_day > total_stats.max_days_survived) {
         total_stats.max_days_survived = curr_day;
      }
      //Loop through each plot, and if the plot has a crop growing on it,
      //increment the number of days the plot has been active
      for (int i = 0; i < NUMBER_OF_PLOTS; i++) {
         if (plots[i].active) {
            (plots[i].days_active)++;
         }
      }
      //Reset all boolean variables keeping track of what event has occurred
      //that day to false
      for(int i = 0; i < 10; i++) {
         event_occurred[i] = false;
      }
      //Cue the random event for the day
      GameState::begin_event();
   }
   //Do not start a new day if the user is broke
}

//Written by Annie
//This function has no arguments and the return type is a stats struct.
//Accessor method so that the game can keep track of statistics from
//multiple playthroughs of the game in one run of the program for
//the statistics page on the main menu.
stats GameState::get_game_stats() {
   return total_stats;
}

#endif //GameState 
