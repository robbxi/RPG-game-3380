#include "WildBerry.h"
#include "../Action/Actions.h"
#include <raylib.h>
#include <vector>

void WildBerry::decideAction(Combat combat) {
  if (actions.empty()) {
    fprintf(stderr, "no actions for enemy AI\n");
    // return nullptr;
  }
  
  std::vector<Action*> actionWeight = actions; 
  targetWeight = {}; 
  
  // check if any units have their attack boosted
  for (Unit* hero : combat.heroes)
  {
    bool no_stat = true;
    for (Token* token : hero->tokens)
    {
        if (token->tokenID/100 == 1) no_stat = false;
    }
    if (no_stat) {
        actionWeight.push_back(new InflictPoison(3));
        targetWeight.push_back(hero);
    }
  }

  int randomActionIndex = GetRandomValue(0, actionWeight.size() - 1);
  fprintf(stderr, "randomActionIndex rolled: %d\n", randomActionIndex);
  selectedAction = actionWeight[randomActionIndex];
};

std::vector<Unit*> WildBerry::decideTarget(std::vector<Unit*> targets) {
  if (targets.empty()){
    return {};
  }
  if (selectedAction->targetType != "self" && !targetWeight.empty())
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
