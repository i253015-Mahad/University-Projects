#include "Gamakichi.h"
#include <cmath>
#include <cstdlib>

const float GAMA_HEIGHT = 180.0f;
const float FIRE_INTERVAL = 4.0f;
const float GAMA_MOVE_SPEED = 80.0f;
const float DEATH_DURATION = 4.0f;
const float GROUND_PAUSE_TIME = 1.5f;
const float TOP_LIMIT = 30.0f;
const float GROUND_LIMIT = 350.0f;

Gamakichi::Gamakichi(float startX, float startY) {
    x = startX;
    y = startY;
    bobOffset = 0;
    bobTimer = 0;
    moveVelocityY = GAMA_MOVE_SPEED;
    atGround = false;
    groundPauseTimer = 0;
    groundPauseDuration = GROUND_PAUSE_TIME;
    topLimit = TOP_LIMIT;
    groundLimit = GROUND_LIMIT;
    health = GAMA_MAX_HEALTH;
    defeated = false;
    deathTimer = 0;
    fireTimer = 0;
    fireInterval = FIRE_INTERVAL;
    firePhase = 0;
    isHit = false;
    hitFlashTimer = 0;
    animTimer = 0;
    animFrame = 0;
    bombCount = 0;

    for (int i = 0; i < MAX_GAMA_BOMBS; i++)
        bombs[i] = nullptr;

    for (int i = 0; i < 3; i++) {
        gamaFrames[i].x = 0;
        gamaFrames[i].y = 0;
        gamaFrames[i].w = 1;
        gamaFrames[i].h = 1;
    }

    healthBarBg.setSize(Vector2f(400, 32));
    healthBarBg.setFillColor(Color(40, 0, 0));
    healthBarBg.setOutlineColor(Color::Black);
    healthBarBg.setOutlineThickness(3.0f);
    healthBarBg.setPosition(200, 16);

    healthBarFill.setSize(Vector2f(400, 32));
    healthBarFill.setFillColor(Color(50, 220, 50));
    healthBarFill.setOutlineColor(Color::Black);
    healthBarFill.setOutlineThickness(1.0f);
    healthBarFill.setPosition(200, 16);

    updateHitBox();
}

Gamakichi::~Gamakichi() {
    for (int i = 0; i < MAX_GAMA_BOMBS; i++) {
        delete bombs[i];
        bombs[i] = nullptr;
    }
}

void Gamakichi::loadTexture(string imagePath) {
    if (!texture.loadFromFile(imagePath)) return;
    sprite.setTexture(texture);

    gamaFrames[0].x = 268; gamaFrames[0].y = 63;
    gamaFrames[0].w = 170; gamaFrames[0].h = 87;

    gamaFrames[1].x = 451; gamaFrames[1].y = 63;
    gamaFrames[1].w = 167; gamaFrames[1].h = 87;

    gamaFrames[2].x = 22;  gamaFrames[2].y = 31;
    gamaFrames[2].w = 228; gamaFrames[2].h = 119;

    setFrame(0);

    sharedSnowTexture.loadFromFile("assets/Images/Nick.png");
}

void Gamakichi::setFrame(int index) {
    GamaFrame& f = gamaFrames[index];
    sprite.setTextureRect(IntRect(f.x, f.y, f.w, f.h));

    float scale = GAMA_HEIGHT / (float)f.h;
    sprite.setScale(scale, scale);
    sprite.setOrigin(0, 0);
    sprite.setPosition(x, y);

    if (isHit)
        sprite.setColor(Color(255, 100, 100, 200));
    else
        sprite.setColor(Color(255, 255, 255, 255));
}

void Gamakichi::updateHitBox() {
    hitBox = FloatRect(x + 10, y + 10, 220, 150);
}

void Gamakichi::applyHit() {
    if (defeated) return;

    health--;
    isHit = true;
    hitFlashTimer = 0;

    if (health <= 0) {
        defeated = true;
        deathTimer = 0;
    }
}

