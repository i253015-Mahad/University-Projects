#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionDetector.h"
#include "Platform.h"
#include "MogeraChild.h"
using namespace sf;

const int MAX_MOGERA_CHILDREN = 5;
const int MOGERA_MAX_HEALTH = 40;

class Mogera {
public:
    Mogera(float startX, float startY);
    ~Mogera();

    void loadTexture(string imagePath);
    void update(float dt, Platform* platforms[],
        int platformCount, CollisionDetector& cd);
    void draw(RenderWindow& window, bool showHitBox);

    void      applyHit();
    bool      isDefeated()   const;
    bool      shouldRemove() const;
    FloatRect getHitBox()    const;
    int       getHealth()    const;
    MogeraChild* getChild(int index) const;

    bool checkChildHit(FloatRect playerHitBox, CollisionDetector& cd);
    bool checkSnowballHit(FloatRect snowballBox, CollisionDetector& cd);
private:
    float x, y;
    float velocityY;
    bool  onGround;
    float jumpTimer;
    int   health;
    bool  defeated;
    float deathTimer;

    float spawnTimer;
    float spawnInterval;

    Texture sharedSnowTexture;
    Texture texture;
    Sprite  sprite;
    float   animTimer;
    int     animFrame;
    bool    isHit;
    float   hitFlashTimer;

    MogeraChild* children[MAX_MOGERA_CHILDREN];
    int          childCount;


    RectangleShape healthBarBg;
    RectangleShape healthBarFill;

    FloatRect hitBox;

    // 0=leaving ground, 1=mid air, 2=fully extended, 3=death
    struct MogeraFrame { int x, y, w, h; };
    MogeraFrame frames[4];

    void spawnChild();
    void updateChildren(float dt, Platform* platforms[],
        int platformCount, CollisionDetector& cd);
    void drawHealthBar(RenderWindow& window);
    void updateHitBox();
    void setFrame(int index);
};