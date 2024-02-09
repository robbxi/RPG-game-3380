#pragma once
#include "./Foe.h"

class BlueBerry : public Foe {
  public:
    BlueBerry() {
      id = "BlueBerry";
      hp = 50;
      maxHp = 50;
      bonusMaxHp;

      baseAtk = 6;
      bonusAtk = 0;
      baseDef = 7;
      bonusDef = 0;

      baseSpeed = 6;

      baseEnergy = 1;
      energy;

      // possible later implementation
      // expGain
      // loot

      actionList.push_back({"DoNothing",0});
      actionList.push_back({"Strike",0});
      actionList.push_back({"BoostDef",5});
    };


    // std::vector<Action*> actions = {};
    // Action* decideAction() override;
    void decideAction(Combat combat) override;
    std::vector<Unit*> decideTarget(std::vector<Unit*> targets) override;
};
