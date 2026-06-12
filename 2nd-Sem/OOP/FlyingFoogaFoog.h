#pragma once
#include "Botom.h"

const int FLYNG_STATE_GROUND = 0;
const int FLYNG_STATE_FLYING = 1;

const float FLY_TARGET_HEIGHT = 38.0f;

class FlyingFoogaFoog : public Botom {
public:
    FlyingFoogaFoog(float startX, float startY);

    void update(float dt, Platform* platforms[],
        int platformCount, CollisionDetector& cd) override;
    void draw(RenderWindow& window, bool showHitBox) override;
    void loadTexture(string imagePath) override;

protected:
    int   flyState;
    float groundTimer;
    float flyTimer;
    float flyDirX;
    float flyDirY;
    float flySpeed;
    float dirChangeTimer;

    float deathAngle;

    bool flying;

    EnemyFrame flyFrames[16];

    void updateFlyAI(float dt);
    void updateFlyAnimation(float dt);
    void setFlyFrame(int index);
};