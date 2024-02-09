#pragma once
#include <string>
#include "../Unit.h"
#include "../../Game.h"
// #include "../Token/Token.h"
// #include "../Combat.h"

class Action {
  public:
    Action() {};
    virtual ~Action() = default;
    // Possible targetType
    // "self"
    // "ally"
    // "allies"
    // "team"
    // "enemy"
    // "enemies"
    // "all"
    // "ALL"
    std::string targetType;
    int energyCost = 1;
    int animationDuration = 12;
    int multiSelect;
    int amount;
    std::vector<std::string> actionDesc = {};

    virtual int perform(Unit* user, std::vector<Unit*> targets, Game& game) = 0;
};

