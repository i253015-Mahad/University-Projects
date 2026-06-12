#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionDetector.h"
#include "Enemy.h"
#include "Platform.h"
#include "Tornado.h"
using namespace sf;

class Snowball {
public:
    Snowball(float startX, float startY, bool goingRight, int ownerPlayer);

    void update(float dt, Enemy* enemies[], int enemyCount,
        Platform* platforms[], int platformCount, CollisionDetector& cd);
    void draw(RenderWindow& window, bool showHitBox);

    bool isActive() const;
    FloatRect getHitBox() const;
    void deactivate();

private:
    float x, y;
    float velocityX;
    float velocityY;
    bool  active;
    int   ownerPlayer;
    float distanceTravelled; 

    CircleShape shape;
    FloatRect   hitBox;

    void handleScreenWrap();
    void updateHitBox();
    void checkEnemyCollision(Enemy* enemies[], int enemyCount,
        CollisionDetector& cd);
};