#include "MogeraChild.h"

const float CHILD_GRAVITY = 600.0f;
const float CHILD_WALK_SPEED = 80.0f;
const float CHILD_INITIAL_ROLL = 180.0f;
const float CHILD_MAX_ROLL = 420.0f;
const float CHILD_SPEEDUP = 60.0f;
const float SPEEDUP_INTERVAL = 1.2f;
const float WALK_DURATION = 2.0f;
const float ROLL_DURATION = 1.5f;
const float REST_DURATION = 1.0f;
const float CHILD_HEIGHT = 38.0f;
const float BALL_HEIGHT = 35.0f;
const float SNOW_COAT_TIME = 5.0f;
const float SNOW_ROLL_SPEED = 300.0f;

const int SNOW_F[12][4] = {
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

MogeraChild::MogeraChild(float startX, float startY, bool goingRight, Texture* sharedSnowTexture) {
    x = startX;
    y = startY;
    active = true;
    onGround = false;
    childState = CHILD_STATE_WALKING;
    hitThisFrame = false;
    walkTimer = 0;
    rollTimer = 0;
    restTimer = 0;
    rollSpeed = CHILD_INITIAL_ROLL;
    speedUpTimer = 0;
    rollCount = 0;
    deathTimer = 0;
    ballAngle = 0;
    coatTimer = 0;
    animTimer = 0;
    animFrame = 0;
    snowAnimFrame = 0;
    snowAnimTimer = 0;
    coatLevel = 0;

    velocityX = goingRight ?
        CHILD_WALK_SPEED : -CHILD_WALK_SPEED;
    velocityY = 0;

    walkFrames[0] = { 1784, 798, 178, 173 }; 
    walkFrames[1] = { 1962, 798, 177, 188 }; 
    walkFrames[2] = { 1784, 798, 178, 173 };  
    walkFrames[3] = { 1962, 798, 177, 188 };  

    ballFrames[0] = { 1830, 980, 99,  161 };
    ballFrames[1] = { 2030, 985, 92,  156 };
    ballFrames[2] = { 2210, 999, 90,  142 };

    if (sharedSnowTexture != nullptr)
        snowSprite.setTexture(*sharedSnowTexture);

    updateHitBox();
}

void MogeraChild::loadTexture(string imagePath) {
    if (!texture.loadFromFile(imagePath)) return;
    sprite.setTexture(texture);
    setWalkFrame(0);
}

void MogeraChild::applySnowHit() {
    if (hitThisFrame) return;
    hitThisFrame = true;

    if (childState == CHILD_STATE_SNOW_COATED ||
        childState == CHILD_STATE_SNOW_ROLLING ||
        childState == CHILD_STATE_DYING) return;

    coatLevel++;

    if (coatLevel >= 2) {
        childState = CHILD_STATE_SNOW_COATED;
        coatTimer = SNOW_COAT_TIME;
        velocityX = 0;
        snowAnimFrame = 4;
        coatLevel = 2;
    }
    else {
        velocityX *= 0.5f;
        snowAnimFrame = 0;
    }
}

void MogeraChild::startSnowRolling(bool goRight) {
    if (childState != CHILD_STATE_SNOW_COATED) return;
    childState = CHILD_STATE_SNOW_ROLLING;
    velocityX = goRight ?
        SNOW_ROLL_SPEED : -SNOW_ROLL_SPEED;
}

void MogeraChild::setWalkFrame(int index) {
    ChildFrame& f = walkFrames[index];
    sprite.setTextureRect(IntRect(f.x, f.y, f.w, f.h));

    float scale = CHILD_HEIGHT / (float)f.h;
    sprite.setOrigin(0, 0);
    sprite.setRotation(0);

    if (velocityX > 0) {
        sprite.setScale(-scale, scale);
        sprite.setPosition(
            x + (float)f.w * scale, y);
    }
    else {
        sprite.setScale(scale, scale);
        sprite.setPosition(x, y);
    }
}

void MogeraChild::setBallFrame(int index) {
    ChildFrame& f = ballFrames[index];
    sprite.setTextureRect(IntRect(f.x, f.y, f.w, f.h));

    float scale = BALL_HEIGHT / (float)f.h;
    sprite.setOrigin(f.w / 2.0f, f.h / 2.0f);
    sprite.setScale(scale, scale);
    sprite.setRotation(ballAngle);
    sprite.setPosition(x + 20, y + 20);
}

void MogeraChild::drawSnowSprite(RenderWindow& window) {
    const int* f = SNOW_F[snowAnimFrame];
    snowSprite.setTextureRect(
        IntRect(f[0], f[1], f[2], f[3]));

    float scaleX = hitBox.width / (float)f[2];
    float scaleY = hitBox.height / (float)f[3];

    snowSprite.setScale(scaleX, scaleY);
    snowSprite.setPosition(hitBox.left, hitBox.top);
    window.draw(snowSprite);
}

void MogeraChild::update(float dt,
    Platform* platforms[], int platformCount,
    CollisionDetector& cd) {
    if (!active) return;

    hitThisFrame = false;

    // Death
    if (childState == CHILD_STATE_DYING) {
        deathTimer += dt;
        velocityY += CHILD_GRAVITY * dt;
        y += velocityY * dt;
        if (deathTimer >= 0.5f) active = false;
        return;
    }
    if (childState == CHILD_STATE_SNOW_COATED) {
        applyGravity(dt);
        y += velocityY * dt;
        handlePlatformCollision(platforms,
            platformCount, cd);
        updateHitBox();

        coatTimer -= dt;
        if (coatTimer <= 0) {
            childState = CHILD_STATE_WALKING;
            coatLevel = 0;
            velocityX = (x < 600) ?
                CHILD_WALK_SPEED : -CHILD_WALK_SPEED;
            walkTimer = 0;
        }

        snowAnimTimer += dt;
        if (snowAnimTimer >= 0.1f) {
            snowAnimTimer = 0;
            snowAnimFrame++;
            if (snowAnimFrame > 7) snowAnimFrame = 4;
        }



        return;
    }
    if (childState == CHILD_STATE_SNOW_ROLLING) {
        applyGravity(dt);
        x += velocityX * dt;
        y += velocityY * dt;

        if (x < -60 || x > 860 || y > 620) {
            active = false;
            return;
        }

        handlePlatformCollision(platforms,
            platformCount, cd);
        updateHitBox();

        snowAnimTimer += dt;
        if (snowAnimTimer >= 0.08f) {
            snowAnimTimer = 0;
            snowAnimFrame++;
            if (snowAnimFrame > 7) snowAnimFrame = 4;
        }
        return;
    }

    applyGravity(dt);

    if (childState == CHILD_STATE_WALKING) {
        x += velocityX * dt;
        walkTimer += dt;

        if (walkTimer >= WALK_DURATION) {
            childState = CHILD_STATE_ROLLING;
            rollTimer = 0;
            rollSpeed = CHILD_INITIAL_ROLL;
            velocityX = (velocityX >= 0) ?
                rollSpeed : -rollSpeed;
        }
    }
    else if (childState == CHILD_STATE_ROLLING) {
        x += velocityX * dt;
        rollTimer += dt;

        ballAngle += abs(velocityX) * dt * 0.5f;
        if (ballAngle > 360.0f) ballAngle -= 360.0f;

        speedUpTimer += dt;
        if (speedUpTimer >= SPEEDUP_INTERVAL) {
            speedUpTimer = 0;
            if (velocityX > 0) {
                velocityX += CHILD_SPEEDUP;
                if (velocityX > CHILD_MAX_ROLL)
                    velocityX = CHILD_MAX_ROLL;
            }
            else {
                velocityX -= CHILD_SPEEDUP;
                if (velocityX < -CHILD_MAX_ROLL)
                    velocityX = -CHILD_MAX_ROLL;
            }
        }

        if (x < 0) { x = 0;    velocityX = abs(velocityX); }
        if (x > 745) { x = 745; velocityX = -abs(velocityX); }

        if (rollTimer >= ROLL_DURATION) {
            childState = CHILD_STATE_RESTING;
            restTimer = 0;
            velocityX = 0;
            rollCount++;

            rollSpeed = CHILD_INITIAL_ROLL +
                rollCount * 40.0f;
            if (rollSpeed > CHILD_MAX_ROLL)
                rollSpeed = CHILD_MAX_ROLL;
        }
    }
    else if (childState == CHILD_STATE_RESTING) {
        restTimer += dt;
        velocityX = 0;

        float rd = REST_DURATION - rollCount * 0.1f;
        if (rd < 0.3f) rd = 0.3f;

        if (restTimer >= rd) {
            childState = CHILD_STATE_ROLLING;
            rollTimer = 0;
            speedUpTimer = 0;
            velocityX = (x < 600) ?
                rollSpeed : -rollSpeed;
        }
    }

    y += velocityY * dt;
    if (y > 850) active = false;

    handlePlatformCollision(platforms,
        platformCount, cd);
    updateHitBox();

    animTimer += dt;
    if (childState == CHILD_STATE_WALKING) {
        if (animTimer >= 0.15f) {
            animTimer = 0;
            animFrame = (animFrame + 1) % 4;
        }
    }
    else if (childState == CHILD_STATE_ROLLING) {
        float spd = 0.15f -
            (abs(velocityX) / CHILD_MAX_ROLL) * 0.1f;
        if (spd < 0.05f) spd = 0.05f;
        if (animTimer >= spd) {
            animTimer = 0;
            animFrame = (animFrame + 1) % 3;
        }
    }
}

void MogeraChild::applyGravity(float dt) {
    if (!onGround) {
        velocityY += CHILD_GRAVITY * dt;
        if (velocityY > 500.0f) velocityY = 500.0f;
    }
}

void MogeraChild::handlePlatformCollision(
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
            if (childState == CHILD_STATE_ROLLING ||
                childState == CHILD_STATE_SNOW_ROLLING)
                velocityX = abs(velocityX);
            else
                velocityX = -velocityX;
        }
        else if (cd.hitsFromRight(hitBox, platBox)) {
            x = platBox.left + platBox.width;
            if (childState == CHILD_STATE_ROLLING ||
                childState == CHILD_STATE_SNOW_ROLLING)
                velocityX = -abs(velocityX);
            else
                velocityX = -velocityX;
        }
    }
}

