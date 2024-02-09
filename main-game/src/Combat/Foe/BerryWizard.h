#pragma once
#include "./Foe.h"

class BerryWizard : public Foe {
  public:
    BerryWizard() {
      id = "BerryWizard";
      hp = 100;
      maxHp = 100;
      bonusMaxHp;

      baseAtk = 6;
      bonusAtk = 0;
      baseDef = 6;
      bonusDef = 0;

      baseSpeed = 6;

      baseEnergy = 1;
      energy;

      // possible later implementation
      // expGain
      // loot

      actionList.push_back({"ChargeStrike",4});
    };


    // std::vector<Action*> actions = {};
    // Action* decideAction() override;
    void decideAction(Combat combat) override;
    std::vector<Unit*> decideTarget(std::vector<Unit*> targets) override;
};
