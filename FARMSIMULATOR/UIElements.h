#include "UIEngine.h"
#include "constants.h"

// global root element
UIElement* Screen = new UIElement;

// prototypes for element intialization functions
UIElement* getBackground1();
UIElement* getMainMenu();

// definitions for element intialization functions
// background used for menus
UIElement* getBackground1() {
    UIElement* bg = new UIElement;
    // draw scene involving a tractor on a grassy field under a blue sky
    bg->addChild(new RectangleElement(0, 0, 320, 120, LCD.Blue));
    bg->addChild(new RectangleElement(0, 120, 320, 120, LCD.Green));
    bg->addChild(new RectangleElement(200, 140, 80, 40, LCD.Red));
    bg->addChild(new RectangleElement(240, 100, 40, 40, LCD.Black));
    bg->addChild(new RectangleElement(246, 106, 28, 28, LCD.White));
    bg->addChild(new RectangleElement(200, 150, 10, 20, LCD.Gray));
    bg->addChild(new CircleElement(205, 180, 20, LCD.Black));
    bg->addChild(new CircleElement(270, 175, 25, LCD.Black));
    bg->addChild(new CircleElement(205, 180, 8, LCD.Gray));
    bg->addChild(new CircleElement(270, 175, 10, LCD.Gray));
    return bg;
}
// main menu
UIElement* getMainMenu() {
    // create a pointer to the main menu container element
    UIElement* mainMenu = new UIElement;

    // add a nice background image to the main menu
    mainMenu->addChild(getBackground1());

    // add title to menu
    RectangleElement* titleContainer = new RectangleElement(20, 20, 215, 44);
    titleContainer->addChild(new StringElement(35, 35, "FARM SIMULATOR"));
    titleContainer->addChild(new StringElement(183, 35, "2020", LCD.Red));
    mainMenu->addChild(titleContainer);

    // add start game button

    // add credits button

    // add quit button

    // return the menu element pointer
    return mainMenu;
}
UIElement* MainMenu = getMainMenu();