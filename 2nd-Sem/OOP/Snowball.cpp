#include "Snowball.h"
#include "Tornado.h"

const float SNOWBALL_SPEED = 350.0f;
const float MAX_TRAVEL_TIME = 0.9f;   
const float INITIAL_UP = -50.0f; 
const float SNOWBALL_GRAVITY = 350.0f;  

Snowball::Snowball(float startX, float startY,
    bool goingRight, int owner) {
    x = startX;
    y = startY;
    ownerPlayer = owner;
    active = true;
    distanceTravelled = 0;

    velocityX = goingRight ? SNOWBALL_SPEED : -SNOWBALL_SPEED;

    velocityY = INITIAL_UP;

    shape.setRadius(8.0f);
    shape.setFillColor(Color::White);
    shape.setOutlineColor(Color(180, 180, 255));
    shape.setOutlineThickness(1.0f);

    updateHitBox();
}

void Snowball::update(float dt, Enemy* enemies[],
    int enemyCount, Platform* platforms[],
    int platformCount, CollisionDetector& cd) {
    if (!active) return;

    velocityY += SNOWBALL_GRAVITY * dt;

    x += velocityX * dt;
    y += velocityY * dt;

    distanceTravelled += dt;

    if (distanceTravelled > MAX_TRAVEL_TIME)
        active = false;

    if (y > 620)
        active = false;

    for (int i = 0; i < platformCount; i++) {
        if (platforms[i] == nullptr) continue;
        if (cd.overlaps(hitBox,
            platforms[i]->getHitBox())) {
            active = false;
            return;
        }
    }

    handleScreenWrap();
    updateHitBox();
    checkEnemyCollision(enemies, enemyCount, cd);
}

void Snowball::handleScreenWrap() {
    if (x < 0 || x + 16 > 800)
        active = false;
}

void Snowball::updateHitBox() {
    hitBox = FloatRect(x, y, 16, 16);
}

void Snowball::checkEnemyCollision(Enemy* enemies[],
    int enemyCount, CollisionDetector& cd) {
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i] == nullptr) continue;
        if (enemies[i]->isDefeated()) continue;

        Tornado* t = dynamic_cast<Tornado*>(enemies[i]);
        if (t != nullptr && t->isTornadoForm()) continue;

        if (cd.overlaps(hitBox,
            enemies[i]->getHitBox())) {
            enemies[i]->applySnowHit();
            active = false;
            return;
        }
    }
}

void Snowball::draw(RenderWindow& window,
    bool showHitBox) {
    if (!active) return;

    shape.setPosition(x, y);
    window.draw(shape);

    if (showHitBox) {
        RectangleShape debug;
        debug.setPosition(hitBox.left, hitBox.top);
        debug.setSize(Vector2f(hitBox.width,
            hitBox.height));
        debug.setFillColor(Color::Transparent);
        debug.setOutlineColor(Color::Yellow);
        debug.setOutlineThickness(1.0f);
        window.draw(debug);
    }
}

void      Snowball::deactivate() { active = false; }
bool      Snowball::isActive()   const { return active; }
FloatRect Snowball::getHitBox()  const { return hitBox; }