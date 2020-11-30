#include "UIEngine.h"
#include "constants.h"

// global root element
UIElement* Screen = new UIElement;

// global pointers to other elements
UIElement* MainMenu;
UIElement* CreditsPage;

// prototypes for element intialization functions
UIElement* getBackground1();

RectangleElement* getStandardTitle(int x, int y, int w, stringT label);
RectangleElement* getStandardBody(int x, int y, int w, int h, stringT message);
RectangleElement* getStandardButton(int x, int y, int w, stringT label, void (*handler)());

UIElement* getMainMenu();
UIElement* getCreditsPage();

// function to initialize global element pointers
void initUI() {
    MainMenu = getMainMenu();
    CreditsPage= getCreditsPage();
}

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

// standard UI text elements
// title
RectangleElement* getStandardTitle(int x, int y, int w, stringT label) {
    // set standard element parameters
    int h = 44; // title assumed to contain single row of text
    int padding = 15; // pixels between shape border and text
    colorT panelColor = LCD.Scarlet;
    colorT textColor = LCD.White;

    // create element pointer
    RectangleElement* titleElement = new RectangleElement(x, y, w, h, panelColor);
    // add label
    titleElement->addChild(new StringElement(x+padding, y+padding, label, textColor));

    // return element pointer
    return titleElement;
}
// body text
RectangleElement* getStandardTitle(int x, int y, int w, int h, stringT message) {
    // set standard element parameters
    int padding = 15; // pixels between shape border and text
    colorT panelColor = LCD.Black;
    colorT textColor = LCD.White;

    // create element pointer
    RectangleElement* bodyElement = new RectangleElement(x, y, w, h, panelColor);
    // add body text
    bodyElement->addChild(new StringElement(x+padding, y+padding, message, textColor));

    // return element pointer
    return bodyElement;
}
// button
RectangleElement* getStandardButton(int x, int y, int w, stringT label, void (*handler)()) {
    // set standard element parameters
    int h = 30; // title assumed to contain single row of text
    int padding = 8; // pixels between shape border and text
    colorT panelColor = LCD.Gray;
    colorT textColor = LCD.White;

    // create element pointer
    RectangleElement* buttonElement = new RectangleElement(x, y, w, h, panelColor);
    // add label
    buttonElement->addChild(new StringElement(x+padding, y+padding, label, textColor));
    // add click handler
    buttonElement->setClickHandler(handler);

    // return element pointer
    return buttonElement;
}

// main menu
UIElement* getMainMenu() {
    // create a pointer to the main menu container element
    UIElement* mainMenu = new UIElement;

    // add a nice background image to the main menu
    mainMenu->addChild(getBackground1());

    // add title panel to menu
    mainMenu->addChild(getStandardTitle(20, 20, 190, "Farm Simulator 2020"));

    // add start button
    mainMenu->addChild(getStandardButton(20, 75, 120, "Start", [] {}));

    // add instructions button
    mainMenu->addChild(getStandardButton(20, 113, 120, "Instructions", [] {}));

    // add statistics button
    mainMenu->addChild(getStandardButton(20, 151, 120, "Statistics", [] {}));

    // add credits button
    mainMenu->addChild(getStandardButton(20, 189, 120, "Credits", [] {
        // on click: switch to credits page
        Screen->removeChild(MainMenu);
        Screen->addChild(CreditsPage);
    }));

    // return the menu element pointer
    return mainMenu;
}
// credits page
UIElement* getCreditsPage() {
    // create pointer to element container
    UIElement* creditsPage = new UIElement;

    // add background

    // add title element

    // add body

    // add return button

    // return element pointer
    return creditsPage;
}