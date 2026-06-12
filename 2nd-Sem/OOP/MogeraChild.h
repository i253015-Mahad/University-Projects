#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionDetector.h"
#include "Platform.h"
using namespace sf;
using namespace std;

const int CHILD_STATE_WALKING = 0;
const int CHILD_STATE_ROLLING = 1;
const int CHILD_STATE_RESTING = 2;
const int CHILD_STATE_DYING = 3;
const int CHILD_STATE_SNOW_COATED = 4;
const int CHILD_STATE_SNOW_ROLLING = 5;

class MogeraChild {
public:
    MogeraChild(float startX, float startY, bool goingRight, Texture* sharedSnowTexture);

    void loadTexture(string imagePath);
    void update(float dt, Platform* platforms[],
        int platformCount, CollisionDetector& cd);
    void draw(RenderWindow& window, bool showHitBox);

    void applySnowHit();
    void startSnowRolling(bool goRight);
    void kill();

    bool      isActive()      const;
    bool      isDying()       const;
    bool      isSnowCoated()  const;
    bool      isSnowRolling() const;
    int       getState()      const;
    FloatRect getHitBox()     const;

private:
    float x, y;
    float velocityX, velocityY;
    bool  active;
    bool  onGround;
    int   childState;
    bool  hitThisFrame;

    // Walk/roll timing
    float walkTimer;
    float rollTimer;
    float restTimer;
    float rollSpeed;
    float speedUpTimer;
    int   rollCount;
    float deathTimer;
    float ballAngle;

    // Snow coat timer
    float coatTimer;


    Sprite  snowSprite;
    int     snowAnimFrame;
    float   snowAnimTimer;
    int coatLevel;

    Texture   texture;
    Sprite    sprite;
    FloatRect hitBox;

    float animTimer;
    int   animFrame;

    struct ChildFrame { int x, y, w, h; };
    ChildFrame walkFrames[4];
    ChildFrame ballFrames[3];

    void applyGravity(float dt);
    void handlePlatformCollision(Platform* platforms[],
        int platformCount, CollisionDetector& cd);
    void updateHitBox();
    void setWalkFrame(int index);
    void setBallFrame(int index);
    void drawSnowSprite(RenderWindow& window);
};