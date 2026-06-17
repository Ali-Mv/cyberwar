#include "Hacker.h"
#include <iostream>

Hacker::Hacker(const string &n, int h, int c1, int c2, int cf) : name(n), health(h), energy(0), rage(0), maxHealth(health), cost1(c1), cost2(c2), costF(cf)
{
}

Hacker::~Hacker()
{
}

string Hacker::getName() const
{
    return name;
}
int Hacker::getHealth() const
{
    return health;
}
int Hacker::getEnergy() const
{
    return energy;
}
int Hacker::getRage() const
{
    return rage;
}
int Hacker::getAbility1Cost() const
{
    return cost1;
}
int Hacker::getAbility2Cost() const
{
    return cost2;
}
int Hacker::getFinisherCost() const
{
    return costF;
}

bool Hacker::isCrashed() const
{
    return health <= 0;
}

int Hacker::minActionCost() const
{
    int min = cost1;
    if (cost2 < min)
        min = cost2;
    if (costF < min)
        min = costF;
    return min;
}

void Hacker::addEnergy(int value)
{
    energy += value;
}
void Hacker::spendEnergy(int value)
{
    energy -= value;
    if (energy < 0)
        energy = 0;
}

void Hacker::heal(int value)
{
    health += value;
    if (health > maxHealth)
        health = maxHealth;
}
void Hacker::setRage(int value)
{
    if (value < 0)
        value = 0;
    if (value > 100)
        value = 100;
    rage = value;
}
void Hacker::addRage(int value)
{
    setRage(rage + value);
}

void Hacker::resolveHit(Hacker *t, int damage, int rageGain, const string &moveLog)
{
    cout << moveLog << endl;
    int dealt = t->receiveAttack(this, damage, rageGain);
    if (t->isCrashed())
        cout << t->getName() << " crashed." << endl;
    else if (dealt == 0)
        cout << t->getName() << " took 0 damage." << endl;
}

bool Hacker::hasAliveTarget(Hacker *targets[2]) const
{
    for (int i = 0; i < 2; i++)
        if (targets[i] && !targets[i]->isCrashed())
            return true;
    return false;
}

int Hacker::collectAlive(Hacker *targets[2], Hacker *out[2]) const
{
    int count = 0;
    for (int i = 0; i < 2; i++)
        if (targets[i] && !targets[i]->isCrashed())
            out[count++] = targets[i];
    return count;
}
