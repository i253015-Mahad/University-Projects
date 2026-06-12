#include "PlayingState.h"

PlayingState::PlayingState(RenderWindow& win,
    InputManager& inp, int type)
    : window(win), input(inp) {

    showHitBox = false;
    platformCount = 0;
    snowballCount = 0;
    enemyCount = 0;
    gameOver = false;
    mogera = nullptr;
    gamakichi = nullptr;

    for (int i = 0; i < MAX_SNOWBALLS; i++)
        snowballs[i] = nullptr;
    for (int i = 0; i < MAX_ENEMIES; i++)
        enemies[i] = nullptr;
    for (int i = 0; i < MAX_PLATFORMS; i++)
        platforms[i] = nullptr;
    playerNumber = type;

    player1 = new Player(200, 480, 1);
    player1->loadTexture("assets/Images/Nick.png", 1);

    if (type == 2)
    {
        player2 = new Player(500, 480, 2);
        player2->loadTexture("assets/Images/Player_Blue.png", 2);
    }

    levelManager.initConfigs();
    setupLevel();
}

PlayingState::~PlayingState() {
    delete player1;
    if (playerNumber == 2)
        delete player2;
    delete mogera;
    delete gamakichi;

    for (int i = 0; i < platformCount; i++) {
        delete platforms[i];
        platforms[i] = nullptr;
    }
    for (int i = 0; i < MAX_SNOWBALLS; i++) {
        delete snowballs[i];
        snowballs[i] = nullptr;
    }
    for (int i = 0; i < enemyCount; i++) {
        delete enemies[i];
        enemies[i] = nullptr;
    }
}

void PlayingState::setupLevel() {
    Font font;
    if (font.loadFromFile("PixelPurl.ttf")) {
        Text msg;
        msg.setFont(font);
        msg.setString("Loading next level  :)");
        msg.setCharacterSize(28);
        msg.setFillColor(Color(255, 220, 50));
        msg.setStyle(Text::Bold);
        FloatRect tb = msg.getLocalBounds();
        msg.setOrigin(tb.width / 2.f, tb.height / 2.f);
        msg.setPosition(400, 300);

        window.clear(Color(20, 20, 40));
        window.draw(msg);
        window.display();
    }

    for (int i = 0; i < platformCount; i++) {
        delete platforms[i];
        platforms[i] = nullptr;
    }
    platformCount = 0;

    for (int i = 0; i < enemyCount; i++) {
        delete enemies[i];
        enemies[i] = nullptr;
    }
    enemyCount = 0;

    delete mogera;    mogera = nullptr;
    delete gamakichi; gamakichi = nullptr;

    levelManager.loadLevel(
        platforms, platformCount,
        enemies, enemyCount,
        mogera,
        gamakichi
    );

    player1->resetPosition();
    if (playerNumber == 2)
        player2->resetPosition();
}

void PlayingState::handleInput(InputManager& inp) {
    if (gameOver) return;


    if (inp.isJustPressed(TOGGLE_HITBOX))
        showHitBox = !showHitBox;

    player1->handleInput(inp,
        P1_MOVE_LEFT, P1_MOVE_RIGHT, P1_JUMP);
    if (playerNumber == 2)
    {
        player2->handleInput(inp,
            P2_MOVE_LEFT, P2_MOVE_RIGHT, P2_JUMP);
    }

    if (inp.isJustPressed(P1_THROW)) {
        throwSnowball(player1, 1);
        player1->startThrowAnimation();
    }
    if (inp.isJustPressed(P2_THROW) && playerNumber == 2) {
        throwSnowball(player2, 2);
        player2->startThrowAnimation();
    }
}

void PlayingState::throwSnowball(Player* player,
    int playerNum) {
    if (snowballCount >= MAX_SNOWBALLS) return;

    for (int i = 0; i < MAX_SNOWBALLS; i++) {
        if (snowballs[i] == nullptr) {
            float spawnX = player->isFacingRight() ?
                player->getX() + 40 :
                player->getX() - 20;

            snowballs[i] = new Snowball(
                spawnX,
                player->getY() + 25,
                player->isFacingRight(),
                playerNum
            );
            snowballCount++;
            return;
        }
    }
}

void PlayingState::cleanupSnowballs() {
    for (int i = 0; i < MAX_SNOWBALLS; i++) {
        if (snowballs[i] != nullptr &&
            !snowballs[i]->isActive()) {
            delete snowballs[i];
            snowballs[i] = nullptr;
            snowballCount--;
        }
    }
}

