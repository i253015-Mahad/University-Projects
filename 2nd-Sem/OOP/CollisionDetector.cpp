#include "CollisionDetector.h"


bool CollisionDetector::overlaps(FloatRect a, FloatRect b) {
    return a.intersects(b);
}

bool CollisionDetector::isLandingOn(FloatRect moving, FloatRect platform,
    float velocityY) {
    if (velocityY < 0) return false;

    float movingBottom = moving.top + moving.height;
    float platformTop = platform.top;

    bool horizontalOverlap = (moving.left + moving.width > platform.left) &&
        (moving.left < platform.left + platform.width);

    bool verticalMatch = (movingBottom >= platformTop - 20.0f) &&
        (movingBottom <= platformTop + 30.0f);

    return horizontalOverlap && verticalMatch;
}

bool CollisionDetector::hitsFromLeft(FloatRect moving, FloatRect wall) {
    float movingRight = moving.left + moving.width;
    float movingBottom = moving.top + moving.height;
    float movingCenterY = moving.top + moving.height / 2;

    bool horizontal = (movingRight >= wall.left) &&
        (moving.left < wall.left);
    bool vertical = (movingCenterY > wall.top) &&
        (movingCenterY < wall.top + wall.height);

    return horizontal && vertical;
}

bool CollisionDetector::hitsFromRight(FloatRect moving, FloatRect wall) {
    float wallRight = wall.left + wall.width;
    float movingCenterY = moving.top + moving.height / 2;

    bool horizontal = (moving.left <= wallRight) &&
        (moving.left + moving.width > wallRight);
    bool vertical = (movingCenterY > wall.top) &&
        (movingCenterY < wall.top + wall.height);

    return horizontal && vertical;
}