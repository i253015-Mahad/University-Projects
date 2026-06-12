#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Enemy.h"
#include "Botom.h"
#include "FlyingFoogaFoog.h"
#include "Tornado.h"
#include "Mogera.h"
#include "Gamakichi.h"
using namespace sf;

const int MAX_LEVEL_ENEMIES = 20;
const int MAX_LEVELS = 10;

struct EnemyConfig {
    int   type;           // 0=Botom  1=FlyingFoogaFoog  2=Tornado
    float x, y;
    int   textureVariant; // Botom: 0=Blue 1=Orange 2=Pink
    // Fooga: 0=Blue 1=Orange 2=Red
    // Tornado: 0=Blue 1=Red
    int   hitsToCoat;
};

struct PlatformConfig {
    float x, y, w, h;
};

struct LevelConfig {
    int            levelNumber;
    bool           isBonusLevel;
    int            enemyCount;
    EnemyConfig    enemies[MAX_LEVEL_ENEMIES];
    int            platformCount;
    PlatformConfig platforms[MAX_PLATFORMS];
    bool           hasMogera;
    float          moegraX, moegraY;
    bool           hasGamakichi;
    float          gamakichiX, gamakichiY;
    const char* backgroundPath;
};

class LevelManager {
public:
    LevelManager();

    void initConfigs();

    void loadLevel(
        Platform* platforms[], int& platformCount,
        Enemy* enemies[], int& enemyCount,
        Mogera*& moegraOut,
        Gamakichi*& gamakichiOut
    );

    void drawBackground(RenderWindow& window);


    bool isLevelComplete(
        Enemy* enemies[], int enemyCount,
        Mogera* mogera,
        Gamakichi* gamakichi
    ) const;

    bool advanceLevel();

    int  getCurrentLevelNumber() const;
    bool isLastLevel()           const;

private:
    LevelConfig m_levels[MAX_LEVELS];
    int         m_currentIndex;

    Texture     m_bgTexture;
    Sprite      m_bgSprite;

    void buildLevel1();
    void buildLevel2();
    void buildLevel3();
    void buildLevel4();
    void buildLevel5();
    void buildLevel6();
    void buildLevel7();
    void buildLevel8();
    void buildLevel9();
    void buildLevel10();

    const char* getTexturePath(int type, int variant) const;
};