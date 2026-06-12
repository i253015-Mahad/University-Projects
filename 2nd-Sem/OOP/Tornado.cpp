#include "Tornado.h"
#include <cmath>
#include <cstdlib>

const float TORNADO_HEIGHT = 38.0f;
const float KNIFE_INTERVAL = 3.0f;
const float NORMAL_DURATION = 4.0f;
const float TORNADO_DURATION = 3.0f;
const float TORNADO_SPEED = 200.0f;

Tornado::Tornado(float startX, float startY)
    : FlyingFoogaFoog(startX, startY) {
    tornadoState = TORNADO_STATE_NORMAL;
    tornadoTimer = 0;
    tornadoDuration = TORNADO_DURATION;
    normalTimer = 0;
    tornadoSpeed = TORNADO_SPEED;
    knifeTimer = 0;
    knifeInterval = KNIFE_INTERVAL;
    lastPlayerX = 400;
    lastPlayerY = 300;
    knifeCount = 0;
    deathAngle = 0;

    for (int i = 0; i < MAX_KNIVES; i++)
        knives[i] = nullptr;
    for (int i = 0; i < 18; i++)
        tornadoFrames[i] = { 0, 0, 1, 1 };

    flySpeed = 80.0f + (rand() % 100);
}

Tornado::~Tornado() {
    for (int i = 0; i < MAX_KNIVES; i++) {
        delete knives[i];
        knives[i] = nullptr;
    }
}

void Tornado::loadTexture(string imagePath) {
    if (!texture.loadFromFile(imagePath))
        return;

    sprite.setTexture(texture);

    tornadoFrames[0] = { 20,  40,  101, 116 };
    tornadoFrames[1] = { 144, 40,  125, 118 };
    tornadoFrames[2] = { 282, 42,  122, 116 };
    tornadoFrames[3] = { 420, 36,  128, 122 };

    tornadoFrames[4] = { 1,   169, 122, 326 };
    tornadoFrames[5] = { 124, 169, 145, 326 };

    tornadoFrames[6] = { 2,   506, 121, 196 };

    tornadoFrames[7] = { 27,  879,  96,  119 };
    tornadoFrames[8] = { 124, 881,  143, 114 };

    tornadoFrames[9] = { 548, 1049, 120, 118 };  
    tornadoFrames[10] = { 678, 1049, 120, 118 };  
    tornadoFrames[11] = { 886, 1050, 85,  117 };  
    tornadoFrames[12] = { 991, 1049, 94,  104 };  


    tornadoFrames[13] = { 548,  1168, 125, 169 };  
    tornadoFrames[14] = { 694,  1168, 137, 169 };  
    tornadoFrames[15] = { 845,  1168, 112, 164 };  
    tornadoFrames[16] = { 983,  1206, 117, 126 };  
    tornadoFrames[17] = { 1113, 1206, 130, 126 };  

    setTornadoFrame(0);
}

void Tornado::setTornadoFrame(int index) {
    if (state == ENEMY_STATE_FULL_COAT ||
        state == ENEMY_STATE_ROLLING) return;

    EnemyFrame& f = tornadoFrames[index];
    sprite.setTextureRect(IntRect(f.x, f.y, f.w, f.h));

    float scale = TORNADO_HEIGHT / (float)f.h;

    if (state == ENEMY_STATE_DEAD) {
        sprite.setOrigin(f.w / 2.0f, f.h / 2.0f);
        sprite.setScale(scale, scale);
        sprite.setRotation(deathAngle);
        sprite.setPosition(x + 20, y + 20);
        return;
    }

    if (tornadoState == TORNADO_STATE_TORNADO) {
        sprite.setOrigin(0, 0);
        sprite.setScale(scale, scale);
        sprite.setRotation(0);
        sprite.setPosition(x, y);
        return;
    }

    bool needsFlip = (velocityX > 0);

    if (!needsFlip) {
        sprite.setScale(scale, scale);
        sprite.setOrigin(0, 0);
        sprite.setRotation(0);
        sprite.setPosition(x, y);
    }
    else {
        sprite.setScale(-scale, scale);
        sprite.setOrigin(0, 0);
        sprite.setRotation(0);
        sprite.setPosition(x + (float)f.w * scale, y);
    }
}