void PlayingState::checkPlayerEnemyCollision() {
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i] == nullptr)    continue;
        if (enemies[i]->isDefeated()) continue;

        bool dangerousState =
            enemies[i]->getState() == ENEMY_STATE_WALK ||
            enemies[i]->getState() == ENEMY_STATE_ESCAPING;

        bool rollingState = enemies[i]->isFullyCoated();

        if (player1->isAlive() &&
            !player1->getIsInvincible() &&
            cd.overlaps(player1->getHitBox(),
                enemies[i]->getHitBox())) {
            if (rollingState)
                enemies[i]->startRolling(
                    player1->isFacingRight());
            else if (dangerousState)
                player1->loseLife();
        }

        if (playerNumber == 2)
        {
            if (player2->isAlive() &&
                !player2->getIsInvincible() &&
                cd.overlaps(player2->getHitBox(),
                    enemies[i]->getHitBox())) {
                if (rollingState)
                    enemies[i]->startRolling(
                        player2->isFacingRight());
                else if (dangerousState)
                    player2->loseLife();
            }
        }
    }
}

void PlayingState::checkRollingEnemyCollision() {
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i] == nullptr)    continue;
        if (!enemies[i]->isRolling()) continue;

        for (int j = 0; j < enemyCount; j++) {
            if (i == j) continue;
            if (enemies[j] == nullptr)    continue;
            if (enemies[j]->isDefeated()) continue;
            if (enemies[j]->isRolling())  continue;

            if (cd.overlaps(enemies[i]->getHitBox(),
                enemies[j]->getHitBox())) {
                enemies[j]->killEnemy();
                enemies[i]->incrementChain();
            }
        }

        if (mogera != nullptr &&
            !mogera->isDefeated() &&
            cd.overlaps(enemies[i]->getHitBox(),
                mogera->getHitBox())) {
            mogera->applyHit();
            enemies[i]->incrementChain();
        }
    }
}

void PlayingState::checkKnifePlayerCollision() {
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i] == nullptr) continue;

        Tornado* t = dynamic_cast<Tornado*>(enemies[i]);
        if (t == nullptr) continue;

        if (player1->isAlive() &&
            !player1->getIsInvincible())
            if (t->checkKnifeHit(player1->getHitBox(), cd))
                player1->loseLife();

        if (playerNumber == 2)
        {
            if (player2->isAlive() &&
                !player2->getIsInvincible())
                if (t->checkKnifeHit(player2->getHitBox(), cd))
                    player2->loseLife();
        }
    }
}

void PlayingState::updateMogera(float dt) {
    if (mogera == nullptr) return;

    mogera->update(dt, platforms, platformCount, cd);

    for (int i = 0; i < MAX_SNOWBALLS; i++) {
        if (snowballs[i] == nullptr)   continue;
        if (!snowballs[i]->isActive()) continue;
        if (mogera->checkSnowballHit(
            snowballs[i]->getHitBox(), cd))
            snowballs[i]->deactivate();
    }

    if (!mogera->isDefeated()) {
        if (player1->isAlive() && !player1->getIsInvincible())
            if (mogera->checkChildHit(player1->getHitBox(), cd))
                player1->loseLife();

        if (playerNumber == 2)
        {
            if (player2->isAlive() && !player2->getIsInvincible())
                if (mogera->checkChildHit(player2->getHitBox(), cd))
                    player2->loseLife();
        }

        if (player1->isAlive() && !player1->getIsInvincible() &&
            cd.overlaps(player1->getHitBox(), mogera->getHitBox()))
            player1->loseLife();

        if (playerNumber == 2)
        {
            if (player2->isAlive() && !player2->getIsInvincible() &&
                cd.overlaps(player2->getHitBox(), mogera->getHitBox()))
                player2->loseLife();
        }

        for (int i = 0; i < MAX_MOGERA_CHILDREN; i++) {
            MogeraChild* child = mogera->getChild(i);
            if (child == nullptr)       continue;
            if (!child->isActive())     continue;
            if (!child->isSnowCoated()) continue;

            if (player1->isAlive() &&
                cd.overlaps(player1->getHitBox(), child->getHitBox()))
                child->startSnowRolling(player1->isFacingRight());

            if (playerNumber == 2)
            {
                if (player2->isAlive() &&
                    cd.overlaps(player2->getHitBox(), child->getHitBox()))
                    child->startSnowRolling(player2->isFacingRight());
            }
        }

        for (int i = 0; i < MAX_MOGERA_CHILDREN; i++) {
            MogeraChild* c1 = mogera->getChild(i);
            if (c1 == nullptr)        continue;
            if (!c1->isSnowRolling()) continue;

            for (int j = 0; j < MAX_MOGERA_CHILDREN; j++) {
                if (i == j) continue;
                MogeraChild* c2 = mogera->getChild(j);
                if (c2 == nullptr)   continue;
                if (!c2->isActive()) continue;
                if (c2->isDying())   continue;
                if (cd.overlaps(c1->getHitBox(), c2->getHitBox()))
                    c2->kill();
            }

            if (!mogera->isDefeated() &&
                cd.overlaps(c1->getHitBox(), mogera->getHitBox()))
                mogera->applyHit();
        }
    }

    if (mogera->shouldRemove()) {
        delete mogera;
        mogera = nullptr;
    }
}

