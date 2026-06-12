#include "Enemy.h"

const float ENEMY_GRAVITY = 700.0f;
const float COAT_TIME_1 = 3.0f;
const float COAT_TIME_2 = 5.0f;
const float COAT_TIME_3 = 999.0f;
const float ESCAPE_TIME = 0.8f;
const float ROLL_SPEED = 300.0f;

const SnowFrame SNOW_FRAMES[12] = {
    { 72,  3266, 256, 301 },
    { 328, 3266, 305, 301 },
    { 633, 3266, 315, 301 },
    { 948, 3266, 305, 301 },
    { 72,  3567, 256, 306 },
    { 328, 3567, 305, 306 },
    { 633, 3567, 315, 306 },
    { 948, 3567, 305, 306 },
    { 72,  3873, 256, 287 },
    { 328, 3873, 305, 287 },
    { 633, 3873, 315, 287 },
    { 948, 3873, 305, 287 },
};

Enemy::Enemy(float startX, float startY) {
    x = startX;
    y = startY;
    velocityX = 0;
    velocityY = 0;
    onGround = false;
    alive = true;
    state = ENEMY_STATE_WALK;
    coatTimer = 0;
    escapeTimer = 0;
    rollSpeed = ROLL_SPEED;
    chainCount = 0;
    deathTimer = 0;
    coatLevel = 0;
    hitThisFrame = false;
    hitsToCoat = 2;
    shakeTimer = 0;
    shakeOffset = 0;
    snowAnimFrame = 0;
    snowAnimTimer = 0;

    snowTexture.loadFromFile("assets/Images/Nick.png");
    snowSprite.setTexture(snowTexture);
}

void Enemy::applySnowHit() {
    if (hitThisFrame) return;
    hitThisFrame = true;

    if (state == ENEMY_STATE_ROLLING) return;
    if (state == ENEMY_STATE_DEAD)    return;

    coatLevel++;

    if (hitsToCoat == 1 ||
        coatLevel >= hitsToCoat) {
        // Fully encase
        state = ENEMY_STATE_FULL_COAT;
        coatTimer = COAT_TIME_3;
        velocityX = 0;
        coatLevel = hitsToCoat;
        snowAnimFrame = 4;
    }
    else {
        // Partial coat
        state = ENEMY_STATE_PARTIAL_COAT;
        coatTimer = (coatLevel == 1) ?
            COAT_TIME_1 : COAT_TIME_2;
        velocityX = 0;
        snowAnimFrame = 0;
    }
}

void Enemy::resetHitFlag() {
    hitThisFrame = false;
}

void Enemy::setHitsToCoat(int hits) {
    hitsToCoat = hits;
}

void Enemy::startRolling(bool goingRight) {
    if (state != ENEMY_STATE_FULL_COAT) return;
    state = ENEMY_STATE_ROLLING;
    velocityX = goingRight ? ROLL_SPEED : -ROLL_SPEED;
    velocityY = 0;
    snowAnimFrame = 4;
}

void Enemy::killEnemy() {
    state = ENEMY_STATE_DEAD;
    velocityX = 0;
    velocityY = 0;
}

void Enemy::incrementChain() {
    chainCount++;
    if (velocityX > 0) velocityX += 20.0f;
    else               velocityX -= 20.0f;
}

bool Enemy::shouldRemove() const {
    return state == ENEMY_STATE_DEAD &&
        deathTimer > 1.0f;
}

void Enemy::updateSnowAnimation(float dt) {
    if (state == ENEMY_STATE_WALK ||
        state == ENEMY_STATE_DEAD) return;

    snowAnimTimer += dt;
    if (snowAnimTimer < 0.1f) return;
    snowAnimTimer = 0;

    if (state == ENEMY_STATE_PARTIAL_COAT) {
        snowAnimFrame++;
        if (snowAnimFrame > 3) snowAnimFrame = 0;
    }
    else if (state == ENEMY_STATE_FULL_COAT ||
        state == ENEMY_STATE_ROLLING) {
        if (snowAnimFrame < 4) snowAnimFrame = 4;
        snowAnimFrame++;
        if (snowAnimFrame > 7) snowAnimFrame = 4;
    }
    else if (state == ENEMY_STATE_ESCAPING) {
        snowAnimFrame = (snowAnimFrame == 8) ? 9 : 8;
    }
}

