#include "BlueBerry.h"
#include "../Action/Actions.h"
#include <raylib.h>
#include <vector>

void BlueBerry::decideAction(Combat combat) {
  if (actions.empty()) {
    fprintf(stderr, "no actions for enemy AI\n");
    // return nullptr;
  }
  
  std::vector<Action*> actionWeight = actions; 
  targetWeight = {}; 
  
  // check if any units have their attack boosted
  for (Unit* foe : combat.foes)
  {
    int no_stat = 0;
    for (Token* token : foe->tokens)
    {
        if (token->tokenID/100 == 1) no_stat++;
    }
    if (no_stat > 0 && no_stat <= 2) {
        actionWeight.push_back(new BoostDef(5));
        targetWeight.push_back(foe);
    }
  }

  int randomActionIndex = GetRandomValue(0, actionWeight.size() - 1);
  fprintf(stderr, "randomActionIndex rolled: %d\n", randomActionIndex);
  selectedAction = actionWeight[randomActionIndex];
};

std::vector<Unit*> BlueBerry::decideTarget(std::vector<Unit*> targets) {
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
