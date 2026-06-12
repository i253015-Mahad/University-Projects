#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "InputManager.h"
#include "Player.h"
#include "Platform.h"
#include "CollisionDetector.h"
#include "Snowball.h"
#include "Enemy.h"
#include "Botom.h"
#include "FlyingFoogaFoog.h"
#include "Tornado.h"
#include "Mogera.h"
#include "Gamakichi.h"
#include "LevelManager.h"
using namespace sf;

const int MAX_SNOWBALLS = 10;

class PlayingState : public GameState {
public:
    PlayingState(RenderWindow& window,
        InputManager& input, int type);
    ~PlayingState();

    void handleInput(InputManager& input);
    void update(float dt);
    void draw(RenderWindow& window, bool showHitBox);

    bool isGameOver() const;

private:
    int playerNumber;
    Player* player1;
    Player* player2;
    Platform* platforms[MAX_PLATFORMS];
    int        platformCount;
    Snowball* snowballs[MAX_SNOWBALLS];
    int        snowballCount;
    Enemy* enemies[MAX_ENEMIES];
    int        enemyCount;
    Mogera* mogera;
    Gamakichi* gamakichi;

    CollisionDetector cd;
    RenderWindow& window;
    InputManager& input;
    bool              showHitBox;
    bool              gameOver;
    bool         levelComplete;

    LevelManager levelManager;  
    void setupLevel();
    void throwSnowball(Player* player, int playerNum);
    void cleanupSnowballs();
    void checkPlayerEnemyCollision();
    void checkRollingEnemyCollision();
    void checkKnifePlayerCollision();
    void updateMogera(float dt);
    void updateGamakichi(float dt);
};