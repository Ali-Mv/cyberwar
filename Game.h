#pragma once
#include "Hacker.h"

class Game {
private:
    Hacker* hackers[3];
    int roundNumber;

    int aliveCount() const;
    Hacker* getWinnerIfEnded() const;
    void printStatus() const;

    void doTurn(int idx);
    void buildTargetsFor(int idx, Hacker* outTargets[2]) const;

public:
    Game();
    ~Game();
    void run();
};
