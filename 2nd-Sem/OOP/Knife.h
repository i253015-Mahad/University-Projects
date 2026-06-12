#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Knife {
public:
    Knife(float startX, float startY,
        float targetX, float targetY);

    void update(float dt);
    void draw(RenderWindow& window, bool showHitBox);
    void killKnife();

    bool      isActive()  const;
    FloatRect getHitBox() const;

private:
    float x, y;
    float velocityX, velocityY;
    bool  active;
    float lifetime;
    float angle;

    Texture   texture;
    Sprite    sprite;
    FloatRect hitBox;

    void updateHitBox();
    void loadKnifeTexture();
};