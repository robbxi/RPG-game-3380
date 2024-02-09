#pragma once
#include "Action.h"

class Heal : public Action {
  public:
    // Heal() {
    //   energyCost = 1;
    // }
    Heal(int insert);
    ~Heal();
    
    // TODO: add target type functionality (should be simple)
    // std::string targetType = "enemy";

    int perform(Unit* user, std::vector<Unit*> targets, Game& game) override;
};