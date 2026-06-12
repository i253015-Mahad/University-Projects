#include "Player.h"

const float GRAVITY = 800.0f;
const float JUMP_FORCE = -450.0f;
const float MOVE_SPEED = 200.0f;
const float SCREEN_WIDTH = 800.0f;
const float SCREEN_HEIGHT = 600.0f;
const float TARGET_HEIGHT = 75.0f;  

Player::Player(float startX, float startY, int pNumber) {
    x = startX;
    y = startY;
    this->startX = startX;
    this->startY = startY;
    velocityX = 0;
    velocityY = 0;
    onGround = false;
    lives = 22;
    playerNumber = pNumber;
    alive = true;
    facingRight = true;
    animTimer = 0;
    animFrame = 0;
    playerIndex = 1;
    isThrowing = false;
    throwAnimTimer = 0;
    isInvincible = false;
    hitTimer = 0;
    flashTimer = 0;
    respawning = false;
    respawnTimer = 0;
    updateHitBox();
}

void Player::loadTexture(string imagePath, int pIndex) {
    playerIndex = pIndex;

    if (!texture.loadFromFile(imagePath))
        return;

    sprite.setTexture(texture);

    if (playerIndex == 1) {
        frames[0] = { 81,   76,   272, 263 };
        frames[1] = { 383,  68,   237, 255 };
        frames[2] = { 688,  68,   252, 255 };
        frames[3] = { 990,  68,   246, 255 };
        frames[4] = { 1275, 59,   253, 264 };
        frames[5] = { 385,  1586, 240, 264 };
        frames[6] = { 655,  1586, 275, 264 };
    }
    else {
        frames[0] = { 6,   1,   79, 77 };
        frames[1] = { 88,  3,   71, 72 };
        frames[2] = { 172, 1,   87, 74 };
        frames[3] = { 254, 1,   76, 74 };
        frames[4] = { 335, 1,   75, 74 };
        frames[5] = { 90,  423, 70, 72 };
        frames[6] = { 162, 423, 81, 72 };
    }

    setFrame(0);
}

