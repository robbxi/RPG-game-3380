#pragma once
#include "Action.h"
#include "../Token/DefBoost.h"
// #include "../Token/Tokens.h"

class BoostDef : public Action {
  public:
    // InflictPoison() {
    //   energyCost = 1;
    // }
    BoostDef(int stack);
    ~BoostDef();

    int perform(Unit* user, std::vector<Unit*> targets, Game& game) override;
};