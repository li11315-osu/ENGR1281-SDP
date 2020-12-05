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

GameState::GameState(int diff){

    // Initialize state variables
    difficulty = diff;
    coins = START_COINS;
    curr_day = 1;

    // Set all of the plots to an empty
    for(int i = 0; i < NUMBER_OF_PLOTS; i++){
        plots[i] = plot{empty, false, 0};
    }

}

void GameState::begin_event(){
    // Generating random number [0, number of events]
    int pick = RandInt() % (int)(sizeof(events)/sizeof(events[0]));

    event rand_event = events[pick];

    // Deciding whether to add money or subtract it
    if(rand_event.isPenalty){
        coins -= rand_event.moneyAmount;
    } else {
        coins += rand_event.moneyAmount;
    }

    wipeout(rand_event.wipeout_list);
}

void GameState::wipeout(std::vector<int> wl){
    for(int i = 0; i < wl.size(); i++){
        plots[wl.at(i)] = plot_raw{empty, false, 0};
    }
    
}

#endif //GameState