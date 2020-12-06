#ifndef UIElements_H
#define UIElements_H

#include "UIEngine.h"
#include "GameState.h"
// #include "constants.h"

// global pointer to state of current game
GameState* G = new GameState(0);

// global root element
UIElement* Screen = new UIElement;

// global pointers to other elements
// menu pages
UIElement* MainMenu;
UIElement* CreditsPage;
UIElement* StatisticsPage;
UIElement* InstructionsPage;

// game pages
UIElement* DifficultySelection;
UIElement* GameMenu;

// sub-panels for game menu
UIElement* TopBar;
UIElement* HomePanel;
UIElement* PlotsPanel;

// transition screen between in-game days
UIElement* DayTransitionScreen;

// individual plot elements shown in plots panel
RectangleElement* PlotElements[NUMBER_OF_PLOTS];

// keep track of currently-displayed menu page
UIElement* CurrentPage;

// keep track of currently-displayed in-game menu panel
UIElement* CurrentGamePanel;

// prototypes for element intialization functions
// backgrounds
UIElement* getBackground1();
UIElement* getBackground2();

// helpers for standard menu elements
RectangleElement* getStandardTitle(int x, int y, int w, stringT label);
RectangleElement* getStandardButton(int x, int y, int w, stringT label, void (*handler)());

// menu pages
UIElement* getMainMenu();
UIElement* getCreditsPage();
UIElement* getStatisticsPage();
UIElement* getInstructionsPage();

// game pages
UIElement* getDifficultySelection();
UIElement* getGameMenu();

// sub-panels for game menu
UIElement* getTopBar();
UIElement* getHomePanel();
UIElement* getPlotsPanel();

// transition screen between in-game days
UIElement* getDayTransition();

// individual plot elements in plots panel, rendered based on internal plots array
// these elements will be re-initialized often so this function returns a value 
// instead of a pointer to make memory management easier
RectangleElement getPlotElement(int index);
// helper function to keep plots panel reflective of internal data
void updatePlotElements();

// helper function to initialize game state and display game menu
void playGame(int diff);
// helper function to switch between menu pages
void switchToPage(UIElement* page);
// helper function to switch between in-game UI panels
void switchToPanel(UIElement* panel);

// entity graphics
CircleElement* getCoinSprite(int x, int y);