void MogeraChild::updateHitBox() {
    hitBox = FloatRect(x, y, 40, 45);
}

void MogeraChild::draw(RenderWindow& window,
    bool showHitBox) {
    if (!active) return;

    sprite.setColor(Color(255, 255, 255, 255));

    switch (childState) {
    case CHILD_STATE_WALKING:
        setWalkFrame(animFrame % 4);
        window.draw(sprite);
        break;

    case CHILD_STATE_ROLLING:
        setBallFrame(animFrame % 3);
        window.draw(sprite);
        break;

    case CHILD_STATE_RESTING:
        ballAngle = 0;
        setBallFrame(0);
        window.draw(sprite);
        break;

    case CHILD_STATE_SNOW_COATED:
    case CHILD_STATE_SNOW_ROLLING:

        drawSnowSprite(window);
        break;

    case CHILD_STATE_DYING:
    {
        int flash = (int)(deathTimer / 0.08f) % 2;
        sprite.setColor(flash == 0 ?
            Color(255, 100, 100, 200) :
            Color(255, 255, 100, 150));
        setWalkFrame(animFrame % 4);
        window.draw(sprite);
        break;
    }
    }

    if (showHitBox &&
        childState != CHILD_STATE_DYING) {
        RectangleShape debug;
        debug.setPosition(hitBox.left, hitBox.top);
        debug.setSize(Vector2f(
            hitBox.width, hitBox.height));
        debug.setFillColor(Color::Transparent);
        debug.setOutlineColor(Color::Red);
        debug.setOutlineThickness(1.0f);
        window.draw(debug);
    }
}

void MogeraChild::kill() {
    if (childState == CHILD_STATE_DYING) return;
    childState = CHILD_STATE_DYING;
    deathTimer = 0;
    velocityY = -200.0f;
}

bool MogeraChild::isActive() const { return active; }
bool MogeraChild::isDying()  const {
    return childState == CHILD_STATE_DYING;
}
bool MogeraChild::isSnowCoated() const {
    return childState == CHILD_STATE_SNOW_COATED;
}
bool MogeraChild::isSnowRolling() const {
    return childState == CHILD_STATE_SNOW_ROLLING;
}
int  MogeraChild::getState()   const { return childState; }
FloatRect MogeraChild::getHitBox() const { return hitBox; }