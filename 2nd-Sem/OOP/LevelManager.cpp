#include "LevelManager.h"

LevelManager::LevelManager() : m_currentIndex(0) {
    for (int i = 0; i < MAX_LEVELS; i++) {
        m_levels[i].levelNumber = i + 1;
        m_levels[i].isBonusLevel = false;
        m_levels[i].enemyCount = 0;
        m_levels[i].platformCount = 0;
        m_levels[i].hasMogera = false;
        m_levels[i].moegraX = 350;
        m_levels[i].moegraY = 50;
        m_levels[i].hasGamakichi = false;
        m_levels[i].gamakichiX = 350;
        m_levels[i].gamakichiY = 50;
        m_levels[i].backgroundPath = "";
    }
}

void LevelManager::initConfigs() {
    buildLevel1();
    buildLevel2();
    buildLevel3();
    buildLevel4();
    buildLevel5();
    buildLevel6();
    buildLevel7();
    buildLevel8();
    buildLevel9();
    buildLevel10();
}

void LevelManager::drawBackground(RenderWindow& window) {
    window.draw(m_bgSprite);
}

const char* LevelManager::getTexturePath(int type,
    int variant) const {
    if (type == 0) {
        if (variant == 1) return "assets/Images/Botom_Orange.png";
        if (variant == 2) return "assets/Images/Botom_Pink.png";
        return "assets/Images/Botom_Blue.png";
    }
    if (type == 1) {
        if (variant == 1) return "assets/Images/FlyingFoogaFoog_Orange.png";
        if (variant == 2) return "assets/Images/FlyingFoogaFoog_Red.png";
        return "assets/Images/FlyingFoogaFoog_Blue.png";
    }
    if (type == 2) {
        if (variant == 1) return "assets/Images/Tornado_Red.png";
        return "assets/Images/Tornado_Blue.png";
    }
    return "";
}


void LevelManager::buildLevel1() {
    LevelConfig& c = m_levels[0];
    c.levelNumber = 1;
    c.isBonusLevel = false;
    c.hasMogera = false;
    c.hasGamakichi = false;
    c.backgroundPath = "assets/Images/Floor_1.png";

    c.platformCount = 10;
    c.platforms[0] = { 203, 169, 386, 15 };
    c.platforms[1] = { 110, 211,  89, 15 };
    c.platforms[2] = { 595, 211,  95, 15 };
    c.platforms[3] = { 0, 296, 335, 15 };
    c.platforms[4] = { 458, 296, 342, 15 };
    c.platforms[5] = { 159, 381, 473, 15 };
    c.platforms[6] = { 0, 465, 189, 15 };
    c.platforms[7] = { 307, 465, 180, 15 };
    c.platforms[8] = { 604, 465, 196, 15 };
    c.platforms[9] = { 0, 549, 800, 50 };

    c.enemyCount = 5;
    c.enemies[0] = { 0, 300, 114, 0, 2 }; 
    c.enemies[1] = { 0, 130, 156, 0, 2 }; 
    c.enemies[2] = { 0, 100, 241, 1, 2 };
    c.enemies[3] = { 0, 600, 241, 1, 2 }; 
    c.enemies[4] = { 0, 350, 326, 0, 2 }; 
}


void LevelManager::buildLevel2() {
    LevelConfig& c = m_levels[1];
    c.levelNumber = 2;
    c.isBonusLevel = false;
    c.hasMogera = false;
    c.hasGamakichi = false;
    c.backgroundPath = "assets/Images/Floor_2.png";

    c.platformCount = 10;
    c.platforms[0] = { 159, 132, 332, 15 };
    c.platforms[1] = { 607, 132,  83, 15 };
    c.platforms[2] = { 109, 216,  83, 15 };
    c.platforms[3] = { 308, 216, 300, 15 };
    c.platforms[4] = { 189, 301, 302, 15 };
    c.platforms[5] = { 607, 301,  83, 15 };
    c.platforms[6] = { 108, 386,  85, 15 };
    c.platforms[7] = { 308, 386, 301, 15 };
    c.platforms[8] = { 189, 470, 449, 15 };
    c.platforms[9] = { 0, 554, 800, 50 };

    c.enemyCount = 6;
    c.enemies[0] = { 0, 250,  77, 0, 2 }; 
    c.enemies[1] = { 0, 130, 161, 2, 2 }; 
    c.enemies[2] = { 0, 400, 161, 0, 2 }; 
    c.enemies[3] = { 0, 280, 246, 2, 2 }; 
    c.enemies[4] = { 0, 400, 331, 2, 2 }; 
    c.enemies[5] = { 0, 350, 415, 0, 2 }; 
}


