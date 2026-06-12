#include "FlyingFoogaFoog.h"
#include "Botom.h"
#include <cmath>
#include <cstdlib>

const float GROUND_TIME = 3.0f;   
const float FLY_TIME = 4.0f; 
const float FLY_SPEED = 120.0f;
const float DIR_CHANGE = 1.5f;   
const float FLYNG_HEIGHT = 38.0f;  

FlyingFoogaFoog::FlyingFoogaFoog(float startX, float startY)
    : Botom(startX, startY) {
    flyState = FLYNG_STATE_GROUND;
    groundTimer = 0;
    flyTimer = 0;
    flyDirX = 1.0f;
    flyDirY = -1.0f;
    flySpeed = FLY_SPEED;
    dirChangeTimer = 0;

    for (int i = 0; i < 16; i++)
        flyFrames[i] = { 0, 0, 1, 1 };
}

void FlyingFoogaFoog::loadTexture(string imagePath) {
    if (!texture.loadFromFile(imagePath))
        return;

    sprite.setTexture(texture);

    flyFrames[0] = { 0,   0,   147, 192 };  
    flyFrames[1] = { 147, 0,   233, 192 };  
    flyFrames[2] = { 380, 0,   190, 192 };  

    flyFrames[3] = { 0,   192, 171, 189 }; 
    flyFrames[4] = { 171, 192, 194, 189 };  
    flyFrames[5] = { 365, 192, 194, 189 };  
    flyFrames[6] = { 0,   381, 177, 184 };  
    flyFrames[7] = { 177, 381, 194, 184 }; 

    flyFrames[8] = { 0,   565, 182, 196 };  
    flyFrames[9] = { 182, 565, 193, 196 };  
    flyFrames[10] = { 375, 565, 185, 196 };  

    flyFrames[11] = { 41,  761, 139, 218 };  

    flyFrames[12] = { 41,  761, 139, 218 };  

    setFlyFrame(0);
}

void FlyingFoogaFoog::setFlyFrame(int index) {
    EnemyFrame& f = flyFrames[index];
    sprite.setTextureRect(IntRect(f.x, f.y, f.w, f.h));

    float scale = FLY_TARGET_HEIGHT / (float)f.h;

    if (state == ENEMY_STATE_DEAD) {
        sprite.setOrigin(f.w / 2.0f, f.h / 2.0f);
        sprite.setScale(scale, scale);
        sprite.setRotation(deathAngle);
        sprite.setPosition(x + 20, y + 20);
        return;
    }

    bool needsFlip = flying ? (flyDirX > 0) : (velocityX > 0);

    if (!needsFlip) {
        sprite.setScale(scale, scale);
        sprite.setOrigin(0, 0);
        sprite.setPosition(x, y);
    }
    else {
        sprite.setScale(-scale, scale);
        sprite.setOrigin(0, 0);
        sprite.setPosition(x + (float)f.w * scale, y);
    }
}

void FlyingFoogaFoog::updateFlyAI(float dt) {
    if (state != ENEMY_STATE_WALK) return;

    if (flyState == FLYNG_STATE_GROUND) {
        groundTimer += dt;

        if (groundTimer >= GROUND_TIME) {
            groundTimer = 0;
            flyState = FLYNG_STATE_FLYING;
            flyTimer = 0;

            flyDirX = (rand() % 2 == 0) ? 1.0f : -1.0f;
            flyDirY = (rand() % 2 == 0) ? 1.0f : -1.0f;
        }
    }
    else if (flyState == FLYNG_STATE_FLYING) {
        flyTimer += dt;
        dirChangeTimer += dt;

        x += flyDirX * flySpeed * dt;
        y += flyDirY * flySpeed * dt;

        if (dirChangeTimer >= DIR_CHANGE) {
            dirChangeTimer = 0;
            int dir = rand() % 8;
            float dirs[8][2] = {
                {1,0},{-1,0},{0,1},{0,-1},
                {1,1},{-1,1},{1,-1},{-1,-1}
            };
            flyDirX = dirs[dir][0];
            flyDirY = dirs[dir][1];
        }

        if (x < 0) { x = 0;   flyDirX = 1.0f; }
        if (x > 750) { x = 750; flyDirX = -1.0f; }
        if (y < 50) { y = 50;  flyDirY = 1.0f; }  
        if (y > 520) { y = 520; flyDirY = -1.0f; }  

    
        if (flyTimer >= FLY_TIME) {
            flyState = FLYNG_STATE_GROUND;
            flyTimer = 0;
            groundTimer = 0;
            flyDirY = 0;
        }
    }
}

