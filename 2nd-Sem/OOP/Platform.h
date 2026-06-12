#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

const int MAX_PLATFORMS = 20;

class Platform {
public:
    Platform(float x, float y, float width, float height);

    void draw(RenderWindow& window, bool showHitBox);

    FloatRect getHitBox() const;

private:
    RectangleShape shape;
    FloatRect hitBox;
};
