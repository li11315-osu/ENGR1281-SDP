#ifndef GAMESTATE
#define GAMESTATE

#include <iostream>
#include "GameState.h"

#define NUMBER_OF_CROPS 12
#define NUMBER_OF_EVENTS 5
#define START_COINS 500

const crop_type empty = {.name = "empty", .crop_id = 0};
const crop_type carrot = {.name = "Carrot", .grow_time = 4, .crop_id = 1, .sale_price = 100, .seed_price = 20};

char* GameState::test() {
   return "THIS IS A TEST";
}

// WIP
GameState::GameState(int diff){

    // Initialize state variables
    difficulty = diff;
    coins = START_COINS;
    curr_day = 1;

    // Set all of the plots to an empty
    for(int i = 0; i < NUMBER_OF_CROPS; i++){
        plots[i] = {.type = empty, .active = false};
    }

    // Initiate the events
}

#endif //GameState