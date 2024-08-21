#pragma once
#include "Player.h"
class Assassin :
    public Player
{
public:
    Assassin();
    Assassin(float hp, float maxHp, float exp);
    virtual ~Assassin();

public:
    bool isClocking = false;
};

