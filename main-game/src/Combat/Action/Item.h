#pragma once
#include "Action.h"
#include "../Token/AtkBoost.h"
// #include "../Token/Tokens.h"

class Item : public Action {
  public:
    // InflictPoison() {
    //   energyCost = 1;
    // }
    Item();
    ~Item();

    int perform(Unit* user, std::vector<Unit*> targets, Game& game) override;
};