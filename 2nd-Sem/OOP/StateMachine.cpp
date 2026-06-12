#include "StateMachine.h"

StateMachine::StateMachine() {
    top = -1;  
    for (int i = 0; i < MAX_STATES; i++)
        states[i] = nullptr;
}

StateMachine::~StateMachine() {
    while (!isEmpty())
        pop();
}

void StateMachine::push(GameState* state) {
    if (top < MAX_STATES - 1) {
        top++;
        states[top] = state;
    }
}

void StateMachine::pop() {
    if (!isEmpty()) {
        delete states[top];
        states[top] = nullptr;
        top--;
    }
}

void StateMachine::change(GameState* state) {
    pop();
    push(state);
}

GameState* StateMachine::current() {
    if (isEmpty()) return nullptr;
    return states[top];
}

bool StateMachine::isEmpty() const {
    return top == -1;
}