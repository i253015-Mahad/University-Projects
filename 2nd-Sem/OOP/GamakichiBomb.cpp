#include "GamakichiBomb.h"

const float BOMB_GRAVITY = 500.0f;
const float BOMB_WALK_SPEED = 70.0f;
const float BOMB_ROLL_SPEED = 280.0f;
const float BOMB_HEIGHT = 55.0f;   
const float BOMB_COAT_TIME = 5.0f;
const float BOMB_EXPLODE_DUR = 0.8f;

const int BSNOW[12][4] = {
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

GamakichiBomb::GamakichiBomb(float startX, float startY, float dirX, float dirY, Texture* sharedSnowTexture)
{
    x = startX;
    y = startY;
    active = true;
    onGround = false;
    bombState = BOMB_STATE_WALKING;
    hitThisFrame = false;
    coatTimer = 0;
    explodeTimer = 0;
    ballAngle = 0;
    animTimer = 0;
    animFrame = 0;
    snowAnimFrame = 0;  
    snowAnimTimer = 0;
    coatLevel = 0;
    lifetime = 0;
    maxLifetime = 6.0f;  

    velocityX = dirX * BOMB_WALK_SPEED;
    velocityY = dirY * BOMB_WALK_SPEED;

    walkFrames[0] = { 260, 220, 37, 42 };
    walkFrames[1] = { 301, 226, 34, 41 };
    walkFrames[2] = { 340, 222, 41, 41 };

    explodeFrames[0] = { 639, 60, 44, 46 };
    explodeFrames[1] = { 684, 60, 45, 46 };
    explodeFrames[2] = { 730, 60, 47, 46 };
    explodeFrames[3] = { 779, 66, 38, 29 };

    if (sharedSnowTexture != nullptr)
        snowSprite.setTexture(*sharedSnowTexture);

    updateHitBox();
}

void GamakichiBomb::loadTexture(string imagePath) {
    if (!texture.loadFromFile(imagePath)) return;
    sprite.setTexture(texture);
    setWalkFrame(0);
}

void GamakichiBomb::setWalkFrame(int index) {
    BombFrame& f = walkFrames[index];
    sprite.setTextureRect(IntRect(f.x, f.y, f.w, f.h));

    float scale = BOMB_HEIGHT / (float)f.h;
    sprite.setOrigin(0, 0);
    sprite.setRotation(0);
    sprite.setScale(scale, scale);
    sprite.setPosition(x, y);
}

void GamakichiBomb::setExplodeFrame(int index) {
    BombFrame& f = explodeFrames[index];
    sprite.setTextureRect(IntRect(f.x, f.y, f.w, f.h));

    float scale = 65.0f / (float)f.h;
    sprite.setScale(scale, scale);
    sprite.setOrigin(0, 0);
    sprite.setPosition(x - 10, y - 10);
}

void GamakichiBomb::drawSnowSprite(RenderWindow& window) {
    const int* f = BSNOW[snowAnimFrame];
    snowSprite.setTextureRect(
        IntRect(f[0], f[1], f[2], f[3]));

    float scaleX = hitBox.width / (float)f[2];
    float scaleY = hitBox.height / (float)f[3];

    snowSprite.setScale(scaleX, scaleY);
    snowSprite.setPosition(hitBox.left, hitBox.top);
    window.draw(snowSprite);
}

void GamakichiBomb::applySnowHit() {
    if (hitThisFrame) return;
    hitThisFrame = true;

    if (bombState == BOMB_STATE_ROLLING ||
        bombState == BOMB_STATE_EXPLODING ||
        bombState == BOMB_STATE_COATED) return;

    coatLevel++;

    if (coatLevel >= 2) {
        bombState = BOMB_STATE_COATED;
        coatTimer = BOMB_COAT_TIME;
        velocityX = 0;
        velocityY = 0;
        snowAnimFrame = 4;
        coatLevel = 2;
    }
    else {
        velocityX *= 0.5f;
        snowAnimFrame = 0;
    }
}

void GamakichiBomb::startRolling(bool goRight) {
    if (bombState != BOMB_STATE_COATED) return;
    bombState = BOMB_STATE_ROLLING;
    velocityX = goRight ?
        BOMB_ROLL_SPEED : -BOMB_ROLL_SPEED;
    snowAnimFrame = 4;  
}

void GamakichiBomb::explode() {
    if (bombState == BOMB_STATE_EXPLODING) return;
    bombState = BOMB_STATE_EXPLODING;
    explodeTimer = 0;
    animFrame = 0;
    velocityX = 0;
    velocityY = 0;
}

void GamakichiBomb::applyGravity(float dt) {
    if (!onGround) {
        velocityY += BOMB_GRAVITY * dt;
        if (velocityY > 500.0f) velocityY = 500.0f;
    }
}

void GamakichiBomb::handlePlatformCollision(
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

void GamakichiBomb::updateHitBox() {
    hitBox = FloatRect(x, y, 50, 55);
}

void GamakichiBomb::update(float dt,
    Platform* platforms[], int platformCount,
    CollisionDetector& cd) {

    if (bombState == BOMB_STATE_WALKING) {
        lifetime += dt;
        if (lifetime >= maxLifetime)
            explode();
    }

    if (!active) return;

    hitThisFrame = false;

    if (bombState == BOMB_STATE_EXPLODING) {
        explodeTimer += dt;
        animTimer += dt;
        if (animTimer >= 0.15f) {
            animTimer = 0;
            animFrame++;
            if (animFrame >= 4) animFrame = 3;
        }
        if (explodeTimer >= BOMB_EXPLODE_DUR)
            active = false;
        return;
    }

    if (bombState == BOMB_STATE_COATED) {
        applyGravity(dt);
        y += velocityY * dt;
        handlePlatformCollision(platforms,
            platformCount, cd);
        updateHitBox();

        coatTimer -= dt;
        if (coatTimer <= 0) {
            bombState = BOMB_STATE_WALKING;
            coatLevel = 0;
            velocityX = (x < 600) ?
                BOMB_WALK_SPEED : -BOMB_WALK_SPEED;
        }

        snowAnimTimer += dt;
        if (snowAnimTimer >= 0.1f) {
            snowAnimTimer = 0;
            snowAnimFrame++;
            if (snowAnimFrame > 7) snowAnimFrame = 4;
        }
        return;
    }

    applyGravity(dt);

    if (bombState == BOMB_STATE_WALKING) {
        x += velocityX * dt;

        if (x < 0) { x = 0;    velocityX = abs(velocityX); }
        if (x > 745) { x = 745; velocityX = -abs(velocityX); }
    }
    else if (bombState == BOMB_STATE_ROLLING) {
        x += velocityX * dt;

        ballAngle += abs(velocityX) * dt * 0.5f;
        if (ballAngle > 360.0f) ballAngle -= 360.0f;

        snowAnimTimer += dt;
        if (snowAnimTimer >= 0.08f) {
            snowAnimTimer = 0;
            snowAnimFrame++;
            if (snowAnimFrame > 7) snowAnimFrame = 4;
        }

        if (x < -60 || x > 860) {
            active = false;
            return;
        }
    }

    y += velocityY * dt;
    if (y > 620) { active = false; return; }

    handlePlatformCollision(platforms,
        platformCount, cd);
    updateHitBox();

    if (bombState == BOMB_STATE_WALKING) {
        animTimer += dt;
        if (animTimer >= 0.15f) {
            animTimer = 0;
            animFrame = (animFrame + 1) % 3;
        }
    }
}

void GamakichiBomb::draw(RenderWindow& window,
    bool showHitBox) {
    if (!active) return;

    sprite.setColor(Color(255, 255, 255, 255));

    switch (bombState) {
    case BOMB_STATE_WALKING:
        setWalkFrame(animFrame % 3);
        window.draw(sprite);
        break;

    case BOMB_STATE_COATED:
        drawSnowSprite(window);
        break;

    case BOMB_STATE_ROLLING:
        drawSnowSprite(window);
        break;

    case BOMB_STATE_EXPLODING:
        setExplodeFrame(animFrame % 4);
        window.draw(sprite);
        break;
    }

    if (showHitBox &&
        bombState != BOMB_STATE_EXPLODING) {
        RectangleShape debug;
        debug.setPosition(hitBox.left, hitBox.top);
        debug.setSize(Vector2f(
            hitBox.width, hitBox.height));
        debug.setFillColor(Color::Transparent);
        debug.setOutlineColor(Color::Yellow);
        debug.setOutlineThickness(1.0f);
        window.draw(debug);
    }
}

bool GamakichiBomb::isActive()    const { return active; }
bool GamakichiBomb::isCoated()    const {
    return bombState == BOMB_STATE_COATED;
}
bool GamakichiBomb::isRolling()   const {
    return bombState == BOMB_STATE_ROLLING;
}
bool GamakichiBomb::isExploding() const {
    return bombState == BOMB_STATE_EXPLODING;
}
FloatRect GamakichiBomb::getHitBox() const { return hitBox; }