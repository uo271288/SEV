#pragma once
#include "Enemy.h"

class SquashedEnemy :
    public Enemy
{
public:
    SquashedEnemy(std::string idle, std::string movement, std::string die, float x, float y);

    bool isUp(Actor* actor);
};