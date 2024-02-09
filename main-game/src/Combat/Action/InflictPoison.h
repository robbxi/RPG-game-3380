#pragma once
#include "Action.h"
#include "../Token/Poison.h"
// #include "../Token/Tokens.h"

class InflictPoison : public Action {
  public:
    // InflictPoison() {
    //   energyCost = 1;
    // }
    InflictPoison(int stack);
    ~InflictPoison();

    int perform(Unit* user, std::vector<Unit*> targets, Game& game) override;
};