void LevelManager::buildLevel3() {
    LevelConfig& c = m_levels[2];
    c.levelNumber = 3;
    c.isBonusLevel = false;
    c.hasMogera = false;
    c.hasGamakichi = false;
    c.backgroundPath = "assets/Images/Floor_3.png";

    c.platformCount = 11;
    c.platforms[0] = { 157, 132, 490, 15 };
    c.platforms[1] = { 2, 217,  96, 15 };
    c.platforms[2] = { 207, 217, 390, 15 };
    c.platforms[3] = { 707, 217,  93, 15 };
    c.platforms[4] = { 157, 302,  88, 15 };
    c.platforms[5] = { 360, 302,  81, 15 };
    c.platforms[6] = { 557, 302,  88, 15 };
    c.platforms[7] = { 2, 472, 147, 15 };
    c.platforms[8] = { 260, 472, 288, 15 };
    c.platforms[9] = { 658, 472, 142, 15 };
    c.platforms[10] = { 0, 557, 800, 50 };

    c.enemyCount = 7;
    c.enemies[0] = { 0, 250,  77, 1, 2 }; 
    c.enemies[1] = { 0, 500,  77, 1, 2 };
    c.enemies[2] = { 0,  20, 162, 2, 2 }; 
    c.enemies[3] = { 0, 350, 162, 1, 2 }; 
    c.enemies[4] = { 0, 720, 162, 2, 2 }; 
    c.enemies[5] = { 0,  40, 417, 2, 2 }; 
    c.enemies[6] = { 0, 680, 417, 1, 2 }; 
}

void LevelManager::buildLevel4() {
    LevelConfig& c = m_levels[3];
    c.levelNumber = 4;
    c.isBonusLevel = true;
    c.hasMogera = false;
    c.hasGamakichi = false;
    c.backgroundPath = "assets/Images/Floor_4.png";

    c.enemyCount = 5;
    c.enemies[0] = { 0, 300,  74, 0, 2 }; 
    c.enemies[1] = { 0, 550,  74, 1, 2 }; 
    c.enemies[2] = { 0, 150, 334, 2, 2 }; 
    c.enemies[3] = { 0, 500, 334, 0, 2 }; 
    c.enemies[4] = { 0, 300, 421, 1, 2 }; 

    c.platformCount = 9;
    c.platforms[0] = { 259, 129, 435, 15 };
    c.platforms[1] = { 110, 215, 432, 15 };
    c.platforms[2] = { 108, 302,  87, 15 };
    c.platforms[3] = { 360, 302, 337, 15 };
    c.platforms[4] = { 3, 389, 347, 15 };
    c.platforms[5] = { 458, 389, 342, 15 };
    c.platforms[6] = { 95, 476, 257, 15 };
    c.platforms[7] = { 460, 476, 249, 15 };
    c.platforms[8] = { 0, 562, 800, 50 };
}


void LevelManager::buildLevel5() {
    LevelConfig& c = m_levels[4];
    c.levelNumber = 5;
    c.isBonusLevel = false;
    c.hasMogera = true;
    c.moegraX = 350;
    c.moegraY = 50;
    c.hasGamakichi = false;
    c.backgroundPath = "assets/Images/Floor_5.png";

    c.platformCount = 6;
    c.platforms[0] = { 3, 213, 339, 15 };
    c.platforms[1] = { 159, 300, 286, 15 };
    c.platforms[2] = { 555, 343, 241, 15 };
    c.platforms[3] = { 3, 387, 344, 15 };
    c.platforms[4] = { 158, 472, 287, 15 };
    c.platforms[5] = { 0, 558, 800, 50 };

    c.enemyCount = 5;
    c.enemies[0] = { 0,  60, 158, 0, 2 }; 
    c.enemies[1] = { 1, 250, 245, 2, 2 }; 
    c.enemies[2] = { 1, 600, 288, 2, 2 }; 
    c.enemies[3] = { 0, 100, 332, 0, 2 }; 
    c.enemies[4] = { 2, 250, 417, 1, 2 }; 
}