// function to initialize global element pointers
void initUI() {
    MainMenu = getMainMenu();
    CreditsPage = getCreditsPage();
    InstructionsPage = getInstructionsPage();
    StatisticsPage = getStatisticsPage();

    DifficultySelection = getDifficultySelection();

    TopBar = getTopBar();
    HomePanel = getHomePanel();
    PlotsPanel = getPlotsPanel();
    DayTransitionScreen = getDayTransition();
    GameMenu = getGameMenu();

    CurrentPage = nullptr;
    CurrentGamePanel = new UIElement;
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
        // on click: go to difficulty selection
        switchToPage(DifficultySelection);
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
// difficulty selection
UIElement* getDifficultySelection() {
    // initialize element pointer
    UIElement* difficultySelection = new UIElement;

    // set background
    difficultySelection->addChild(getBackground1());

    // add title text
    difficultySelection->addChild(getStandardTitle(20, 20, 280, "Select a Difficulty Level"));

    // add buttons
    RectangleElement* normalModeButton = getStandardButton(20, 90, 280, "Normal Mode", [] {
        // on click: set game difficulty to normal mode, start game
        playGame(0);
    });
    normalModeButton->setColor(LCD.Black);
    difficultySelection->addChild(normalModeButton);

    RectangleElement* chaosModeButton = getStandardButton(20, 130, 280, "Chaos Mode", [] {
        // on click: set game difficulty to chaos mode, start game
        playGame(1);
    });
    chaosModeButton->setColor(LCD.Black);
    difficultySelection->addChild(chaosModeButton);

    difficultySelection->addChild(getStandardButton(20, 190, 120, "Return", [] {
        // on click: return to main menu
        switchToPage(MainMenu);
    }));

    // return element pointer
    return difficultySelection;
}
// game menu
UIElement* getGameMenu() {
    // initialize element pointer
    UIElement* gameMenu = new UIElement;

    /*
    //GameState g;
    stringT test = G->test();
    // add placeholder text
    gameMenu->addChild(new StringElement(100, 100, test, LCD.White));
    */

    // add background
    gameMenu->addChild(getBackground2());

    // add top bar
    gameMenu->addChild(TopBar);

    // body panel gets added/removed during game

    // return element pointer
    return gameMenu;
}
// game menu elements
// top bar
UIElement* getTopBar() {
    // initialize element pointer
    UIElement* topBar = new UIElement;

    // add bar
    topBar->addChild(new RectangleElement(0, 0, 320, 40, LCD.Black));

    // add tracker for current day
    topBar->addChild(new StringElement(15, 15, "Day", LCD.White));
    topBar->addChild(new ValueElement(50, 15, [] {
        return G->curr_day;
    }, LCD.White));

    // add tracker for money
    topBar->addChild(getCoinSprite(80, 13));
    topBar->addChild(new ValueElement(100, 15, [] {
        return G->coins;
    }, LCD.White));

    // add end day button
    topBar->addChild(getStandardButton(170, 5, 75, "End Day", [] {
        // on click: start procedure for moving to next day
        G->new_day();
        switchToPage(DayTransitionScreen);
    }));

    // add quit button
    topBar->addChild(getStandardButton(255, 5, 50, "Quit", [] {
        // on click: return to main menu
        switchToPage(MainMenu);
    }));

    // return element pointer
    return topBar;
}
// home panel
UIElement* getHomePanel() {
    // initialize element pointer
    UIElement* homePanel = new UIElement;

    // add listings for each crop type

    // add button to go to plots
    homePanel->addChild(getStandardButton(205, 50, 100, "View Plots", [] {
        // on click: switch from home panel to plots panel
        switchToPanel(PlotsPanel);
    }));

    // return element pointer
    return homePanel;
}
// plots panel
UIElement* getPlotsPanel() {
    // initialize element pointer
    UIElement* plotsPanel = new UIElement;

    // add pointers to individual plot elements

    // add button to return to home panel
    plotsPanel->addChild(getStandardButton(205, 50, 100, "Return", [] {
        // on click: switch from plots panel to home panel
        switchToPanel(HomePanel);
    }));

    // return element pointer
    return plotsPanel;
}
// individual plots
RectangleElement getPlotElement(int index) {
    // get size and dimensions
    int plotWidth = 45;
    int plotHeight = plotWidth;
    int plotX = 20 + (50 * (index % 4));
    int plotY = 50 + (50 * (index / 4));

    // initialize element pointer
    RectangleElement plotElement = RectangleElement(plotX, plotY, plotWidth, plotHeight);

    // show indicator for crop type

    // show indicator for remaining days

    // return element pointer
    return plotElement;
}
// re-initialize plot elements to account for changes in internal data
void updatePlots() {
    //
}
// transition screen
UIElement* getDayTransition() {
    // intialize element pointer
    UIElement* transitionScreen = new UIElement;

    // black background covering entire screen
    RectangleElement* bg = new RectangleElement(0, 0, 320, 240, LCD.Black);
    // exit transition screen and start new day when background clicked
    bg->setClickHandler([] {
        switchToPage(GameMenu);
    });
    transitionScreen->addChild(bg);

    // on-screen text
    transitionScreen->addChild(new StringElement(100, 100, "Start of Day", LCD.White));
    transitionScreen->addChild(new ValueElement(195, 101, [] {
        return G->curr_day;
    }, LCD.White));
    transitionScreen->addChild(new StringElement(50, 120, "Click Anywhere to Continue", LCD.White));

    // return element pointer
    return transitionScreen;
}

// graphical representation of in-game currency
CircleElement* getCoinSprite(int x, int y) {
    // draw white circle with gray 'c' in the middle, resembling a silver coin
    // why not a gold coin? because I'm too lazy to use the expanded color selection
    int radius = 8;

    // x and y refer to top left corner, not center of circle
    CircleElement* coinSprite = new CircleElement(x+radius, y+radius, radius, LCD.White, LCD.Gray);
    coinSprite->addChild(new StringElement(x+3, y+3, "c", LCD.Gray));

    return coinSprite;
}

// switch between pages
void switchToPage(UIElement* page) {
    if (CurrentPage) Screen->removeChild(CurrentPage);
    Screen->addChild(page);
    CurrentPage = page;
}

// switch between in-game menu panels
void switchToPanel(UIElement* panel) {
    GameMenu->addChild(panel);
    if (CurrentGamePanel) GameMenu->removeChild(CurrentGamePanel);
    CurrentGamePanel = panel;
}

void playGame(int diff) {
    // initialize game state
    *G = GameState(diff);

    switchToPage(GameMenu); // go to game menu
    switchToPanel(HomePanel); 
}

#endif // UIElements_H