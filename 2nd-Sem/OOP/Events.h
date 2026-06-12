#pragma once

const int EVENT_ENEMY_DIED = 0;
const int EVENT_LEVEL_COMPLETE = 1;
const int EVENT_BOSS_DEFEATED = 2;
const int EVENT_PLAYER_HIT = 3;
const int EVENT_GEM_COLLECTED = 4;
const int EVENT_SCORE_CHANGED = 5;
const int EVENT_COUNT = 6;

const int MAX_LISTENERS = 10;

class EventBus {
public:
    static EventBus& get() {
        static EventBus instance;
        return instance;
    }

    void subscribe(int eventType, void (*listener)()) {
        if (eventType < 0 || eventType >= EVENT_COUNT) return;
        if (listenerCount[eventType] < MAX_LISTENERS) {
            listeners[eventType][listenerCount[eventType]] = listener;
            listenerCount[eventType]++;
        }
    }

    void fire(int eventType) {
        if (eventType < 0 || eventType >= EVENT_COUNT) return;
        for (int i = 0; i < listenerCount[eventType]; i++)
            listeners[eventType][i]();
    }

private:
    EventBus() {
        for (int i = 0; i < EVENT_COUNT; i++) {
            listenerCount[i] = 0;
            for (int j = 0; j < MAX_LISTENERS; j++)
                listeners[i][j] = nullptr;
        }
    }

    void (*listeners[EVENT_COUNT][MAX_LISTENERS])();
    int listenerCount[EVENT_COUNT];
};