bool Tornado::isTornadoForm() const {
    return tornadoState == TORNADO_STATE_TORNADO;
}

void Tornado::throwKnife() {
    if (tornadoState == TORNADO_STATE_TORNADO) return;

    for (int i = 0; i < MAX_KNIVES; i++) {
        if (knives[i] == nullptr) {
            knives[i] = new Knife(
                x + 20, y + 20,
                lastPlayerX, lastPlayerY
            );
            knifeCount++;
            knifeInterval = 2.0f + (rand() % 30) / 10.0f;
            return;
        }
    }
}

void Tornado::updateKnives(float dt) {
    for (int i = 0; i < MAX_KNIVES; i++) {
        if (knives[i] != nullptr) {
            knives[i]->update(dt);
            if (!knives[i]->isActive()) {
                delete knives[i];
                knives[i] = nullptr;
                knifeCount--;
            }
        }
    }
}

void Tornado::updateTornadoForm(float dt) {
    if (state != ENEMY_STATE_WALK) return;

    if (tornadoState == TORNADO_STATE_NORMAL) {
        normalTimer += dt;
        if (normalTimer >= NORMAL_DURATION) {
            normalTimer = 0;
            tornadoState = TORNADO_STATE_SPINNING;
            tornadoTimer = 0;
            animFrame = 9;  
        }
    }
    else if (tornadoState == TORNADO_STATE_SPINNING) {
        tornadoTimer += dt;

        if (tornadoTimer >= 0.5f) {
            tornadoState = TORNADO_STATE_TORNADO;
            tornadoTimer = 0;
            float angle = (rand() % 8) * 45.0f * 3.14159f / 180.0f;
            flyDirX = cos(angle);
            flyDirY = sin(angle);
        }
    }
    else if (tornadoState == TORNADO_STATE_TORNADO) {
        tornadoTimer += dt;

        x += flyDirX * tornadoSpeed * dt;
        y += flyDirY * tornadoSpeed * dt;

        if (x < 0) { x = 0;   flyDirX = -flyDirX; }
        if (x > 750) { x = 750; flyDirX = -flyDirX; }
        if (y < 0) { y = 0;   flyDirY = -flyDirY; }
        if (y > 530) { y = 530; flyDirY = -flyDirY; }

        if (tornadoTimer >= tornadoDuration) {
            tornadoState = TORNADO_STATE_NORMAL;
            tornadoTimer = 0;
            normalTimer = 0;
            tornadoDuration = 2.0f + (rand() % 30) / 10.0f;
            animFrame = 0;  
        }
    }
}

void Tornado::updateTornadoAnimation(float dt) {
    animTimer += dt;
    if (animTimer < 0.1f) return;
    animTimer = 0;

    switch (state) {
    case ENEMY_STATE_WALK:
        if (tornadoState == TORNADO_STATE_SPINNING ||
            tornadoState == TORNADO_STATE_TORNADO) {
            if (animFrame < 9 || animFrame > 12)
                animFrame = 9;
            else {
                animFrame++;
                if (animFrame > 12) animFrame = 9;
            }
        }
        else {
            if (knifeTimer > knifeInterval - 0.3f) {
                animFrame = (animFrame == 7) ? 8 : 7;
            }
            else {
                if (animFrame < 0 || animFrame > 3)
                    animFrame = 0;
                else {
                    animFrame++;
                    if (animFrame > 3) animFrame = 0;
                }
            }
        }
        break;

    case ENEMY_STATE_PARTIAL_COAT:
        animFrame = (animFrame == 4) ? 5 : 4;
        break;

    case ENEMY_STATE_FULL_COAT:
    case ENEMY_STATE_ROLLING:
        animFrame = 6;
        break;

    case ENEMY_STATE_DEAD:
        if (animFrame < 13)
            animFrame = 13;
        else if (animFrame < 17)
            animFrame++;
        break;
    }
}

