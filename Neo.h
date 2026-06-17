#pragma once
#include "Hacker.h"

class Neo : public Hacker
{
private:
    Hacker *lastTwo[2];
    Hacker *healedList[10];
    int healedCount;

public:
    Neo();
    
    int receiveAttack(Hacker *attacker, int damage, int rageGain) override;

    bool canUseAbility1(Hacker *targets[2]) const override;
    bool canUseAbility2(Hacker *targets[2]) const override;
    bool canUseFinisher(Hacker *targets[2]) const override;

    void ability1(Hacker *targets[2]) override;
    void ability2(Hacker *targets[2]) override;
    void finisher(Hacker *targets[2]) override;

    bool wasHealedTarget(Hacker *h) const;
};
