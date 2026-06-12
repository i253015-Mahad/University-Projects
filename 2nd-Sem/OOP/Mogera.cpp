#include "Mogera.h"
#include <cstdlib>
#include <cmath>

const float SPAWN_INTERVAL = 5.0f;
const float MOGERA_HEIGHT = 200.0f;
const float MOGERA_GRAVITY = 400.0f;
const float MOGERA_JUMP = -600.0f;
const float DEATH_DURATION = 4.0f;

Mogera::Mogera(float startX, float startY) {
    x = 550;
    y = 380;
    velocityY = 0;
    onGround = false;
    jumpTimer = 0;
    health = MOGERA_MAX_HEALTH;
    defeated = false;
    deathTimer = 0;
    spawnTimer = 0;
    spawnInterval = SPAWN_INTERVAL;
    animTimer = 0;
    animFrame = 0;
    isHit = false;
    hitFlashTimer = 0;
    childCount = 0;

    for (int i = 0; i < MAX_MOGERA_CHILDREN; i++)
        children[i] = nullptr;

    for (int i = 0; i < 4; i++)
        frames[i] = { 0, 0, 1, 1 };

    healthBarBg.setSize(Vector2f(300, 28));
    healthBarBg.setFillColor(Color(40, 0, 0));
    healthBarBg.setOutlineColor(Color::Black);
    healthBarBg.setOutlineThickness(3.0f);
    healthBarBg.setPosition(250, 18);

    healthBarFill.setSize(Vector2f(300, 28));
    healthBarFill.setFillColor(Color(50, 220, 50));
    healthBarFill.setOutlineColor(Color::Black);
    healthBarFill.setOutlineThickness(1.0f);
    healthBarFill.setPosition(250, 18);

    updateHitBox();
}

Mogera::~Mogera() {
    for (int i = 0; i < MAX_MOGERA_CHILDREN; i++) {
        delete children[i];
        children[i] = nullptr;
    }
}

void Mogera::loadTexture(string imagePath) {
    if (!texture.loadFromFile(imagePath)) return;

    sprite.setTexture(texture);

    frames[0] = { 40,   11,  530, 548 };
    frames[1] = { 590,  6,   536, 593 };
    frames[2] = { 1164, 7,   535, 781 };
    frames[3] = { 851,  888, 811, 308 };

    setFrame(0);
    sharedSnowTexture.loadFromFile("assets/Images/Nick.png");
}

void Mogera::setFrame(int index) {
    MogeraFrame& f = frames[index];
    sprite.setTextureRect(IntRect(f.x, f.y, f.w, f.h));

    if (index == 3) {
        float scaleX = 280.0f / (float)f.w;
        float scaleY = 80.0f / (float)f.h;
        sprite.setScale(scaleX, scaleY);
        sprite.setOrigin(0, 0);
        sprite.setPosition(x, y + 100);
    }
    else {
        float scale = MOGERA_HEIGHT / (float)f.h;
        sprite.setScale(scale, scale);
        sprite.setOrigin(0, 0);
        sprite.setPosition(x, y);
    }

    if (isHit)
        sprite.setColor(Color(255, 100, 100, 200));
    else
        sprite.setColor(Color(255, 255, 255, 255));
}

void Mogera::updateHitBox() {
    hitBox = FloatRect(x + 10, y + 10, 160, 140);
}

void Mogera::applyHit() {
    if (defeated) return;

    health--;
    isHit = true;
    hitFlashTimer = 0;

    if (health <= 0) {
        defeated = true;
        deathTimer = 0;
        animFrame = 3;
    }
}

void Mogera::spawnChild() {
    for (int i = 0; i < MAX_MOGERA_CHILDREN; i++) {
        if (children[i] == nullptr) {
            children[i] = new MogeraChild(x + 20, y + 60, false, &sharedSnowTexture);
            children[i]->loadTexture(
                "assets/Images/Mogera.png");
            childCount++;
            return;
        }
    }
}

void Mogera::updateChildren(float dt,
    Platform* platforms[], int platformCount,
    CollisionDetector& cd) {
    for (int i = 0; i < MAX_MOGERA_CHILDREN; i++) {
        if (children[i] != nullptr) {
            children[i]->update(dt, platforms,
                platformCount, cd);
            if (!children[i]->isActive()) {
                delete children[i];
                children[i] = nullptr;
                childCount--;
            }
        }
    }
}