void Enemy::drawSnowSprite(RenderWindow& window) {
    if (state == ENEMY_STATE_WALK ||
        state == ENEMY_STATE_DEAD) return;

    const SnowFrame& f = SNOW_FRAMES[snowAnimFrame];
    snowSprite.setTextureRect(
        IntRect(f.x, f.y, f.w, f.h));

    float scaleX = hitBox.width / (float)f.w;
    float scaleY = hitBox.height / (float)f.h;

    snowSprite.setScale(scaleX, scaleY);
    snowSprite.setPosition(hitBox.left, hitBox.top);
    window.draw(snowSprite);
}

void Enemy::updateEscapeLogic(float dt) {
    if (state == ENEMY_STATE_PARTIAL_COAT ||
        state == ENEMY_STATE_FULL_COAT) {
        coatTimer -= dt;
        if (coatTimer <= 0) {
            state = ENEMY_STATE_ESCAPING;
            escapeTimer = ESCAPE_TIME;
            shakeTimer = 0;
            snowAnimFrame = 8;
        }
    }

    if (state == ENEMY_STATE_ESCAPING) {
        escapeTimer -= dt;
        shakeTimer += dt;
        shakeOffset = (int)(shakeTimer * 20) % 2 == 0 ?
            3.0f : -3.0f;

        if (escapeTimer <= 0) {
            state = ENEMY_STATE_WALK;
            shakeOffset = 0;
            coatLevel = 0;
            velocityX = (rand() % 2 == 0) ?
                80.0f : -80.0f;
        }
    }
}

void Enemy::updateRollingLogic(float dt,
    Platform* platforms[], int platformCount,
    CollisionDetector& cd) {
    if (state != ENEMY_STATE_ROLLING) return;

    velocityY += 5000.0f * dt;
    if (velocityY > 800.0f)
        velocityY = 800.0f;

    y += velocityY * dt;
    x += velocityX * dt;

    if (y > 580) {
        state = ENEMY_STATE_DEAD;
        return;
    }

    updateHitBox(55, 55);  

    onGround = false;
    for (int i = 0; i < platformCount; i++) {
        if (platforms[i] == nullptr) continue;
        FloatRect platBox = platforms[i]->getHitBox();

        if (cd.isLandingOn(hitBox, platBox, velocityY)) {
            y = platBox.top - hitBox.height;
            velocityY = 0;
            onGround = true;
            updateHitBox(55, 55);  
        }
    }

    if (x + 55 < 0 || x > 800) {
        state = ENEMY_STATE_DEAD;
        return;
    }
}


void Enemy::applyGravity(float dt) {
    if (!onGround) {
        velocityY += ENEMY_GRAVITY * dt;
        if (velocityY > 600.0f)
            velocityY = 600.0f;
    }
}

void Enemy::handlePlatformCollision(
    Platform* platforms[], int platformCount,
    CollisionDetector& cd) {
    onGround = false;

    for (int i = 0; i < platformCount; i++) {
        if (platforms[i] == nullptr) continue;
        FloatRect platBox = platforms[i]->getHitBox();

        if (cd.isLandingOn(hitBox, platBox, velocityY)) {
            y = platBox.top - hitBox.height;
            velocityY = 0;
            onGround = true;
        }
        else if (cd.hitsFromLeft(hitBox, platBox)) {
            x = platBox.left - hitBox.width;
            velocityX = -velocityX;
        }
        else if (cd.hitsFromRight(hitBox, platBox)) {
            x = platBox.left + platBox.width;
            velocityX = -velocityX;
        }
    }
}

void Enemy::updateHitBox(float w, float h) {
    hitBox = FloatRect(x, y, w, h);
}

void Enemy::drawHitBox(RenderWindow& window) {
    RectangleShape debug;
    debug.setPosition(hitBox.left, hitBox.top);
    debug.setSize(Vector2f(hitBox.width, hitBox.height));
    debug.setFillColor(Color::Transparent);
    debug.setOutlineColor(Color::Red);
    debug.setOutlineThickness(1.0f);
    window.draw(debug);
}

bool      Enemy::isDefeated()    const {
    return state == ENEMY_STATE_DEAD;
}
bool      Enemy::isFullyCoated() const {
    return state == ENEMY_STATE_FULL_COAT;
}
bool      Enemy::isRolling()     const {
    return state == ENEMY_STATE_ROLLING;
}
int       Enemy::getState()      const { return state; }
int       Enemy::getChainCount() const { return chainCount; }
FloatRect Enemy::getHitBox()     const { return hitBox; }