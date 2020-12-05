#ifndef GAMESTATE
#define GAMESTATE

#include <iostream>
#include <vector>

#include "GameState.h"
#include "FEHRandom.h"

#define NUMBER_OF_PLOTS 12
#define START_COINS 500

char* GameState::test() {
   return "Hello, World!";
}

//Written by Drew
GameState::GameState(int diff){

    // Initialize state variables
    difficulty = diff;
    coins = START_COINS;
    curr_day = 0;

    // Set all of the plots to an empty
    for(int i = 0; i < NUMBER_OF_PLOTS; i++){
        plots[i] = plot{empty, false, 0};
    }

}

//Written by Drew
void GameState::begin_event(){
    // Generating random number [0, number of events]
    int pick = RandInt() % (int)(sizeof(events)/sizeof(events[0]));

    event rand_event = events[pick];

    // Deciding whether to add money or subtract it
    if(rand_event.isPenalty){
        coins -= rand_event.moneyAmount;
        if (coins < 0) {
           coins = 0;
        }
    } else {
        coins += rand_event.moneyAmount;
    }

    wipeout(rand_event.wipeout_list);
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
      //Update the state of the selected plot
      (*p).active = true;
      (*p).days_active = 0;
      (*p).type = (*c);
   }
   //If the user cannot afford the seeds, nothing should happen
}

//Written by Annie
void GameState::harvest(plot *p) {
   //Make sure the selected plot is ready for harvest
   if ((*p).days_active >= ((*p).type).grow_time) {
      //Add the sale price of the crop to the user's total money
      coins += ((*p).type).sale_price;
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
      //Cue the random event for the day
      GameState::begin_event();
   }
   //Do not start a new day if the user is broke
}

#endif //GameState
