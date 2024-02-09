#include "Grape.h"
#include "../Action/Actions.h"
#include <raylib.h>
#include <vector>

void Grape::decideAction(Combat combat) {
  if (actions.empty()) {
    fprintf(stderr, "no actions for enemy AI\n");
    // return nullptr;
  }
  
  std::vector<Action*> actionWeight = actions; 
  targetWeight = {}; 
  
  // check if any units have their attack boosted
  for (Unit* foe : combat.foes)
  {
    bool no_stat = true;
    for (Token* token : foe->tokens)
    {
        if (token->tokenID/100 == 1) no_stat = false;
    }
    if (no_stat) {
        actionWeight.push_back(new BoostAtk(5));
        targetWeight.push_back(foe);
    }
  }

  int randomActionIndex = GetRandomValue(0, actionWeight.size() - 1);
  fprintf(stderr, "randomActionIndex rolled: %d\n", randomActionIndex);
  selectedAction = actionWeight[randomActionIndex];
  // if (selectedAction == nullptr) {
  // return nullptr;
  // game.dialogQueue.push("Foe did nothing!");
  // selectedAction->perform(this, this, game);
  // startAnimationTime = GetTime();
  // animationTimer = 2.0;
  // selectedAction = nullptr;
  // }
  // return selectedAction;
};

std::vector<Unit*> Grape::decideTarget(std::vector<Unit*> targets) {
  if (targets.empty()){
    return {};
  }
  if (selectedAction->targetType == "self" && !targetWeight.empty())
  {
    for (Unit* target : targets) {
        targetWeight.push_back(target);
    }
    int randomTargetIndex = GetRandomValue(0, targets.size() - 1);
    fprintf(stderr, "randomTargetIndex rolled: %d\n", randomTargetIndex);
    Unit* target = targetWeight[randomTargetIndex];
    targets = {};
    targets.push_back(target);
  }
  return targets;
}