void FlyingFoogaFoog::updateFlyAnimation(float dt) {
    animTimer += dt;
    if (animTimer < 0.12f) return;
    animTimer = 0;

    switch (state) {
    case ENEMY_STATE_WALK:
        if (flyState == FLYNG_STATE_FLYING) {
           
            if (animFrame < 3 || animFrame > 7)
                animFrame = 3;
            else {
                animFrame++;
                if (animFrame > 7) animFrame = 3;
            }
        }
        else {
          
            if (animFrame < 0 || animFrame > 2)
                animFrame = 0;
            else {
                animFrame++;
                if (animFrame > 2) animFrame = 0;
            }
        }
        break;

    case ENEMY_STATE_PARTIAL_COAT:
        if (animFrame < 8 || animFrame > 10)
            animFrame = 8;
        else {
            animFrame++;
            if (animFrame > 10) animFrame = 8;
        }
        break;

    case ENEMY_STATE_FULL_COAT:
    case ENEMY_STATE_ROLLING:
        animFrame = 11;
        break;

    case ENEMY_STATE_ESCAPING:
        animFrame = (animFrame == 8) ? 9 : 8;
        break;

    case ENEMY_STATE_DEAD:
        animFrame = 12;
        break;
    }
}

void FlyingFoogaFoog::update(float dt, Platform* platforms[],
    int platformCount, CollisionDetector& cd) {

    if (state == ENEMY_STATE_DEAD) {
        deathTimer += dt;
        updateFlyAnimation(dt);
        return;
    }

    if (state == ENEMY_STATE_ROLLING) {
        updateRollingLogic(dt, platforms, platformCount, cd);
        updateSnowAnimation(dt);
        updateFlyAnimation(dt);
        return;
    }

    if (flyState == FLYNG_STATE_FLYING &&
        state == ENEMY_STATE_WALK) {
        updateFlyAI(dt);
        updateHitBox(45, 45);
        updateEscapeLogic(dt);
        updateSnowAnimation(dt);
        updateFlyAnimation(dt);
        return;
    }

    applyGravity(dt);

    if (state == ENEMY_STATE_WALK)
        x += velocityX * dt;

    y += velocityY * dt;

    if (x < 0)   x = 0;
    if (x > 750) x = 750;

    updateHitBox(45, 50);
    handlePlatformCollision(platforms, platformCount, cd);
    updateHitBox(45, 50);

    if (state == ENEMY_STATE_WALK) {
        directionTimer += dt;
        if (directionTimer >= 2.5f) {
            directionTimer = 0;
            if (rand() % 3 == 0)
                velocityX = -velocityX;
        }
        if (x <= 5) { x = 5;   velocityX = speed; }
        if (x >= 745) { x = 745; velocityX = -speed; }
    }

    updateFlyAI(dt);
    updateEscapeLogic(dt);
    updateSnowAnimation(dt);
    updateFlyAnimation(dt);
}

void FlyingFoogaFoog::draw(RenderWindow& window, bool showHitBox) {
    if (state == ENEMY_STATE_FULL_COAT ||
        state == ENEMY_STATE_ROLLING ||
        state == ENEMY_STATE_PARTIAL_COAT) {
        drawSnowSprite(window);
    }
    else if (state == ENEMY_STATE_ESCAPING) {
        setFlyFrame(animFrame);
        window.draw(sprite);
        drawSnowSprite(window);
    }
    else {
        setFlyFrame(animFrame);
        window.draw(sprite);
    }

    if (showHitBox)
        drawHitBox(window);
}