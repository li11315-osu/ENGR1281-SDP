#include "FEHLCD.h"
#include "UIElements.h"

/**
 * Entry point to the application
 * 
 * @returns status code of program exit
 */
int main() {
    // keep track of touch coordinates
    int x, y;
    // add main menu to screen
    Screen->addChild(MainMenu);
    // start program loop
    while (1) {
        // clear and re-render screen
        LCD.Clear();
        Screen->render();

        // wait for touch
        while (!LCD.Touch(&x, &y)) {}

        // respond to touch
        Screen->handleClick(x, y);
    }
    return 0;
}