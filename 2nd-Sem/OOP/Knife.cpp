#include "Knife.h"
#include <cmath>

const float KNIFE_SPEED = 350.0f;
const float KNIFE_LIFETIME = 3.0f;

Knife::Knife(float startX, float startY,
    float targetX, float targetY) {
    x = startX;
    y = startY;
    active = true;
    lifetime = 0;
    angle = 0;

    float dx = targetX - startX;
    float dy = targetY - startY;
    float len = sqrt(dx * dx + dy * dy);

    if (len > 0) {
        velocityX = (dx / len) * KNIFE_SPEED;
        velocityY = (dy / len) * KNIFE_SPEED;
        angle = atan2(dy, dx) * 180.0f / 3.14159f;
    }
    else {
        velocityX = KNIFE_SPEED;
        velocityY = 0;
        angle = 0;
    }

    loadKnifeTexture();
    updateHitBox();
}

void Knife::loadKnifeTexture() {
    if (!texture.loadFromFile("assets/Images/Tornado_Red.png"))
        return;

    sprite.setTexture(texture);

    sprite.setTextureRect(IntRect(497, 890, 63, 27));

    float scale = 20.0f / 27.0f;
    sprite.setScale(scale, scale);
    sprite.setOrigin(63 / 2.0f, 27 / 2.0f);
}

void Knife::update(float dt) {
    if (!active) return;

    x += velocityX * dt;
    y += velocityY * dt;

    lifetime += dt;

    if (lifetime > KNIFE_LIFETIME)
        active = false;

    if (x < -20 || x > 820 || y < -20 || y > 620)
        active = false;

    updateHitBox();
}

void Knife::updateHitBox() {
    hitBox = FloatRect(x - 10, y - 5, 20, 10);
}

void Knife::draw(RenderWindow& window, bool showHitBox) {
    if (!active) return;

    sprite.setPosition(x, y);
    sprite.setRotation(angle);
    window.draw(sprite);

    if (showHitBox) {
        RectangleShape debug;
        debug.setPosition(hitBox.left, hitBox.top);
        debug.setSize(Vector2f(hitBox.width, hitBox.height));
        debug.setFillColor(Color::Transparent);
        debug.setOutlineColor(Color::Yellow);
        debug.setOutlineThickness(1.0f);
        window.draw(debug);
    }
}

void      Knife::killKnife() { active = false; }
bool      Knife::isActive()  const { return active; }
FloatRect Knife::getHitBox() const { return hitBox; }