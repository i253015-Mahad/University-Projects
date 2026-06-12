#pragma once
#include "GameState.h"


const int MAX_STATES = 10;

class StateMachine {
public:
    StateMachine();
    ~StateMachine();

    void push(GameState* state);   
    void pop();                    
    void change(GameState* state); 

    GameState* current();          
    bool isEmpty() const;

private:
    GameState* states[MAX_STATES]; 
    int top;                       
};