void LevelManager::buildLevel6() {
    LevelConfig& c = m_levels[5];
    c.levelNumber = 6;
    c.isBonusLevel = false;
    c.hasMogera = false;
    c.hasGamakichi = false;
    c.backgroundPath = "assets/Images/Floor_6.png";

    c.platformCount = 11;
    c.platforms[0] = { 162, 124, 479, 15 };
    c.platforms[1] = { 4, 212, 194, 15 };
    c.platforms[2] = { 606, 212, 191, 15 };
    c.platforms[3] = { 4, 298,  95, 15 };
    c.platforms[4] = { 208, 298, 141, 15 };
    c.platforms[5] = { 453, 298, 144, 15 };
    c.platforms[6] = { 707, 298,  90, 15 };
    c.platforms[7] = { 4, 472,  96, 15 };
    c.platforms[8] = { 208, 472, 387, 15 };
    c.platforms[9] = { 705, 472,  91, 15 };
    c.platforms[10] = { 0, 558, 800, 50 };

    c.enemyCount = 8;
    c.enemies[0] = { 0, 200,  69, 1, 3 }; 
    c.enemies[1] = { 0, 500,  69, 1, 3 }; 
    c.enemies[2] = { 0,  60, 157, 1, 3 }; 
    c.enemies[3] = { 0, 700, 157, 1, 3 }; 
    c.enemies[4] = { 1, 250, 243, 0, 3 }; 
    c.enemies[5] = { 1, 500, 243, 0, 3 }; 
    c.enemies[6] = { 2, 250, 417, 0, 3 }; 
    c.enemies[7] = { 2, 500, 417, 0, 3 }; 
}


void LevelManager::buildLevel7() {
    LevelConfig& c = m_levels[6];
    c.levelNumber = 7;
    c.isBonusLevel = false;
    c.hasMogera = false;
    c.hasGamakichi = false;
    c.backgroundPath = "assets/Images/Floor_7.png";

    c.platformCount = 15;
    c.platforms[0] = { 1, 128, 239, 15 };
    c.platforms[1] = { 505, 128, 183, 15 };
    c.platforms[2] = { 355, 172, 174, 15 };
    c.platforms[3] = { 157, 214, 223, 15 };
    c.platforms[4] = { 605, 214, 192, 15 };
    c.platforms[5] = { 107, 300,  91, 15 };
    c.platforms[6] = { 408, 300, 233, 15 };
    c.platforms[7] = { 170, 343, 125, 15 };
    c.platforms[8] = { 618, 343, 180, 15 };
    c.platforms[9] = { 270, 386, 170, 15 };
    c.platforms[10] = { 1, 429, 145, 15 };
    c.platforms[11] = { 653, 429, 145, 15 };
    c.platforms[12] = { 118, 472, 224, 15 };
    c.platforms[13] = { 455, 472, 224, 15 };
    c.platforms[14] = { 0, 558, 800, 50 };

    c.enemyCount = 8;
    c.enemies[0] = { 0,  50,  73, 2, 3 }; 
    c.enemies[1] = { 0, 600,  73, 2, 3 }; 
    c.enemies[2] = { 1, 200, 159, 1, 3 }; 
    c.enemies[3] = { 1, 700, 159, 1, 3 }; 
    c.enemies[4] = { 0, 500, 245, 2, 3 }; 
    c.enemies[5] = { 1, 220, 288, 1, 3 }; 
    c.enemies[6] = { 2, 320, 331, 1, 3 }; 
    c.enemies[7] = { 2, 550, 417, 1, 3 }; 
}


