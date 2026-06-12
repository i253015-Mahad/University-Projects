#pragma once
#include "Enemy.h"

class Botom : public Enemy {
public:
    Botom(float startX, float startY);
    void update(float dt, Platform* platforms[],
    int platformCount, CollisionDetector& cd) override;
    void draw(RenderWindow& window, bool showHitBox) override;
    void loadTexture(string imagePath) override;

protected:
    // Protected so FlyingFoogaFoog can access them
    float      animTimer;
    int        animFrame;
    float      directionTimer;
    float      speed;
    EnemyFrame frames[14];

    void updateAI(float dt);
    void updateAnimation(float dt);
    void setFrame(int index);
};