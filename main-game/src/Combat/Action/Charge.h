#pragma once
#include "Action.h"

class Charge : public Action {
  public:
    // Charge() {
    //   energyCost = 1;
    // }
    Charge(int stack);
    ~Charge();

    int perform(Unit* user, std::vector<Unit*> targets, Game& game) override;
};