bool Mogera::checkChildHit(FloatRect playerHitBox,
    CollisionDetector& cd) {
    for (int i = 0; i < MAX_MOGERA_CHILDREN; i++) {
        if (children[i] == nullptr)        continue;
        if (!children[i]->isActive())      continue;
        if (children[i]->isDying())        continue;
        if (children[i]->isSnowCoated())   continue;
        if (children[i]->isSnowRolling())  continue;

        if (cd.overlaps(children[i]->getHitBox(),
            playerHitBox))
            return true;
    }
    return false;
}

bool Mogera::checkSnowballHit(FloatRect snowballBox,
    CollisionDetector& cd) {
    bool hit = false;

    if (!defeated &&
        cd.overlaps(snowballBox, hitBox)) {
        applyHit();
        hit = true;
    }

    for (int i = 0; i < MAX_MOGERA_CHILDREN; i++) {
        if (children[i] == nullptr)   continue;
        if (!children[i]->isActive()) continue;
        if (children[i]->isDying())   continue;

        if (cd.overlaps(snowballBox,
            children[i]->getHitBox())) {
            children[i]->applySnowHit();
            hit = true;
        }
    }
    return hit;
}

void Mogera::update(float dt, Platform* platforms[],
    int platformCount, CollisionDetector& cd) {

    if (defeated) {
        deathTimer += dt;
        updateChildren(dt, platforms, platformCount, cd);
        return;
    }

    if (isHit) {
        hitFlashTimer += dt;
        if (hitFlashTimer >= 0.3f) {
            isHit = false;
            hitFlashTimer = 0;
        }
    }

    velocityY += MOGERA_GRAVITY * dt;
    y += velocityY * dt;

    if (y >= 380) {
        y = 380;
        velocityY = MOGERA_JUMP;
    }

    if (y < 30) {
        y = 30;
        if (velocityY < 0) velocityY = 0;
    }

    x = 550;

    animTimer += dt;
    if (animTimer >= 0.08f) {
        animTimer = 0;

        if (velocityY < -200.0f)
            animFrame = 0;
        else if (velocityY < 0)
            animFrame = 1;
        else
            animFrame = 2;
    }

    spawnTimer += dt;
    if (spawnTimer >= spawnInterval && y > 300) {
        spawnTimer = 0;
        spawnChild();
        spawnChild();

        spawnInterval = SPAWN_INTERVAL -
            (MOGERA_MAX_HEALTH - health) * 0.3f;
        if (spawnInterval < 2.0f)
            spawnInterval = 2.0f;
    }

    updateChildren(dt, platforms, platformCount, cd);
    updateHitBox();
}

void Mogera::drawHealthBar(RenderWindow& window) {
    float pct = (float)health / MOGERA_MAX_HEALTH;
    healthBarFill.setSize(Vector2f(300.0f * pct, 28));

    if (pct > 0.5f)       healthBarFill.setFillColor(Color(50, 220, 50));
    else if (pct > 0.25f) healthBarFill.setFillColor(Color(255, 200, 0));
    else                  healthBarFill.setFillColor(Color(220, 40, 40));

    window.draw(healthBarBg);
    window.draw(healthBarFill);
}

void Mogera::draw(RenderWindow& window, bool showHitBox) {
    if (defeated) {
        if (deathTimer < DEATH_DURATION) {
            int flash = (int)(deathTimer / 0.15f) % 2;
            sprite.setColor(flash == 0 ?
                Color(255, 255, 255, 255) :
                Color(255, 100, 100, 180));
            setFrame(3);
            window.draw(sprite);
        }

        for (int i = 0; i < MAX_MOGERA_CHILDREN; i++) {
            if (children[i] != nullptr)
                children[i]->draw(window, showHitBox);
        }
        return;
    }

    setFrame(animFrame);
    window.draw(sprite);

    for (int i = 0; i < MAX_MOGERA_CHILDREN; i++) {
        if (children[i] != nullptr)
            children[i]->draw(window, showHitBox);
    }

    drawHealthBar(window);

    if (showHitBox) {
        RectangleShape debug;
        debug.setPosition(hitBox.left, hitBox.top);
        debug.setSize(Vector2f(hitBox.width, hitBox.height));
        debug.setFillColor(Color::Transparent);
        debug.setOutlineColor(Color(255, 0, 255));
        debug.setOutlineThickness(2.0f);
        window.draw(debug);
    }
}

bool      Mogera::isDefeated()   const { return defeated; }
bool      Mogera::shouldRemove() const {
    return defeated && deathTimer > DEATH_DURATION;
}
FloatRect Mogera::getHitBox()    const { return hitBox; }
int       Mogera::getHealth()    const { return health; }

MogeraChild* Mogera::getChild(int index) const {
    if (index < 0 ||
        index >= MAX_MOGERA_CHILDREN) return nullptr;
    return children[index];
}