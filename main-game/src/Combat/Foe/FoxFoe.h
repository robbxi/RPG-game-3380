#pragma once
#include "./Foe.h"

class FoxFoe : public Foe {
  public:
    FoxFoe() {
      id = "FoxFoe";
      hp = 100;
      maxHp = 100;
      bonusMaxHp;

      baseAtk = 10;
      bonusAtk = 0;
      baseDef = 4;
      bonusDef = 0;

      baseSpeed = 6;

      baseEnergy = 1;
      energy;

      // possible later implementation
      // expGain
      // loot

      actionList.push_back({"DoNothing",0});
      actionList.push_back({"Strike",0});
    };


    // std::vector<Action*> actions = {};
    // Action* decideAction() override;
    void decideAction(Combat combat) override;
    std::vector<Unit*> decideTarget(std::vector<Unit*> targets) override;
};
