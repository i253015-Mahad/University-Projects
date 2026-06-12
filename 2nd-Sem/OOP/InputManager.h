#pragma once
#include <SFML/Window.hpp>
using namespace sf;



const int P1_MOVE_LEFT = 0;
const int P1_MOVE_RIGHT = 1;
const int P1_JUMP = 2;
const int P1_THROW = 3;
const int P2_MOVE_LEFT = 4;
const int P2_MOVE_RIGHT = 5;
const int P2_JUMP = 6;
const int P2_THROW = 7;
const int ACTION_PAUSE = 8;
const int TOGGLE_HITBOX = 9;
const int ACTION_COUNT = 10;  

class InputManager {
public:
    InputManager();
    void loadDefaults(Keyboard::Key p1[4], Keyboard::Key p2[4], Keyboard::Key pause);
    bool isHeld(int action) const;
    bool isJustPressed(int action) const;
    void update();

private:
    Keyboard::Key bindings[ACTION_COUNT];
    bool currentState[ACTION_COUNT];
    bool prevState[ACTION_COUNT];
};