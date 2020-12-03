#include "FEHLCD.h"
#include "UIElements.h"
//#include "GameState.h"

/**
 * Entry point to the application
 * 
 * @returns status code of program exit
 */
int main() {

    // keep track of touch coordinates
    int x, y;

    // initialize UI elements
    initUI();
    // add main menu to screen
    switchToPage(MainMenu);
    // render screen
    LCD.Clear();
    Screen->render();

    // start program loop
    while (1) {
        // wait for touch
        while (!LCD.Touch(&x, &y)) {}

        // respond to touch
        if (Screen->handleClick(x, y)) {
            // clear and re-render screen if needed
            LCD.Clear();
            Screen->render();
        }
    }
    return 0;
}