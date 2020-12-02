#ifndef UIElements_H
#define UIElements_H

#include "UIEngine.h"
#include "constants.h"

// global root element
UIElement* Screen = new UIElement;

// global pointers to other elements
UIElement* MainMenu;
UIElement* CreditsPage;
UIElement* StatisticsPage;
UIElement* InstructionsPage;

UIElement* CurrentPage;

// prototypes for element intialization functions
UIElement* getBackground1();
UIElement* getBackground2();

RectangleElement* getStandardTitle(int x, int y, int w, stringT label);
RectangleElement* getStandardButton(int x, int y, int w, stringT label, void (*handler)());

UIElement* getMainMenu();
UIElement* getCreditsPage();
UIElement* getStatisticsPage();
UIElement* getInstructionsPage();

void playGame();
void switchToPage(UIElement* page);

// function to initialize global element pointers
void initUI() {
    MainMenu = getMainMenu();
    CreditsPage = getCreditsPage();
    InstructionsPage = getInstructionsPage();
    StatisticsPage = getStatisticsPage();

    CurrentPage = nullptr;
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

UIElement* getBackground2() {
    UIElement* bg = new UIElement;
    // make background green to represent grass 
    bg->addChild(new RectangleElement(0, 0, 320, 120, LCD.Green));
    bg->addChild(new RectangleElement(0, 120, 320, 120, LCD.Green));
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
    mainMenu->addChild(getStandardTitle(20, 20, 190, "Meadow Valley"));

    // add start button
    mainMenu->addChild(getStandardButton(20, 75, 120, "Start", [] {
        // on click: start game
        playGame();
    }));

    // add instructions button
    mainMenu->addChild(getStandardButton(20, 113, 120, "Instructions", [] {
        // on click: switch to instructions page
        switchToPage(InstructionsPage);
    }));

    // add statistics button
    mainMenu->addChild(getStandardButton(20, 151, 120, "Statistics", [] {
        // on click: switch to statistics page
        switchToPage(StatisticsPage);
    }));

    // add credits button
    mainMenu->addChild(getStandardButton(20, 189, 120, "Credits", [] {
        // on click: switch to credits page
        switchToPage(CreditsPage);
    }));

    // return the menu element pointer
    return mainMenu;
}
// credits page
UIElement* getCreditsPage() {
    // create pointer to element container
    UIElement* creditsPage = new UIElement;

    // add background
    creditsPage->addChild(getBackground1());

    // add title element
    creditsPage->addChild(getStandardTitle(20, 20, 280, "Credits"));

    // add body
    creditsPage->addChild(new RectangleElement(20, 73, 280, 110, LCD.Black));
    creditsPage->addChild(new StringElement(30, 85, "Drew Ripberger - ", LCD.White));
    creditsPage->addChild(new StringElement(30, 120, "Annie Getts - ", LCD.White));
    creditsPage->addChild(new StringElement(30, 155, "Thomas Li - ", LCD.White));

    // add return button
    creditsPage->addChild(getStandardButton(20, 190, 120, "Return", [] {
        switchToPage(MainMenu);
    }));

    // return element pointer
    return creditsPage;
}
// instructions page
UIElement* getInstructionsPage() {
    // create element pointer
    UIElement* instructionsPage = new UIElement;

    // add background
    instructionsPage->addChild(getBackground1());

    // add title element
    instructionsPage->addChild(getStandardTitle(20, 20, 280, "Instructions"));

    // add body
    instructionsPage->addChild(new RectangleElement(20, 73, 280, 110, LCD.Black));
    instructionsPage->addChild(new StringElement(30, 85, "Welcome to your farm! Buy &", LCD.White));
    instructionsPage->addChild(new StringElement(30, 102, "plant seeds, watch them grow,", LCD.White));
    instructionsPage->addChild(new StringElement(30, 119, "sell the produce, and repeat!", LCD.White));
    instructionsPage->addChild(new StringElement(30, 136, "Each day brings new twists!", LCD.White));

    // add return button
    instructionsPage->addChild(getStandardButton(20, 190, 120, "Return", [] {
        switchToPage(MainMenu);
    }));

    // return element pointer
    return instructionsPage;
}
// statistics page
UIElement* getStatisticsPage() {
    // create element pointer
    UIElement* statisticsPage = new UIElement;

    // add background
    statisticsPage->addChild(getBackground1());

    // add title element
    statisticsPage->addChild(getStandardTitle(20, 20, 280, "Statistics"));

    // add body
    statisticsPage->addChild(new RectangleElement(20, 73, 280, 110, LCD.Black));

    statisticsPage->addChild(new StringElement(30, 85, "Max Days Survived: ", LCD.White));
    statisticsPage->addChild(new ValueElement(220, 85, [] {
        return 0;
    }, LCD.White));

    statisticsPage->addChild(new StringElement(30, 102, "Total Money Earned: ", LCD.White));
    statisticsPage->addChild(new ValueElement(220, 102, [] {
        return 0;
    }, LCD.White));

    statisticsPage->addChild(new StringElement(30, 119, "Total Money Lost: ", LCD.White));
    statisticsPage->addChild(new ValueElement(220, 119, [] {
        return 0;
    }, LCD.White));

    statisticsPage->addChild(new StringElement(30, 136, "Carrots Planted: ", LCD.White));
    statisticsPage->addChild(new ValueElement(220, 136, [] {
        return 0;
    }, LCD.White));

    statisticsPage->addChild(new StringElement(30, 153, "Carrots Harvested: ", LCD.White));
    statisticsPage->addChild(new ValueElement(220, 153, [] {
        return 0;
    }, LCD.White));

    // add return button
    statisticsPage->addChild(getStandardButton(20, 190, 120, "Return", [] {
        switchToPage(MainMenu);
    }));

    // return element pointer
    return statisticsPage;
}

// switch between pages
void switchToPage(UIElement* page) {
    if (CurrentPage) Screen->removeChild(CurrentPage);
    Screen->addChild(page);
    CurrentPage = page;
}

void playGame() {
    UIElement* placeholder = new UIElement;
    placeholder->addChild(new StringElement(100, 100, "Play Game Here", LCD.White));
    placeholder->addChild(getStandardButton(20, 190, 120, "Return", [] {
        switchToPage(MainMenu);
    }));
    switchToPage(placeholder);
}

#endif // UIElements_H