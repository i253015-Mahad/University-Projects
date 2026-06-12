#include "InputManager.h"

InputManager::InputManager() {
    for (int i = 0; i < ACTION_COUNT; i++) {
        currentState[i] = false;
        prevState[i] = false;
        bindings[i] = Keyboard::Unknown;
    }
}

void InputManager::loadDefaults(Keyboard::Key p1[4], Keyboard::Key p2[4], Keyboard::Key pause) {
    bindings[P1_MOVE_LEFT] = p1[0];
    bindings[P1_MOVE_RIGHT] = p1[1];
    bindings[P1_JUMP] = p1[2];
    bindings[P1_THROW] = p1[3];

    bindings[P2_MOVE_LEFT] = p2[0];
    bindings[P2_MOVE_RIGHT] = p2[1];
    bindings[P2_JUMP] = p2[2];
    bindings[P2_THROW] = p2[3];

    bindings[ACTION_PAUSE] = pause;
    bindings[TOGGLE_HITBOX] = Keyboard::F1;
}

void InputManager::update() {
    for (int i = 0; i < ACTION_COUNT; i++) {
        prevState[i] = currentState[i];
        currentState[i] = Keyboard::isKeyPressed(bindings[i]);
    }
}

bool InputManager::isHeld(int action) const {
    return currentState[action];
}

bool InputManager::isJustPressed(int action) const {
    return currentState[action] && !prevState[action];
}