bool Tornado::checkKnifeHit(FloatRect playerHitBox,
    CollisionDetector& cd) {
    for (int i = 0; i < MAX_KNIVES; i++) {
        if (knives[i] == nullptr)   continue;
        if (!knives[i]->isActive()) continue;

        if (cd.overlaps(knives[i]->getHitBox(), playerHitBox)) {
            knives[i]->killKnife();
            return true;
        }
    }
    return false;
}

void Tornado::update(float dt, Platform* platforms[],
    int platformCount, CollisionDetector& cd,
    float playerX, float playerY) {

    lastPlayerX = playerX;
    lastPlayerY = playerY;

    if (state == ENEMY_STATE_DEAD) {
        deathTimer += dt;
        updateTornadoAnimation(dt);
        updateKnives(dt);
        return;
    }

    if (state == ENEMY_STATE_ROLLING) {
        updateRollingLogic(dt, platforms, platformCount, cd);
        updateSnowAnimation(dt);
        updateTornadoAnimation(dt);
        updateKnives(dt);
        return;
    }

    if (tornadoState == TORNADO_STATE_TORNADO ||
        tornadoState == TORNADO_STATE_SPINNING) {
        updateTornadoForm(dt);
        updateHitBox(40, 40);
        updateTornadoAnimation(dt);
        updateKnives(dt);
        return;
    }

    if (state == ENEMY_STATE_WALK) {
        knifeTimer += dt;
        if (knifeTimer >= knifeInterval) {
            knifeTimer = 0;
            throwKnife();
        }
    }

    applyGravity(dt);

    if (state == ENEMY_STATE_WALK)
        x += velocityX * dt;

    y += velocityY * dt;

    if (x < 0)   x = 0;
    if (x > 750) x = 750;

    updateHitBox(40, 45);
    handlePlatformCollision(platforms, platformCount, cd);
    updateHitBox(40, 45);

    if (state == ENEMY_STATE_WALK) {
        directionTimer += dt;
        if (directionTimer >= 2.5f) {
            directionTimer = 0;
            int roll = rand() % 4;
            if (roll == 0)
                velocityX = -velocityX;
            else if (roll == 1 && onGround) {
                velocityY = -450.0f;
                onGround = false;
            }
        }
        if (x <= 5) { x = 5;   velocityX = speed; }
        if (x >= 745) { x = 745; velocityX = -speed; }
    }

    updateTornadoForm(dt);
    updateEscapeLogic(dt);
    updateSnowAnimation(dt);
    updateTornadoAnimation(dt);
    updateKnives(dt);
}

void Tornado::update(float dt, Platform* platforms[],
    int platformCount, CollisionDetector& cd) {
    update(dt, platforms, platformCount, cd,
        lastPlayerX, lastPlayerY);
}

void Tornado::draw(RenderWindow& window, bool showHitBox) {
    if (state == ENEMY_STATE_FULL_COAT ||
        state == ENEMY_STATE_ROLLING ||
        state == ENEMY_STATE_PARTIAL_COAT) {
        drawSnowSprite(window);
    }
    else if (state == ENEMY_STATE_ESCAPING) {
        setTornadoFrame(animFrame);
        window.draw(sprite);
        drawSnowSprite(window);
    }
    else {
        setTornadoFrame(animFrame);
        window.draw(sprite);
    }

    for (int i = 0; i < MAX_KNIVES; i++) {
        if (knives[i] != nullptr)
            knives[i]->draw(window, showHitBox);
    }

    if (showHitBox)
        drawHitBox(window);
}