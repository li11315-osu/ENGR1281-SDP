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


const crop_type empty = crop_type{"empty", 0, 0, 0, 0};
const crop_type carrot = crop_type{"Carrot", 4, 1, 100, 20};
const event flood = event{"Flood", "A flash flood has destroyed some of your crops!", true, 10, std::vector<int>{0, 1, 2, 3}};


class GameState{
    public:

        int difficulty;

        // The plots on the screen that can grow crops
        plot plots[NUMBER_OF_PLOTS];

        // The random events that can occur in between days
        event events[1] = {flood};
        int coins;
        int curr_day;
        bool stillAlive;

        char* test();

        GameState(int);
         
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

    private:
};
#endif // GameState_H