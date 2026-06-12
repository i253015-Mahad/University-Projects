#pragma once
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "CollisionDetector.h"
#include "Platform.h"
using namespace sf;
using namespace std;

struct FrameData {
    int x, y, w, h;
};

class Player {
public:
    Player(float x, float y, int playerNumber);

    void loadTexture(string imagePath, int playerIndex);
    void handleInput(InputManager& input, int leftAction,
        int rightAction, int jumpAction);
    void update(float dt, Platform* platforms[],
        int platformCount, CollisionDetector& cd);
    void draw(RenderWindow& window, bool showHitBox);
    void startThrowAnimation();
    void loseLife();
    void resetPosition();

    FloatRect getHitBox()        const;
    float     getX()             const;
    float     getY()             const;
    bool      isAlive()          const;
    int       getLives()         const;
    bool      isFacingRight()    const;
    bool      getIsInvincible()  const;

private:
    float x, y;
    float startX, startY;
    float velocityX, velocityY;
    bool  onGround;
    int   lives;
    int   playerNumber;
    bool  alive;
    bool  facingRight;

    // Invincibility
    bool  isInvincible;
    float hitTimer;
    float flashTimer;

    // Respawn
    bool  respawning;
    float respawnTimer;

    Texture   texture;
    Sprite    sprite;
    float     animTimer;
    int       animFrame;
    int       playerIndex;


    FrameData frames[7];

    // Throw animation
    bool  isThrowing;
    float throwAnimTimer;

    FloatRect hitBox;

    void applyGravity(float dt);
    void handlePlatformCollision(Platform* platforms[],
        int platformCount, CollisionDetector& cd);
    void handleScreenWrap();
    void updateHitBox();
    void updateAnimation(float dt);
    void setFrame(int frameIndex);
};