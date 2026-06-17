#include "Elliot.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Elliot::Elliot() : Hacker("Elliot", 500, 3, 4, 6), lastAttacker(nullptr)
{
}

int Elliot::receiveAttack(Hacker *attacker, int damage, int rageGain)
{
    if (isCrashed())
        return 0;
    lastAttacker = attacker;
    if (damage < 0)
        damage = 0;
    health -= damage;
    if (health < 0)
        health = 0;
    if (damage > 0)
        addRage(rageGain);
    return damage;
}

bool Elliot::canUseAbility1(Hacker *targets[2]) const
{
    if (isCrashed())
        return false;
    if (energy < getAbility1Cost())
        return false;
    return hasAliveTarget(targets);
}

bool Elliot::canUseAbility2(Hacker *targets[2]) const
{
    if (isCrashed())
        return false;
    if (energy < getAbility2Cost())
        return false;
    if (!lastAttacker)
        return false;
    if (lastAttacker->isCrashed())
        return false;
    bool found = false;
    for (int i = 0; i < 2; i++)
        if (targets[i] == lastAttacker)
            found = true;
    return found;
}

bool Elliot::canUseFinisher(Hacker *targets[2]) const
{
    if (isCrashed())
        return false;
    if (rage != 100)
        return false;
    if (energy < getFinisherCost())
        return false;
    return hasAliveTarget(targets);
}

void Elliot::ability1(Hacker *targets[2])
{
    if (!canUseAbility1(targets))
        return;
    Hacker *alive[2];
    int count = collectAlive(targets, alive);
    if (count == 0)
        return;
    Hacker *target = alive[rand() % count];

    int damage = 30 + (rand() % 31);
    spendEnergy(getAbility1Cost());
    int rageGain = 25 + (rand() % 26);
    resolveHit(target, damage, rageGain, "Elliot uses DDoS on " + target->getName() + " for " + to_string(damage) + " damage.");
}

void Elliot::ability2(Hacker *targets[2])
{
    if (!canUseAbility2(targets))
        return;
    Hacker *target = lastAttacker;
    int damage = 120 + (rand() % 21);
    spendEnergy(getAbility2Cost());
    int rageGain = 25 + (rand() % 26);
    resolveHit(target, damage, rageGain, "Elliot uses IP Trace & Counterattack on " + target->getName() + " for " + to_string(damage) + " damage.");
}

void Elliot::finisher(Hacker *targets[2])
{
    if (!canUseFinisher(targets))
        return;

    Hacker *target = nullptr;
    for (int i = 0; i < 2; i++)
    {
        if (targets[i] && !targets[i]->isCrashed())
        {
            if (!target)
                target = targets[i];
            else if (targets[i]->getHealth() > target->getHealth())
                target = targets[i];
        }
    }
    if (!target)
        return;

    spendEnergy(getFinisherCost());
    int rageGain = 25 + (rand() % 26);
    resolveHit(target, 300, rageGain, "Elliot uses Zero-Day Exploit on " + target->getName() + " for 300 damage.");
    setRage(0);
}
