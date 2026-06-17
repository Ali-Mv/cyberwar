#include "Game.h"
#include "Elliot.h"
#include "Neo.h"
#include "Anonymous.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Game::Game() : roundNumber(0)
{
    hackers[0] = new Anonymous();
    hackers[1] = new Neo();
    hackers[2] = new Elliot();
}

Game::~Game()
{
    for (int i = 0; i < 3; i++)
        delete hackers[i];
}

int Game::aliveCount() const
{
    int num = 0;
    for (int i = 0; i < 3; i++)
        if (!hackers[i]->isCrashed())
            num++;
    return num;
}

Hacker *Game::getWinnerIfEnded() const
{
    if (aliveCount() == 1)
    {
        for (int i = 0; i < 3; i++)
            if (!hackers[i]->isCrashed())
                return hackers[i];
    }
    return nullptr;
}

void Game::buildTargetsFor(int indx, Hacker *outTargets[2]) const
{
    int k = 0;
    for (int i = 0; i < 3; i++)
    {
        if (i == indx)
            continue;
        outTargets[k++] = hackers[i];
    }
}

void Game::printStatus() const
{
    cout << "Status:" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << " - " << hackers[i]->getName() << " | HP: " << hackers[i]->getHealth() << " | Energy: " << hackers[i]->getEnergy() << " | Rage: " << hackers[i]->getRage();
        if (hackers[i]->isCrashed())
            cout << " | CRASHED";
        cout << endl;
    }
}

void Game::doTurn(int indx)
{
    Hacker *hacker = hackers[indx];
    if (hacker->isCrashed())
        return;

    Hacker *targets[2];
    buildTargetsFor(indx, targets);

    cout << endl
         << "Turn: " << hacker->getName() << endl;
    hacker->addEnergy(10);
    cout << hacker->getName() << " gains 10 energy." << endl;

    while (!hacker->isCrashed() && hacker->getEnergy() >= hacker->minActionCost() && !getWinnerIfEnded())
    {
        if (hacker->getRage() == 100 && hacker->canUseFinisher(targets))
        {
            hacker->finisher(targets);
            continue;
        }

        int choices[3];
        int count = 0;
        if (hacker->canUseAbility1(targets))
            choices[count++] = 1;
        if (hacker->canUseAbility2(targets))
            choices[count++] = 2;
        choices[count++] = 0;

        int pick = choices[rand() % count];

        if (pick == 0)
        {
            cout << hacker->getName() << " stops and saves energy." << endl;
            return;
        }
        else if (pick == 1)
            hacker->ability1(targets);
        else
            hacker->ability2(targets);
    }
}

void Game::run()
{
    srand((unsigned)time(nullptr));

    cout << "Cyber War Simulation Started." << endl;

    for (roundNumber = 1; roundNumber <= 7; roundNumber++)
    {
        cout << endl
             << "=== Round " << roundNumber << " ===" << endl;

        hackers[0]->handleShield();
        doTurn(0);
        if (getWinnerIfEnded())
            break;

        doTurn(1);
        if (getWinnerIfEnded())
            break;

        doTurn(2);
        if (getWinnerIfEnded())
            break;

        printStatus();
    }

    cout << endl
         << "=== Match End ===" << endl;

    Hacker *winner = getWinnerIfEnded();
    if (winner)
    {
        cout << "Winner: " << winner->getName() << endl;
        printStatus();
        return;
    }

    cout << "No winner." << endl;
    printStatus();
}
