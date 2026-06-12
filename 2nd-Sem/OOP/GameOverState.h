#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "InputManager.h"
using namespace sf;
using namespace std;

class GameOverState : public GameState {
public:
    GameOverState(RenderWindow& window);

    void handleInput(InputManager& input);
    void update(float dt);
    void draw(RenderWindow& window, bool showHitBox);

private:
    RenderWindow& window;
    Font  font;
    Text  gameOverText;
    Text  promptText;
    float timer;
};
