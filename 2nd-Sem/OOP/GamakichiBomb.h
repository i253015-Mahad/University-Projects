#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionDetector.h"
#include "Platform.h"
using namespace sf;
using namespace std;

const int BOMB_STATE_WALKING = 0;
const int BOMB_STATE_COATED = 1;
const int BOMB_STATE_ROLLING = 2;
const int BOMB_STATE_EXPLODING = 3;

class GamakichiBomb {
public:
    GamakichiBomb(float startX, float startY, float dirX, float dirY, Texture* sharedSnowTexture);

    void loadTexture(string imagePath);
    void update(float dt, Platform* platforms[],
        int platformCount, CollisionDetector& cd);
    void draw(RenderWindow& window, bool showHitBox);

    void applySnowHit();
    void startRolling(bool goRight);
    void explode();

    bool      isActive()    const;
    bool      isCoated()    const;
    bool      isRolling()   const;
    bool      isExploding() const;
    FloatRect getHitBox()   const;

private:
    float x, y;
    float velocityX, velocityY;
    bool  active;
    bool  onGround;
    int   bombState;
    bool  hitThisFrame;
    float lifetime;
    float maxLifetime;

    float coatTimer;
    float explodeTimer;
    float ballAngle;

    Texture   texture;
    Sprite    sprite;
    FloatRect hitBox;

    float animTimer;
    int   animFrame;


    Sprite  snowSprite;
    int     snowAnimFrame;
    float   snowAnimTimer;
    int coatLevel;

    struct BombFrame { int x, y, w, h; };
    BombFrame walkFrames[3];
    BombFrame explodeFrames[4];

    void applyGravity(float dt);
    void handlePlatformCollision(Platform* platforms[],
        int platformCount, CollisionDetector& cd);
    void updateHitBox();
    void setWalkFrame(int index);
    void setExplodeFrame(int index);
    void drawSnowSprite(RenderWindow& window);
};