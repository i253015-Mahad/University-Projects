#include "GameOverState.h"

GameOverState::GameOverState(RenderWindow& win)
    : window(win) {
    timer = 0;

    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
        font.loadFromFile("assets/Fonts/arial.ttf");

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setStyle(Text::Bold);

    FloatRect b = gameOverText.getLocalBounds();
    gameOverText.setPosition(400 - b.width / 2, 220);

    promptText.setFont(font);
    promptText.setString("Press SPACE to exit");
    promptText.setCharacterSize(28);
    promptText.setFillColor(Color::White);

    FloatRect pb = promptText.getLocalBounds();
    promptText.setPosition(400 - pb.width / 2, 370);
}

void GameOverState::handleInput(InputManager& input) {
    if (input.isJustPressed(P1_THROW) ||
        input.isJustPressed(P2_THROW))
        window.close();
}

void GameOverState::update(float dt) {
    timer += dt;
}

void GameOverState::draw(RenderWindow& win, bool showHitBox) {
    win.clear(Color::Black);
    win.draw(gameOverText);


    if ((int)(timer / 0.5f) % 2 == 0)
        win.draw(promptText);
}