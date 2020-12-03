#ifndef GAMESTATE_H
#define GAMESTATE_H

#define NUMBER_OF_CROPS 12
#define NUMBER_OF_EVENTS 5

struct event_raw {
    char event_name[32];

    // Will we use this? Maybe. Should we? No.
    char event_desc[64];

    bool isPenalty;
    int moneyAmount;
    int wipeout_list[NUMBER_OF_CROPS];
} typedef event;

struct crop_type_raw {
    char name[32];
    int grow_time;
    int crop_id;
    int sale_price;
    int seed_price;
} typedef crop_type;

struct plot_raw {
    crop_type type;
    bool active;
    int days_active;
} typedef plot;

class GameState{
    public:

        int difficulty;

        // The plots on the screen that can grow crops
        plot plots[NUMBER_OF_CROPS];

        // The random events that can occur in between days
        event events[NUMBER_OF_EVENTS];
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
        void new_event();

        // Annie
        void harvest(plot*);

        // Drew
        void wipeout(int[]);

    private:
};
#endif // GameState_H