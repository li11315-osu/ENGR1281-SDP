#ifndef GAMESTATE_H
#define GAMESTATE_H

#define NUMBER_OF_PLOTS 12

#include <vector>
#include <cstring>


// Written by Annie and Drew
// Stores the properties of the events that can occur
// These include the name of the event, a brief description of
// the event, whether or not the event has a negative effect 
// on the user, the change in user's money caused by the event,
// and a list of which plots, if any, should be wiped out as a
// result of the event.
struct event_raw {
    char name[32];

    char desc[256];

    bool isPenalty;
    int moneyAmount;
    std::vector<int> wipeout_list;
} typedef event;

// Written by Annie and Drew
// Stores the properties of the crops that can be planted
// These include the name of the crop, the amount of days
// the crop takes to grow, the crop ID we defined for each
// crop, the sale price of the crop, and the price of the 
// seed of the crop.
struct crop_type_raw {
    char name[32];
    int grow_time;
    int crop_id;
    int sale_price;
    int seed_price;
} typedef crop_type;

// Written by Annie and Drew
// Stores the properties of the plots that will make up the farm
// These include the type of crop on the plot, whether or not
// the plot is active, and how many days the plot has been active.
struct plot_raw {
    crop_type type;
    bool active;
    int days_active;
} typedef plot;

//Written by Annie
// Stores the up to date stats of the game as it is running
// These include the maximum number of days survived by the
// user, the total amount of money the user has earned, the
// total amount of money the user has lost, and the number
// of carrots planted by the user.
struct running_game_stats {
    //Game stats
    int max_days_survived;
    int total_money_earned;
    int total_money_lost;
    int carrots_planted;
} typedef stats;

// Crops by Annie and Drew
// Different crop types, including a "null" crop
const crop_type empty = crop_type{"empty", 0, 0, 0, 0}; //Crop ID = 0
const crop_type carrot = crop_type{"Carrot", 2, 1, 100, 20}; //Crop ID = 1
const crop_type tomato = crop_type{"Tomato", 4, 2, 250, 40}; //Crop ID = 2
const crop_type corn = crop_type{"Corn", 3, 3, 170, 30}; //Crop ID = 3
const crop_type lettuce = crop_type{"Lettuce", 5, 4, 300, 60}; //Crop ID = 4

// Events by Annie and Drew
// Different random events, one occurs each day
const event flood = event{"Flood", "A destructive flash flood!", true, 10, std::vector<int>{0, 1, 2, 3}};
const event tornado = event{"Tornado", "TORNADO! All of your crops are gone", true, 50, std::vector<int>{0,1,2,3,4,5,6,7,8,9,10,11}};
const event fire = event{"Fire", "A part of the field caught fire!", true, 20, std::vector<int>{8,9,10,11}};
const event sunny_day = event{"Sunny day :)", "Blue skies and sunshine!", false, 40, std::vector<int>{}};
const event thief = event{"Thief!", "Someone broke in! What'd they take?", true, 100, std::vector<int>{4, 5, 6, 7}};
const event rain = event{"Rain :)", "The crops are loving the water!", false, 50, std::vector<int>{}};
const event bug = event{"Monster bug!", "A giant bug has stomped around!", true, 70, std::vector<int>{6, 7, 8, 9, 10, 11}};
const event fertilizer = event{"Free fertilizer!", "Gift from the neighbors!", false, 50, std::vector<int>{}};
const event pandemic = event{"Cornona Virus :O", "A deadly plant virus!!!", true, 60, std::vector<int>{0, 1, 2, 3, 4, 5}};
const event mystery = event{"Where'd they go?", "It's a mystery event!", true, 70, std::vector<int>{3, 4, 5, 6, 7, 8}};

// Written by Drew and Annie
// Represents the current state of the farm.
// This includes the amount of money you have
// and what crops you have planted.
// This also includes the selected difficulty for the game, the possible events
// that can occur in the game, an array of boolean values storing whether or not 
// each event occurs each day, the number of the day you are on, the methods all
// defined and described in GameState.cpp, and the running game stats described 
// in the stat struct definition.
class GameState {
    public:

        //Difficulty setting
        int difficulty;

        // The plots on the screen that can grow crops
        plot plots[NUMBER_OF_PLOTS];

        // The random events that can occur in between days
        event events[10] = {flood, tornado, fire, sunny_day, thief, rain, bug, fertilizer, pandemic, mystery};
        bool event_occurred[10];

        //Misc. game stats
        int coins;
        int curr_day;
        bool stillAlive;

        // Drew
        char* test();

        //Constructor

        // Drew
        GameState(int);
        
        // For description of each method see GameState.cpp

        // Methods in GameState class
        // Annie
        void plant(plot*, crop_type*);
        // Annie
        void new_day();
        // Drew
        void begin_event();
        // Annie
        void harvest(plot*);
        // Drew
        void wipeout(std::vector<int>);
        // Annie
        stats get_game_stats();

    private:
        stats total_stats;
};
#endif // GameState_H 