void Player::setFrame(int frameIndex) {
    FrameData& f = frames[frameIndex];
    sprite.setTextureRect(IntRect(f.x, f.y, f.w, f.h));

    float scale = TARGET_HEIGHT / (float)f.h;
    bool  flip = facingRight;

    if (!flip) {
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

void Player::startThrowAnimation() {
    isThrowing = true;
    throwAnimTimer = 0;
}

void Player::handleInput(InputManager& input, int leftAction,
    int rightAction, int jumpAction) {

    if (respawning) return;

    velocityX = 0;

    if (input.isHeld(leftAction)) {
        velocityX = -MOVE_SPEED;
        facingRight = false;
    }
    if (input.isHeld(rightAction)) {
        velocityX = MOVE_SPEED;
        facingRight = true;
    }
    if (input.isJustPressed(jumpAction) && onGround) {
        velocityY = JUMP_FORCE;
        onGround = false;
    }
}

void Player::update(float dt, Platform* platforms[],
    int platformCount, CollisionDetector& cd) {

    if (!alive) return;

    if (respawning) {
        respawnTimer += dt;

        flashTimer += dt;
        int flashFrame = (int)(flashTimer / 0.1f) % 2;
        sprite.setColor(flashFrame == 0 ?
            Color(255, 255, 255, 60) :
            Color(255, 255, 255, 255));

        if (respawnTimer >= 1.5f) {
            x = startX;
            y = startY;
            velocityX = 0;
            velocityY = 0;
            respawning = false;
            respawnTimer = 0;
            flashTimer = 0;
        }
        else {
            setFrame(0);
            return;
        }
    }


    if (isInvincible) {
        hitTimer += dt;
        flashTimer += dt;

        int flashFrame = (int)(flashTimer / 0.1f) % 2;
        sprite.setColor(flashFrame == 0 ?
            Color(255, 255, 255, 80) :
            Color(255, 255, 255, 255));

        if (hitTimer >= 2.0f) {
            isInvincible = false;
            hitTimer = 0;
            flashTimer = 0;
            sprite.setColor(Color(255, 255, 255, 255));
        }
    }

    applyGravity(dt);

    x += velocityX * dt;
    y += velocityY * dt;

    handlePlatformCollision(platforms, platformCount, cd);
    handleScreenWrap();
    updateHitBox();
    updateAnimation(dt);
}

void Player::applyGravity(float dt) {
    if (!onGround) {
        velocityY += GRAVITY * dt;
        if (velocityY > 400.0f)
            velocityY = 400.0f;
    }
}

void Player::handlePlatformCollision(Platform* platforms[],
    int platformCount, CollisionDetector& cd) {
    onGround = false;

    for (int i = 0; i < platformCount; i++) {
        FloatRect platBox = platforms[i]->getHitBox();

        if (cd.isLandingOn(hitBox, platBox, velocityY)) {
            y = platBox.top - hitBox.height;
            velocityY = 0;
            onGround = true;
            updateHitBox();
        }
        else if (cd.hitsFromLeft(hitBox, platBox)) {
            x = platBox.left - hitBox.width - 10.0f;
            velocityX = 0;
        }
        else if (cd.hitsFromRight(hitBox, platBox)) {
            x = platBox.left + platBox.width - 10.0f;
            velocityX = 0;
        }
    }
}

void Player::handleScreenWrap() {
    if (x < 0) {
        x = 0;
        velocityX = 0;
    }
    if (x > SCREEN_WIDTH - 50) {
        x = SCREEN_WIDTH - 50;
        velocityX = 0;
    }
    if (y >= SCREEN_HEIGHT - 75) {  
        y = SCREEN_HEIGHT - 75;  
        velocityY = 0;
        onGround = true;
    }
}

void Player::updateHitBox() {
    hitBox = FloatRect(x + 5, y + 5, 45, 75);
}

void Player::updateAnimation(float dt) {
    if (isThrowing) {
        throwAnimTimer += dt;
        if (throwAnimTimer < 0.1f)
            setFrame(5);
        else if (throwAnimTimer < 0.2f)
            setFrame(6);
        else
            isThrowing = false;
        return;
    }

    animTimer += dt;

    if (animTimer >= 0.12f) {
        animTimer = 0;

        if (!onGround)
            animFrame = 4;
        else if (velocityX != 0) {
            if (animFrame < 1 || animFrame > 3)
                animFrame = 1;
            else {
                animFrame++;
                if (animFrame > 3) animFrame = 1;
            }
        }
        else
            animFrame = 0;
    }

    setFrame(animFrame);
}

void Player::draw(RenderWindow& window, bool showHitBox) {
    if (!alive) return;
    if (respawning && respawnTimer < 0.0f) return;

    window.draw(sprite);

    if (showHitBox) {
        RectangleShape debug;
        debug.setPosition(hitBox.left, hitBox.top);
        debug.setSize(Vector2f(hitBox.width, hitBox.height));
        debug.setFillColor(Color::Transparent);
        debug.setOutlineColor(Color::Green);
        debug.setOutlineThickness(1.0f);
        window.draw(debug);
    }
}

void Player::loseLife() {
    if (isInvincible) return;
    if (respawning)   return;

    lives--;

    if (lives <= 0) {
        alive = false;
        return;
    }

    isInvincible = true;
    hitTimer = 0;
    flashTimer = 0;
    respawning = true;
    respawnTimer = 0;
    velocityX = 0;
    velocityY = 0;
}

void Player::resetPosition()
{
        x = startX;
        y = startY;
        velocityX = 0;
        velocityY = 0;
        onGround = false;
}

FloatRect Player::getHitBox()       const { return hitBox; }
float     Player::getX()            const { return x; }
float     Player::getY()            const { return y; }
bool      Player::isAlive()         const { return alive; }
int       Player::getLives()        const { return lives; }
bool      Player::isFacingRight()   const { return facingRight; }
bool      Player::getIsInvincible() const { return isInvincible; }