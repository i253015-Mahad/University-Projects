#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;


class CollisionDetector {
public:
    // Check if two rectangles overlap
    bool overlaps(FloatRect a, FloatRect b);

    // Check if player/enemy is landing on top of a platform
    bool isLandingOn(FloatRect moving, FloatRect platform, float velocityY);

    // Check if player/enemy hits left or right side of another rect
    bool hitsFromLeft(FloatRect moving, FloatRect wall);
    bool hitsFromRight(FloatRect moving, FloatRect wall);
};