void Gamakichi::fireBombs() {
    float dirX[4][6] = {
        { 1,-1, 1,-1, 0, 0},
        { 1,-1, 0, 0, 0, 0},
        { 1,-1, 1,-1, 1,-1},
        { 0, 1,-1, 0, 0, 0},
    };
    float dirY[4][6] = {
        { 1, 1,-1,-1, 0, 0},
        { 0, 0, 0, 0, 0, 0},
        { 0, 0, 1, 1,-1,-1},
        { 1, 1, 1, 0, 0, 0},
    };

    int counts[4] = { 4, 2, 6, 3 };
    int phase = firePhase % 4;
    int count = counts[phase];

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < MAX_GAMA_BOMBS; j++) {
            if (bombs[j] == nullptr) {
                bombs[j] = new GamakichiBomb(x + 80, y + 80, dirX[phase][i], dirY[phase][i], &sharedSnowTexture);
                bombs[j]->loadTexture("assets/Images/Gamakichi.png");
                bombCount++;
                break;
            }
        }
    }

    firePhase++;
}

void Gamakichi::checkBombRollingHit(
    CollisionDetector& cd) {
    for (int i = 0; i < MAX_GAMA_BOMBS; i++) {
        if (bombs[i] == nullptr)    continue;
        if (!bombs[i]->isRolling()) continue;

        if (!defeated &&
            cd.overlaps(bombs[i]->getHitBox(),
                hitBox)) {
            applyHit();
            bombs[i]->explode();
        }

        for (int j = 0; j < MAX_GAMA_BOMBS; j++) {
            if (i == j) continue;
            if (bombs[j] == nullptr)     continue;
            if (!bombs[j]->isActive())   continue;
            if (bombs[j]->isExploding()) continue;
            if (bombs[j]->isRolling())   continue;

            if (cd.overlaps(bombs[i]->getHitBox(),
                bombs[j]->getHitBox()))
                bombs[j]->explode();
        }
    }
}

bool Gamakichi::checkSnowballHit(FloatRect snowballBox,
    CollisionDetector& cd) {
    bool hit = false;

    if (!defeated &&
        cd.overlaps(snowballBox, hitBox)) {
        applyHit();
        hit = true;
    }

    for (int i = 0; i < MAX_GAMA_BOMBS; i++) {
        if (bombs[i] == nullptr)     continue;
        if (!bombs[i]->isActive())   continue;
        if (bombs[i]->isCoated())    continue;
        if (bombs[i]->isExploding()) continue;

        if (cd.overlaps(snowballBox,
            bombs[i]->getHitBox()))
            bombs[i]->applySnowHit();
    }

    return hit;
}

bool Gamakichi::checkBombPlayerHit(
    FloatRect playerBox, CollisionDetector& cd) {
    for (int i = 0; i < MAX_GAMA_BOMBS; i++) {
        if (bombs[i] == nullptr)     continue;
        if (!bombs[i]->isActive())   continue;
        if (bombs[i]->isCoated())    continue;
        if (bombs[i]->isExploding()) continue;

        if (cd.overlaps(bombs[i]->getHitBox(),
            playerBox))
            return true;
    }
    return false;
}

void Gamakichi::checkPlayerKicksBomb(
    FloatRect playerBox, bool playerFacingRight,
    CollisionDetector& cd) {
    for (int i = 0; i < MAX_GAMA_BOMBS; i++) {
        if (bombs[i] == nullptr)   continue;
        if (!bombs[i]->isActive()) continue;
        if (!bombs[i]->isCoated()) continue;

        if (cd.overlaps(playerBox,
            bombs[i]->getHitBox()))
            bombs[i]->startRolling(playerFacingRight);
    }
}

GamakichiBomb* Gamakichi::getBomb(int index) const {
    if (index < 0 || index >= MAX_GAMA_BOMBS)
        return nullptr;
    return bombs[index];
}

