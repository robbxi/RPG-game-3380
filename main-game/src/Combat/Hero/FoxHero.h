#pragma once
#include "./Hero.h"
#include <vector>

class Action;

class FoxHero : public Hero {
  public:
    FoxHero() {
      //int heroLevel = ;
      id = "FoxHero";
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

      actionList.push_back({"Strike",0});
      actionList.push_back({"Charge",3});
      actionList.push_back({"Item",0});
    };
};
