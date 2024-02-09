#pragma once
#include "Action.h"

class actionTemplate : public Action {
  public:
    // actionTemplate() {
    //   energyCost = 1;
    // }
    actionTemplate();
    ~actionTemplate();
    
    // TODO: add target type functionality (should be simple)
    // std::string targetType = "enemy";

    int perform(Unit* user, std::vector<Unit*> targets, Game& game) override;
};