#pragma once
#include "FlyingFoogaFoog.h"
#include "Knife.h"

const int MAX_KNIVES = 5;

const int TORNADO_STATE_NORMAL = 0;
const int TORNADO_STATE_SPINNING = 1;
const int TORNADO_STATE_TORNADO = 2;

class Tornado : public FlyingFoogaFoog {
public:
    Tornado(float startX, float startY);
    ~Tornado();

    void update(float dt, Platform* platforms[],
        int platformCount, CollisionDetector& cd) override;

    void update(float dt, Platform* platforms[],
        int platformCount, CollisionDetector& cd,
        float playerX, float playerY);

    void draw(RenderWindow& window, bool showHitBox) override;
    void loadTexture(string imagePath) override;

    bool checkKnifeHit(FloatRect playerHitBox,
        CollisionDetector& cd);

    bool isTornadoForm() const;

protected:
    int   tornadoState;
    float tornadoTimer;
    float tornadoDuration;
    float normalTimer;
    float tornadoSpeed;

    float  knifeTimer;
    float  knifeInterval;
    float  lastPlayerX;
    float  lastPlayerY;
    Knife* knives[MAX_KNIVES];
    int    knifeCount;

    float deathAngle;

   
    EnemyFrame tornadoFrames[18];

    void throwKnife();
    void updateKnives(float dt);
    void updateTornadoForm(float dt);
    void setTornadoFrame(int index);
    void updateTornadoAnimation(float dt);
};