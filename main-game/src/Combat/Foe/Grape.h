#pragma once
#include "./Foe.h"

class Grape : public Foe {
  public:
    Grape() {
      id = "Grape";
      hp = 50;
      maxHp = 50;
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
      actionList.push_back({"Strike",0});
      actionList.push_back({"BoostAtk",5});
    };


    // std::vector<Action*> actions = {};
    // Action* decideAction() override;
    void decideAction(Combat combat) override;
    std::vector<Unit*> decideTarget(std::vector<Unit*> targets) override;
};
