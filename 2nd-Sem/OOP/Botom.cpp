#include "Botom.h"
#include "Enemy.h"
using namespace std;

const float BOTOM_SPEED = 110.0f;
const float DIRECTION_CHANGE = 4.0f;
const float BOTOM_TARGET_HEIGHT = 55.0f;

Botom::Botom(float startX, float startY) : Enemy(startX, startY) {
    animTimer = 0;
    animFrame = 2;
    directionTimer = (float)(rand() % 3);
    speed = BOTOM_SPEED;
    velocityX = (rand() % 2 == 0) ? speed : -speed;
    hitBox = FloatRect(x, y, 50, 55);

    for (int i = 0; i < 14; i++)
        frames[i] = { 0, 0, 1, 1 };
}

void Botom::loadTexture(string imagePath) {
    if (!texture.loadFromFile(imagePath))
        return;

    sprite.setTexture(texture);

    frames[0] = { 6,   135,  94,  88 };
    frames[1] = { 6,   135,  94,  88 };
    frames[2] = { 1,   365,  96,  85 };
    frames[3] = { 185, 365, 101,  85 };
    frames[4] = { 4,   715,  89,  78 };
    frames[5] = { 4,   715,  89,  78 };
    frames[6] = { 97,  710,  95,  82 };
    frames[7] = { 2,   822,  90,  85 };
    frames[8] = { 95,  822,  93,  85 };
    frames[9] = { 192, 822,  96,  85 };
    frames[10] = { 2,   1052, 93,  94 };
    frames[11] = { 190, 1050, 87,  90 };
    frames[12] = { 660, 1070, 97,  70 };
    frames[13] = { 758, 1093, 93,  42 };

    setFrame(2);
}

void Botom::setFrame(int index) {
    EnemyFrame& f = frames[index];
    sprite.setTextureRect(IntRect(f.x, f.y, f.w, f.h));

    float scale = BOTOM_TARGET_HEIGHT / (float)f.h;

    
    bool needsFlip = (velocityX > 0);

    if (!needsFlip) {
        sprite.setScale(scale, scale);
        sprite.setOrigin(0, 0);
        sprite.setPosition(x + shakeOffset, y - 5.0f);
    }
    else {
        sprite.setScale(-scale, scale);
        sprite.setOrigin(0, 0);
        sprite.setPosition(x + (float)f.w * scale + shakeOffset, y - 5.0f);
    }
}

void Botom::updateAI(float dt) {
    if (state != ENEMY_STATE_WALK) return;

    directionTimer += dt;


    if (directionTimer >= DIRECTION_CHANGE) {
        directionTimer = 0;
        int roll = rand() % 4;
        if (roll == 0)
            velocityX = -velocityX;  
        else if (roll == 1 && onGround) {
            velocityY = -450.0f;
            onGround = false;
        }
    }

    if (x <= 5) {
        x = 5;
        velocityX = speed;
    }
    if (x >= 745) {
        x = 745;
        velocityX = -speed;
    }
}

void Botom::updateAnimation(float dt) {
    animTimer += dt;
    if (animTimer < 0.15f) return;
    animTimer = 0;

    switch (state) {
    case ENEMY_STATE_WALK:
        animFrame = (animFrame == 2) ? 3 : 2;
        break;
    case ENEMY_STATE_PARTIAL_COAT:
        animFrame = (animFrame == 4) ? 5 : 4;
        break;
    case ENEMY_STATE_FULL_COAT:
    case ENEMY_STATE_ROLLING:
        animFrame = 6;
        break;
    case ENEMY_STATE_ESCAPING:
        if (animFrame < 7 || animFrame > 9)
            animFrame = 7;
        else {
            animFrame++;
            if (animFrame > 9) animFrame = 7;
        }
        break;
    case ENEMY_STATE_DEAD:
        if (animFrame < 10)
            animFrame = 10;
        else if (animFrame < 13)
            animFrame++;
        break;
    }
}

void Botom::update(float dt, Platform* platforms[],
    int platformCount, CollisionDetector& cd) {

    if (state == ENEMY_STATE_DEAD) {
        deathTimer += dt;
        updateAnimation(dt);
        return;
    }

    if (state == ENEMY_STATE_ROLLING) {
        updateRollingLogic(dt, platforms, platformCount, cd);
        updateSnowAnimation(dt);
        updateAnimation(dt);
        return;
    }

    applyGravity(dt);

    if (state == ENEMY_STATE_WALK)
        x += velocityX * dt;

    y += velocityY * dt;

    if (x < 0)   x = 0;
    if (x > 750) x = 750;

    updateHitBox(50, 55);
    handlePlatformCollision(platforms, platformCount, cd);
    updateHitBox(50, 55);

    updateAI(dt);
    updateEscapeLogic(dt);
    updateSnowAnimation(dt);
    updateAnimation(dt);
}

void Botom::draw(RenderWindow& window, bool showHitBox) {
    if (state == ENEMY_STATE_FULL_COAT ||
        state == ENEMY_STATE_ROLLING ||
        state == ENEMY_STATE_PARTIAL_COAT) {
        
        drawSnowSprite(window);
    }
    else if (state == ENEMY_STATE_ESCAPING) {
        setFrame(animFrame);
        window.draw(sprite);
        drawSnowSprite(window);
    }
    else {
        setFrame(animFrame);
        window.draw(sprite);
    }

    if (showHitBox)
        drawHitBox(window);
}