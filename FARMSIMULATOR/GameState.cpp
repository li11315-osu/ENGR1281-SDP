#ifndef GAMESTATE
#define GAMESTATE

#include <iostream>
#include <vector>

#include "GameState.h"
#include "FEHRandom.h"

#define NUMBER_OF_PLOTS 12
#define START_COINS 500
//All "chaos mode" additions made by Annie
#define CHAOS_START_COINS 400

char* GameState::test() {
   return "Hello, World!";
}

//Written by Drew
GameState::GameState(int diff){

    // Initialize state variables
    difficulty = diff;
    coins = START_COINS;
    curr_day = 1;

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

//Written by Drew
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

//Written by Drew
void GameState::wipeout(std::vector<int> wl){
    for(int i = 0; i < wl.size(); i++){
        plots[wl.at(i)] = plot_raw{empty, false, 0};
    }
    
}

//Written by Annie
void GameState::plant(plot *p, crop_type *c) {
   //Check to make sure the user can afford the seeds
   if ((*c).seed_price < coins) {
      //Subtract the cost of the seeds from the user's total money
      coins -= (*c).seed_price;
      //Update game statistic of total money lost
      total_stats.total_money_lost += (*c).seed_price;
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
stats GameState::get_game_stats() {
   //Accessor method so that the game can keep track of statistics from
   //multiple playthroughs of the game in one run of the program for
   //the statistics page on the main menu
   return total_stats;
}

#endif //GameState 
