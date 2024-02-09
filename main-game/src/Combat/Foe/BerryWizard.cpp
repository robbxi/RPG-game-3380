#include "BerryWizard.h"
#include "../Action/Actions.h"
#include <raylib.h>
#include <vector>

void BerryWizard::decideAction(Combat combat) {
  if (actions.empty()) {
    fprintf(stderr, "no actions for enemy AI\n");
    // return nullptr;
  }
  
  std::vector<Action*> actionWeight = actions; 
  targetWeight = {}; 

  int randomActionIndex = GetRandomValue(0, actionWeight.size() - 1);
  fprintf(stderr, "randomActionIndex rolled: %d\n", randomActionIndex);
  selectedAction = actionWeight[randomActionIndex];
};

std::vector<Unit*> BerryWizard::decideTarget(std::vector<Unit*> targets) {
  if (targets.empty()){
    return {};
  }
  return targets;
}