void LevelManager::buildLevel8() {
    LevelConfig& c = m_levels[7];
    c.levelNumber = 8;
    c.isBonusLevel = false;
    c.hasMogera = false;
    c.hasGamakichi = false;
    c.backgroundPath = "assets/Images/Floor_8.png";

    c.platformCount = 11;
    c.platforms[0] = { 253, 174, 294, 15 };
    c.platforms[1] = { 158, 216, 101, 15 };
    c.platforms[2] = { 540, 216, 100, 15 };
    c.platforms[3] = { 1, 301, 344, 15 };
    c.platforms[4] = { 454, 301, 343, 15 };
    c.platforms[5] = { 109, 387, 238, 15 };
    c.platforms[6] = { 452, 387, 242, 15 };
    c.platforms[7] = { 1, 472,  96, 15 };
    c.platforms[8] = { 206, 472, 389, 15 };
    c.platforms[9] = { 705, 472,  93, 15 };
    c.platforms[10] = { 0, 557, 800, 50 };

    c.enemyCount = 8;
    c.enemies[0] = { 0, 350, 119, 0, 3 }; 
    c.enemies[1] = { 0, 180, 161, 0, 3 }; 
    c.enemies[2] = { 0, 580, 161, 0, 3 }; 
    c.enemies[3] = { 1,  50, 246, 2, 3 }; 
    c.enemies[4] = { 1, 600, 246, 2, 3 }; 
    c.enemies[5] = { 2, 200, 332, 0, 3 }; 
    c.enemies[6] = { 2, 550, 332, 0, 3 }; 
    c.enemies[7] = { 2, 350, 417, 0, 3 }; 
}


void LevelManager::buildLevel9() {
    LevelConfig& c = m_levels[8];
    c.levelNumber = 9;
    c.isBonusLevel = true;
    c.hasMogera = false;
    c.hasGamakichi = false;
    c.backgroundPath = "assets/Images/Floor_9.png";


    c.enemyCount = 7;
    c.enemies[0] = { 0, 300,  77, 0, 3 }; 
    c.enemies[1] = { 1, 400, 162, 1, 3 }; 
    c.enemies[2] = { 0, 150, 247, 2, 3 }; 
    c.enemies[3] = { 2, 350, 247, 1, 3 };
    c.enemies[4] = { 1, 100, 333, 0, 3 }; 
    c.enemies[5] = { 0, 550, 333, 2, 3 }; 
    c.enemies[6] = { 2, 300, 418, 1, 3 }; 

    c.platformCount = 12;
    c.platforms[0] = { 203, 132, 395, 15 };
    c.platforms[1] = { 0, 217,  96, 15 };
    c.platforms[2] = { 292, 217, 215, 15 };
    c.platforms[3] = { 702, 217,  98, 15 };
    c.platforms[4] = { 79, 302, 262, 15 };
    c.platforms[5] = { 458, 302, 249, 15 };
    c.platforms[6] = { 0, 388, 147, 15 };
    c.platforms[7] = { 257, 388, 291, 15 };
    c.platforms[8] = { 651, 388, 149, 15 };
    c.platforms[9] = { 92, 473, 255, 15 };
    c.platforms[10] = { 457, 473, 254, 15 };
    c.platforms[11] = { 0, 558, 800, 50 };
}


void LevelManager::buildLevel10() {
    LevelConfig& c = m_levels[9];
    c.levelNumber = 10;
    c.isBonusLevel = false;
    c.hasMogera = false;
    c.hasGamakichi = true;
    c.gamakichiX = 350;
    c.gamakichiY = 50;
    c.backgroundPath = "assets/Images/Floor_10.png";

    c.platformCount = 6;
    c.platforms[0] = { 111, 297, 585, 15 };
    c.platforms[1] = { 2, 384, 295, 15 };
    c.platforms[2] = { 510, 384, 289, 15 };
    c.platforms[3] = { 111, 469, 237, 15 };
    c.platforms[4] = { 460, 469, 237, 15 };
    c.platforms[5] = { 0, 554, 800, 50 };

    c.enemyCount = 9;
    c.enemies[0] = { 0, 200, 242, 1, 4 }; 
    c.enemies[1] = { 0, 580, 242, 1, 4 }; 
    c.enemies[2] = { 1, 350, 242, 2, 4 }; 
    c.enemies[3] = { 1,  50, 329, 2, 4 }; 
    c.enemies[4] = { 1, 600, 329, 2, 4 }; 
    c.enemies[5] = { 2, 130, 414, 1, 4 }; 
    c.enemies[6] = { 2, 290, 414, 1, 4 }; 
    c.enemies[7] = { 2, 480, 414, 1, 4 }; 
    c.enemies[8] = { 2, 650, 414, 1, 4 }; 
}


