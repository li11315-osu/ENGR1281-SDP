#ifndef GAMESTATE_H
#define GAMESTATE_H

#define NUMBER_OF_PLOTS 12

#include <vector>
#include <cstring>

struct event_raw {
    char name[32];

    // Will we use this? Maybe. Should we? No.
    char desc[256];

    bool isPenalty;
    int moneyAmount;
    std::vector<int> wipeout_list;

    /*
    event_raw(char n[32], char d[256], bool isP, int money, std::vector<int> w){
        strcpy(name, n);
        strcpy(desc, d);
        isPenalty = isP;
        moneyAmount = money;
        wipeout_list = w;
    }
    */

} typedef event;

//Written by Drew and Annie
struct crop_type_raw {
    char name[32];
    int grow_time;
    int crop_id;
    int sale_price;
    int seed_price;
    /*
    crop_type_raw(char n[32], int g, int cid, int sale, int seed){
        strcpy(name, n);
        grow_time = g;
        crop_id = cid;
        sale_price = sale;
        seed_price = seed;
    }
    */
} typedef crop_type;

//Written by Drew and Annie
struct plot_raw {
    crop_type type;
    bool active;
    int days_active;
    /*
    plot_raw(crop_type t, bool a, int d){
        type = t;
        active = a;
        days_active = d;
    }
    */
} typedef plot;

//Written by Annie
struct running_game_stats {
    //Game stats
    int max_days_survived;
    int total_money_earned;
    int total_money_lost;
    int carrots_planted;
    /*
    running_game_stats(int days, int earned, int lost, int car) {
        max_days_survived = days;
        total_money_earned = earned;
        total_money_lost = lost;
        carrots_planted = car;
    }
    */
} typedef stats;

//Different crop types, including a "null" crop
const crop_type empty = crop_type{"empty", 0, 0, 0, 0};
const crop_type carrot = crop_type{"Carrot", 2, 1, 100, 20};
const crop_type tomato = crop_type{"Tomato", 4, 2, 250, 40};
const crop_type corn = crop_type{"Corn", 3, 3, 170, 30};
const crop_type lettuce = crop_type{"Lettuce", 5, 4, 300, 60};

//Different random events, one occurs each day
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

//Written by Drew and Annie
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

        char* test();

        //Constructor
        GameState(int);
        
        //Methods in GameState class
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
        //Annie + Drew
        stats get_game_stats();

    private:
        stats total_stats;
};
#endif // GameState_H 
