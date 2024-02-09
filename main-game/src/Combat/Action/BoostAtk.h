#pragma once
#include "Action.h"
#include "../Token/AtkBoost.h"
// #include "../Token/Tokens.h"

class BoostAtk : public Action {
  public:
    // InflictPoison() {
    //   energyCost = 1;
    // }
    BoostAtk(int stack);
    ~BoostAtk();

    int perform(Unit* user, std::vector<Unit*> targets, Game& game) override;
};