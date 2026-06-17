#include "Neo.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Neo::Neo() : Hacker("Neo", 450, 4, 4, 5), healedCount(0)
{
    lastTwo[0] = nullptr;
    lastTwo[1] = nullptr;
    for (int i = 0; i < 10; i++)
        healedList[i] = nullptr;
}

int Neo::receiveAttack(Hacker *attacker, int damage, int rageGain)
{
    if (isCrashed())
        return 0;
    lastTwo[1] = lastTwo[0];
    lastTwo[0] = attacker;

    if (damage < 0)
        damage = 0;
    health -= damage;
    if (health < 0)
        health = 0;
    if (damage > 0)
        addRage(rageGain);
    return damage;
}

bool Neo::canUseAbility1(Hacker *targets[2]) const
{
    if (isCrashed())
        return false;
    if (energy < getAbility1Cost())
        return false;

    int count = 0;

    for (int i = 0; i < 2; i++)
    {
        Hacker *target = targets[i];
        if (!target || target->isCrashed())
            continue;

        bool blocked = false;
        if (lastTwo[0] == target)
            blocked = true;
        if (lastTwo[1] == target)
            blocked = true;

        if (!blocked)
            count++;
    }
    return count > 0;
}

bool Neo::canUseAbility2(Hacker *targets[2]) const
{
    if (isCrashed())
        return false;
    if (energy < getAbility2Cost())
        return false;
    return true;
}

bool Neo::wasHealedTarget(Hacker *h) const
{
    for (int i = 0; i < healedCount; i++)
        if (healedList[i] == h)
            return true;
    return false;
}

bool Neo::canUseFinisher(Hacker *targets[2]) const
{
    if (isCrashed())
        return false;
    if (rage != 100)
        return false;
    if (energy < getFinisherCost())
        return false;

    Hacker *candidates[2];
    int count = 0;
    for (int i = 0; i < 2; i++)
    {
        Hacker *target = targets[i];
        if (!target || target->isCrashed())
            continue;
        if (wasHealedTarget(target))
            candidates[count++] = target;
    }
    return count > 0;
}

void Neo::ability1(Hacker *targets[2])
{
    if (!canUseAbility1(targets))
        return;

    Hacker *candidates[2];
    int count = 0;

    for (int i = 0; i < 2; i++)
    {
        Hacker *target = targets[i];
        if (!target || target->isCrashed())
            continue;

        bool blocked = false;
        if (lastTwo[0] == target)
            blocked = true;
        if (lastTwo[1] == target)
            blocked = true;

        if (!blocked)
            candidates[count++] = target;
    }
    if (count == 0)
        return;

    Hacker *target = candidates[rand() % count];
    spendEnergy(getAbility1Cost());
    target->heal(35);
    if (!wasHealedTarget(target) && healedCount < 10)
    {
        healedList[healedCount++] = target;
    }
    cout << "Neo uses Security Patch on " << target->getName() << " and heals 35 health." << endl;
}

void Neo::ability2(Hacker *targets[2])
{
    if (!canUseAbility2(targets))
        return;
    spendEnergy(getAbility2Cost());
    heal(60);
    addRage(25);
    cout << "Neo uses Dark Web Showoff, heals 60 health, and gains 25 rage." << endl;
}

void Neo::finisher(Hacker *targets[2])
{
    if (!canUseFinisher(targets))
        return;

    Hacker *candidates[2];
    int count = 0;
    for (int i = 0; i < 2; i++)
    {
        Hacker *target = targets[i];
        if (!target || target->isCrashed())
            continue;
        if (wasHealedTarget(target))
            candidates[count++] = target;
    }
    if (count == 0)
        return;

    Hacker *target = candidates[rand() % count];
    spendEnergy(getFinisherCost());
    int rageGain = 25 + (rand() % 26);
    resolveHit(target, 250, rageGain, "Neo uses Ransomware Betrayal on " + target->getName() + " for 250 damage.");
    setRage(0);
}