void LevelManager::loadLevel(
    Platform* platforms[], int& platformCount,
    Enemy* enemies[], int& enemyCount,
    Mogera*& moegraOut,
    Gamakichi*& gamakichiOut)
{
    const LevelConfig& cfg = m_levels[m_currentIndex];

    if (m_bgTexture.loadFromFile(cfg.backgroundPath)) {
        m_bgSprite.setTexture(m_bgTexture, true);
        Vector2u sz = m_bgTexture.getSize();
        m_bgSprite.setScale(
            800.0f / (float)sz.x,
            600.0f / (float)sz.y
        );
    }

    platformCount = 0;
    for (int i = 0; i < cfg.platformCount
        && i < MAX_PLATFORMS; i++) {
        const PlatformConfig& p = cfg.platforms[i];
        platforms[platformCount++] =
            new Platform(p.x, p.y, p.w, p.h);
    }

    enemyCount = 0;
    for (int i = 0; i < cfg.enemyCount
        && i < MAX_ENEMIES; i++) {
        const EnemyConfig& ec = cfg.enemies[i];
        const char* tex = getTexturePath(
            ec.type, ec.textureVariant);
        Enemy* e = nullptr;

        if (ec.type == 0) {
            Botom* b = new Botom(ec.x, ec.y);
            b->loadTexture(tex);
            b->setHitsToCoat(ec.hitsToCoat);
            e = b;
        }
        else if (ec.type == 1) {
            FlyingFoogaFoog* f =
                new FlyingFoogaFoog(ec.x, ec.y);
            f->loadTexture(tex);
            f->setHitsToCoat(ec.hitsToCoat);
            e = f;
        }
        else if (ec.type == 2) {
            Tornado* t = new Tornado(ec.x, ec.y);
            t->loadTexture(tex);
            t->setHitsToCoat(ec.hitsToCoat);
            e = t;
        }

        if (e != nullptr)
            enemies[enemyCount++] = e;
    }

    moegraOut = nullptr;
    gamakichiOut = nullptr;

    if (cfg.hasMogera) {
        Mogera* m = new Mogera(cfg.moegraX, cfg.moegraY);
        m->loadTexture("assets/Images/Mogera.png");
        moegraOut = m;
    }

    if (cfg.hasGamakichi) {
        Gamakichi* g = new Gamakichi(
            cfg.gamakichiX, cfg.gamakichiY);
        g->loadTexture("assets/Images/Gamakichi.png");
        gamakichiOut = g;
    }
}

bool LevelManager::isLevelComplete(
    Enemy* enemies[], int enemyCount,
    Mogera* mogera,
    Gamakichi* gamakichi) const
{
    if (m_levels[m_currentIndex].isBonusLevel)
        return true;

    for (int i = 0; i < enemyCount; i++)
        if (enemies[i] != nullptr &&
            !enemies[i]->isDefeated())
            return false;

    if (m_levels[m_currentIndex].hasMogera &&
        mogera != nullptr)
        return false;

    if (m_levels[m_currentIndex].hasGamakichi &&
        gamakichi != nullptr)
        return false;

    return true;
}

bool LevelManager::advanceLevel() {
    if (m_currentIndex >= MAX_LEVELS - 1) return false;
    m_currentIndex++;
    return true;
}

int LevelManager::getCurrentLevelNumber() const {
    return m_levels[m_currentIndex].levelNumber;
}

bool LevelManager::isLastLevel() const {
    return m_currentIndex >= MAX_LEVELS - 1;
}