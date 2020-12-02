#include "GameState.h"
#include "FEHLCD.h"
#include <iostream>

void GameState::test(){
    LCD.Clear();
    LCD.WriteLine("Hello!");
    std::cout << "GameState class created!" << std::endl;
}