void Gamakichi::updateBombs(float dt,
    Platform* platforms[], int platformCount,
    CollisionDetector& cd) {
    for (int i = 0; i < MAX_GAMA_BOMBS; i++) {
        if (bombs[i] != nullptr) {
            bombs[i]->update(dt, platforms,
                platformCount, cd);
            if (!bombs[i]->isActive()) {
                delete bombs[i];
                bombs[i] = nullptr;
                bombCount--;
            }
        }
    }
}

void Gamakichi::update(float dt,
    Platform* platforms[], int platformCount,
    CollisionDetector& cd) {

    if (defeated) {
        deathTimer += dt;
        updateBombs(dt, platforms, platformCount, cd);
        return;
    }

    if (isHit) {
        hitFlashTimer += dt;
        if (hitFlashTimer >= 0.3f) {
            isHit = false;
            hitFlashTimer = 0;
        }
    }

    if (atGround) {
        groundPauseTimer += dt;
        if (groundPauseTimer >= groundPauseDuration) {
            atGround = false;
            groundPauseTimer = 0;
            moveVelocityY = -GAMA_MOVE_SPEED;
        }
    }
    else {
        y += moveVelocityY * dt;

        if (y >= groundLimit) {
            y = groundLimit;
            atGround = true;
            moveVelocityY = 0;
            animFrame = 2;
            fireBombs();

            groundPauseDuration = GROUND_PAUSE_TIME -
                (GAMA_MAX_HEALTH - health) * 0.05f;
            if (groundPauseDuration < 0.5f)
                groundPauseDuration = 0.5f;
        }

        if (y <= topLimit) {
            y = topLimit;
            moveVelocityY = GAMA_MOVE_SPEED;
        }
    }

    animTimer += dt;
    if (animTimer >= 0.4f) {
        animTimer = 0;
        if (animFrame == 2)
            animFrame = 1;
        else if (animFrame == 1)
            animFrame = 0;
    }

    checkBombRollingHit(cd);
    updateBombs(dt, platforms, platformCount, cd);
    updateHitBox();
}

void Gamakichi::drawHealthBar(RenderWindow& window) {
    float pct = (float)health / GAMA_MAX_HEALTH;
    healthBarFill.setSize(Vector2f(400.0f * pct, 32));

    if (pct > 0.5f)       healthBarFill.setFillColor(Color(50, 220, 50));
    else if (pct > 0.25f) healthBarFill.setFillColor(Color(255, 200, 0));
    else                  healthBarFill.setFillColor(Color(220, 40, 40));

    window.draw(healthBarBg);
    window.draw(healthBarFill);
}

void Gamakichi::draw(RenderWindow& window,
    bool showHitBox) {
    if (defeated) {
        if (deathTimer < DEATH_DURATION) {
            int flash = (int)(deathTimer / 0.15f) % 2;
            sprite.setColor(flash == 0 ?
                Color(255, 255, 255, 255) :
                Color(255, 100, 100, 180));
            setFrame(0);
            window.draw(sprite);
        }
        for (int i = 0; i < MAX_GAMA_BOMBS; i++)
            if (bombs[i] != nullptr)
                bombs[i]->draw(window, showHitBox);
        return;
    }

    setFrame(animFrame);
    window.draw(sprite);

    for (int i = 0; i < MAX_GAMA_BOMBS; i++)
        if (bombs[i] != nullptr)
            bombs[i]->draw(window, showHitBox);

    drawHealthBar(window);

    if (showHitBox) {
        RectangleShape debug;
        debug.setPosition(hitBox.left, hitBox.top);
        debug.setSize(Vector2f(
            hitBox.width, hitBox.height));
        debug.setFillColor(Color::Transparent);
        debug.setOutlineColor(Color(0, 255, 255));
        debug.setOutlineThickness(2.0f);
        window.draw(debug);
    }
}

bool      Gamakichi::isDefeated()   const { return defeated; }
bool      Gamakichi::shouldRemove() const {
    return defeated && deathTimer > DEATH_DURATION;
}
FloatRect Gamakichi::getHitBox()    const { return hitBox; }
int       Gamakichi::getHealth()    const { return health; }