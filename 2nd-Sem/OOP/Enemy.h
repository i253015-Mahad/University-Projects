#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionDetector.h"
#include "Platform.h"
using namespace sf;
using namespace std;

const int ENEMY_STATE_WALK = 0;
const int ENEMY_STATE_PARTIAL_COAT = 1;
const int ENEMY_STATE_FULL_COAT = 2;
const int ENEMY_STATE_ESCAPING = 3;
const int ENEMY_STATE_ROLLING = 4;
const int ENEMY_STATE_DEAD = 5;
const int MAX_ENEMIES = 20;

struct EnemyFrame {
    int x, y, w, h;
};

struct SnowFrame {
    int x, y, w, h;
};

class Enemy {
public:
    Enemy(float startX, float startY);
    virtual ~Enemy() {}

    virtual void update(float dt,
        Platform* platforms[], int platformCount,
        CollisionDetector& cd) = 0;
    virtual void draw(RenderWindow& window,
        bool showHitBox) = 0;
    virtual void loadTexture(string imagePath) = 0;

    void applySnowHit();
    void startRolling(bool goingRight);
    void killEnemy();
    void incrementChain();
    void resetHitFlag();
    void setHitsToCoat(int hits);
    bool shouldRemove() const;

    bool      isDefeated()    const;
    bool      isFullyCoated() const;
    bool      isRolling()     const;
    int       getState()      const;
    int       getChainCount() const;
    FloatRect getHitBox()     const;

protected:
    float x, y;
    float velocityX, velocityY;
    bool  onGround;
    bool  alive;
    int   state;

    float coatTimer;
    float escapeTimer;
    float rollSpeed;
    int   chainCount;
    float deathTimer;
    int   coatLevel;
    int   hitsToCoat;
    bool  hitThisFrame;

    float shakeTimer;
    float shakeOffset;

    Texture   texture;
    Sprite    sprite;
    FloatRect hitBox;

    Texture snowTexture;
    Sprite  snowSprite;
    int     snowAnimFrame;
    float   snowAnimTimer;

    void applyGravity(float dt);
    void handlePlatformCollision(
        Platform* platforms[], int platformCount,
        CollisionDetector& cd);
    void updateHitBox(float w, float h);
    void drawHitBox(RenderWindow& window);
    void updateSnowAnimation(float dt);
    void drawSnowSprite(RenderWindow& window);
    void updateEscapeLogic(float dt);
    void updateRollingLogic(float dt,
        Platform* platforms[], int platformCount,
        CollisionDetector& cd);
};