void PlayingState::updateGamakichi(float dt) {
    if (gamakichi == nullptr) return;

    gamakichi->update(dt, platforms, platformCount, cd);

    for (int i = 0; i < MAX_SNOWBALLS; i++) {
        if (snowballs[i] == nullptr)   continue;
        if (!snowballs[i]->isActive()) continue;
        if (gamakichi->checkSnowballHit(
            snowballs[i]->getHitBox(), cd))
            snowballs[i]->deactivate();
    }

    if (!gamakichi->isDefeated()) {
        if (player1->isAlive() && !player1->getIsInvincible() &&
            cd.overlaps(player1->getHitBox(), gamakichi->getHitBox()))
            player1->loseLife();

        if (playerNumber == 2)
        {
            if (player2->isAlive() && !player2->getIsInvincible() &&
                cd.overlaps(player2->getHitBox(), gamakichi->getHitBox()))
                player2->loseLife();
        }

        if (player1->isAlive() && !player1->getIsInvincible())
            if (gamakichi->checkBombPlayerHit(
                player1->getHitBox(), cd))
                player1->loseLife();

        if (playerNumber == 2)
        {
            if (player2->isAlive() && !player2->getIsInvincible())
                if (gamakichi->checkBombPlayerHit(
                    player2->getHitBox(), cd))
                    player2->loseLife();
        }

        if (player1->isAlive())
            gamakichi->checkPlayerKicksBomb(
                player1->getHitBox(),
                player1->isFacingRight(), cd);

        if (playerNumber == 2)
        {
            if (player2->isAlive())
                gamakichi->checkPlayerKicksBomb(
                    player2->getHitBox(),
                    player2->isFacingRight(), cd);
        }
    }

    if (gamakichi->shouldRemove()) {
        delete gamakichi;
        gamakichi = nullptr;
    }
}

void PlayingState::update(float dt) {

    if (gameOver) return;

    for (int i = 0; i < enemyCount; i++)
        if (enemies[i] != nullptr)
            enemies[i]->resetHitFlag();

    player1->update(dt, platforms, platformCount, cd);
    if (playerNumber == 2)
    {
        player2->update(dt, platforms, platformCount, cd);
    }

    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i] == nullptr) continue;
        Tornado* t = dynamic_cast<Tornado*>(enemies[i]);
        if (t != nullptr)
            t->update(dt, platforms, platformCount,
                cd, player1->getX(), player1->getY());
        else
            enemies[i]->update(dt, platforms,
                platformCount, cd);
    }

    for (int i = 0; i < MAX_SNOWBALLS; i++)
        if (snowballs[i] != nullptr)
            snowballs[i]->update(dt, enemies,
                enemyCount, platforms, platformCount, cd);

    checkPlayerEnemyCollision();
    checkRollingEnemyCollision();
    checkKnifePlayerCollision();
    updateMogera(dt);
    updateGamakichi(dt);
    cleanupSnowballs();

    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i] != nullptr &&
            enemies[i]->shouldRemove()) {
            delete enemies[i];
            enemies[i] = nullptr;
        }
    }

 
    if (!levelComplete &&
        levelManager.isLevelComplete(
            enemies, enemyCount, mogera, gamakichi)) {

        levelComplete = true;

        if (levelManager.isLastLevel()) {
            gameOver = true;
        }
        else {
            levelManager.advanceLevel();
            levelComplete = false;
            setupLevel();
        }
    }

    if (!player1->isAlive())
    {
        if (playerNumber == 2)
        {
            if (!player2->isAlive())
                gameOver = true;
        }
        else
            gameOver = true;
    }
        
}

void PlayingState::draw(RenderWindow& win, bool hitBox) {

    levelManager.drawBackground(win);


    for (int i = 0; i < platformCount; i++)
        platforms[i]->draw(win, showHitBox);

    if (gamakichi != nullptr)
        gamakichi->draw(win, showHitBox);

    if (mogera != nullptr)
        mogera->draw(win, showHitBox);

    for (int i = 0; i < enemyCount; i++)
        if (enemies[i] != nullptr)
            enemies[i]->draw(win, showHitBox);

    for (int i = 0; i < MAX_SNOWBALLS; i++)
        if (snowballs[i] != nullptr)
            snowballs[i]->draw(win, showHitBox);

    player1->draw(win, showHitBox);
    if (playerNumber == 2)
        player2->draw(win, showHitBox);
}

bool PlayingState::isGameOver() const {
    return gameOver;
}