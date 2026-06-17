#include "Anonymous.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Anonymous::Anonymous() : Hacker("Anonymous", 650, 2, 4, 8), shieldActive(false), shieldWillBeActiveNextRound(false)
{
}

void Anonymous::handleShield()
{
    if (shieldWillBeActiveNextRound)
    {
        shieldActive = true;
        shieldWillBeActiveNextRound = false;
        cout << "Anonymous firewall shield is active for this round." << endl;
    }
    else
    {
        shieldActive = false;
    }
}

int Anonymous::receiveAttack(Hacker *attacker, int damage, int rageGain)
{
    if (isCrashed())
        return 0;

    if (shieldActive)
    {
        cout << "Anonymous firewall shield blocks the attack from " << attacker->getName() << "." << endl;
        shieldActive = false;
        return 0;
    }

    if (damage < 0)
        damage = 0;

    health -= damage;
    if (health < 0)
        health = 0;

    if (damage > 0)
        addRage(rageGain);

    return damage;
}

bool Anonymous::canUseAbility1(Hacker *targets[2]) const
{
    if (isCrashed())
        return false;
    if (energy < getAbility1Cost())
        return false;
    return hasAliveTarget(targets);
}

bool Anonymous::canUseAbility2(Hacker *targets[2]) const
{
    if (isCrashed())
        return false;
    if (energy < getAbility2Cost())
        return false;
    if (shieldActive || shieldWillBeActiveNextRound)
        return false;
    return true;
}

bool Anonymous::canUseFinisher(Hacker *targets[2]) const
{
    if (isCrashed())
        return false;
    if (rage != 100)
        return false;
    if (energy < getFinisherCost())
        return false;
    return hasAliveTarget(targets);
}

void Anonymous::ability1(Hacker *targets[2])
{
    if (!canUseAbility1(targets))
        return;

    Hacker *alive[2];
    int count = collectAlive(targets, alive);
    if (count == 0)
        return;

    Hacker *target = alive[rand() % count];

    spendEnergy(getAbility1Cost());
    cout << "Anonymous uses Data Theft on " << target->getName() << " for 35 damage and heals self by 35." << endl;
    int rageGain = 25 + (rand() % 26);
    int dealt = target->receiveAttack(this, 35, rageGain);
    heal(dealt);
    if (target->isCrashed())
        cout << target->getName() << " crashed." << endl;
    if (dealt == 0)
        cout << target->getName() << " took 0 damage (shield blocked)." << endl;
}

void Anonymous::ability2(Hacker *targets[2])
{
    if (!canUseAbility2(targets))
        return;
    spendEnergy(getAbility2Cost());
    shieldWillBeActiveNextRound = true;
    cout << "Anonymous uses Firewall Shield. Shield will protect the first incoming attack next round." << endl;
}

void Anonymous::finisher(Hacker *targets[2])
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
            else
            {
                if (targets[i]->getHealth() < target->getHealth())
                    target = targets[i];
            }
        }
    }
    if (!target)
        return;

    spendEnergy(getFinisherCost());
    int rageGain = 25 + (rand() % 26);
    resolveHit(target, 350, rageGain, "Anonymous uses Purge Attack on " + target->getName() + " for 350 damage.");
    setRage(0);
}
