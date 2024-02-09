#pragma once
#include "Action.h"
#include "../Token/Warning.h"
// #include "../Token/Tokens.h"

class ChargeStrike : public Action {
  public:
    // InflictPoison() {
    //   energyCost = 1;
    // }
    ChargeStrike(int stack);
    ~ChargeStrike();

    int perform(Unit* user, std::vector<Unit*> targets, Game& game) override;
};