#include "UIEngine.h"
#include "constants.h"

// global root element
UIElement* Screen = new UIElement;

// main menu
UIElement* getMainMenu() {
    // create a pointer to the main menu container element
    UIElement* mainMenu = new UIElement;

    // add a nice background image to the main menu
    UIElement* bg = new UIElement;
    bg->addChild(new RectangleElement(0, 0, 320, 120, LCD.Blue, LCD.Blue));
    bg->addChild(new RectangleElement(0, 120, 320, 120, LCD.Green, LCD.Green));
    bg->addChild(new RectangleElement(200, 140, 80, 40, LCD.Red, LCD.Red));
    bg->addChild(new RectangleElement(240, 100, 40, 40, LCD.Black, LCD.Black));
    bg->addChild(new RectangleElement(246, 106, 28, 28, LCD.White, LCD.White));
    bg->addChild(new RectangleElement(200, 150, 10, 20, LCD.Gray, LCD.Gray));
    bg->addChild(new CircleElement(205, 180, 20, LCD.Black, LCD.Black));
    bg->addChild(new CircleElement(270, 175, 25, LCD.Black, LCD.Black));
    bg->addChild(new CircleElement(205, 180, 8, LCD.Gray, LCD.Gray));
    bg->addChild(new CircleElement(270, 175, 10, LCD.Gray, LCD.Gray));
    mainMenu->addChild(bg);

    // add title to menu
    RectangleElement* titleContainer = new RectangleElement(20, 20, 215, 44);
    titleContainer->addChild(new StringElement(35, 35, "FARM SIMULATOR"));
    titleContainer->addChild(new StringElement(183, 35, "2020", LCD.Red));
    mainMenu->addChild(titleContainer);

    // return the menu element pointer
    return mainMenu;
}
UIElement* MainMenu = getMainMenu();