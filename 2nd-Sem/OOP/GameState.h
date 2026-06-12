#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class InputManager;

class GameState {
public:
    virtual ~GameState() {}

    virtual void handleInput(InputManager& input) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(RenderWindow& window, bool showHitBox) = 0;
};