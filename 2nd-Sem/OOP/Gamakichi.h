#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionDetector.h"
#include "Platform.h"
#include "GamakichiBomb.h"
using namespace sf;

const int MAX_GAMA_BOMBS = 15;
const int GAMA_MAX_HEALTH = 30;

class Gamakichi {
public:
    Gamakichi(float startX, float startY);
    ~Gamakichi();

    void loadTexture(string imagePath);
    void update(float dt, Platform* platforms[],
        int platformCount, CollisionDetector& cd);
    void draw(RenderWindow& window, bool showHitBox);

    void      applyHit();
    bool      isDefeated()   const;
    bool      shouldRemove() const;
    FloatRect getHitBox()    const;
    int       getHealth()    const;

    bool checkSnowballHit(FloatRect snowballBox,
        CollisionDetector& cd);
    bool checkBombPlayerHit(FloatRect playerBox,
        CollisionDetector& cd);
    void checkPlayerKicksBomb(FloatRect playerBox,
        bool playerFacingRight,
        CollisionDetector& cd);

    GamakichiBomb* getBomb(int index) const;

private:
    float x, y;
    float bobOffset;
    float bobTimer;

    float moveVelocityY;
    bool  atGround;
    float groundPauseTimer;
    float groundPauseDuration;
    float topLimit;
    float groundLimit;

    int   health;
    bool  defeated;
    float deathTimer;

    float fireTimer;
    float fireInterval;
    int   firePhase;

    bool  isHit;
    float hitFlashTimer;

    Texture texture;
    Texture sharedSnowTexture;
    Sprite  sprite;
    float   animTimer;
    int     animFrame;

    GamakichiBomb* bombs[MAX_GAMA_BOMBS];
    int            bombCount;

    RectangleShape healthBarBg;
    RectangleShape healthBarFill;

    FloatRect hitBox;

    struct GamaFrame { int x, y, w, h; };
    GamaFrame gamaFrames[3];

    void fireBombs();
    void checkBombRollingHit(CollisionDetector& cd);
    void updateBombs(float dt, Platform* platforms[],
        int platformCount, CollisionDetector& cd);
    void drawHealthBar(RenderWindow& window);
    void updateHitBox();
    void setFrame(int index);
};