#pragma once
#include "Mahad.h";
#include <SFML/Window/Keyboard.hpp>
using namespace sf;

class Database;

void mainMenu();
void newGame();
void levelSelection();


//for settings
void settings();
Keyboard::Key implement(Keyboard::Key x[4], Keyboard::Key y[4], Keyboard::Key p, int get, int num);
bool settingOpen(int i);

//LeaderBoard
void leaderBoard();
void updateLeaderBoard(Database& x);  


