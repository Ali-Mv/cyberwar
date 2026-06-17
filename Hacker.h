#pragma once
#include <string>
using namespace std;

class Hacker
{
protected:
    string name;
    int health;
    int maxHealth;
    int energy;
    int rage;

    const int cost1;
    const int cost2;
    const int costF;

public:
    Hacker(const string &n, int h, int c1, int c2, int cf);
    virtual ~Hacker();

    string getName() const;
    int getHealth() const;
    int getEnergy() const;
    int getRage() const;
    int getAbility1Cost() const;
    int getAbility2Cost() const;
    int getFinisherCost() const;

    bool isCrashed() const;
    int minActionCost() const;

    void addEnergy(int value);
    void spendEnergy(int value);

    void heal(int value);
    void setRage(int value);
    void addRage(int value);

    bool hasAliveTarget(Hacker *targets[2]) const;
    int collectAlive(Hacker *targets[2], Hacker *out[2]) const;
    void resolveHit(Hacker *t, int damage, int rageGain, const std::string &moveLog);

    virtual void handleShield() {}

    virtual int receiveAttack(Hacker *attacker, int damage, int rageGain) = 0;

    virtual bool canUseAbility1(Hacker *targets[2]) const = 0;
    virtual bool canUseAbility2(Hacker *targets[2]) const = 0;
    virtual bool canUseFinisher(Hacker *targets[2]) const = 0;

    virtual void ability1(Hacker *targets[2]) = 0;
    virtual void ability2(Hacker *targets[2]) = 0;
    virtual void finisher(Hacker *targets[2]) = 0;
};
