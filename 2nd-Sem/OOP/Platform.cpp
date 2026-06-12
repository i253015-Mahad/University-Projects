#include "Platform.h"

Platform::Platform(float x, float y,
    float width, float height) {
    shape.setPosition(x, y);
    shape.setSize(Vector2f(width, height));

    shape.setFillColor(Color::Transparent);
    shape.setOutlineColor(Color(255, 0, 255)); 
    shape.setOutlineThickness(1.0f);

    hitBox = FloatRect(x, y, width, height);
}

void Platform::draw(RenderWindow& window,
    bool showHitBox) {
 
    if (showHitBox)
        window.draw(shape);
}

FloatRect Platform::getHitBox() const {
    return hitBox;
}