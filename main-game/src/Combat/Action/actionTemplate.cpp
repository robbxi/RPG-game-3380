#include "actionTemplate.h"

actionTemplate::actionTemplate() {
}

actionTemplate::~actionTemplate() {
}

//might need to modify for 
int actionTemplate::perform(Unit* user, std::vector<Unit*> targets, Game& game) {
  for (Unit* target : targets) {

    // perform algorithm for the action
    target->hp -= user->getAtk();

    //will need to modigy for actions containing multiple
    fprintf(
      stderr,
      "%s performed [ActionTemplate] on %s!!!\n",
      user->id.c_str(),
      target->id.c_str()
    );
    fprintf(
      stderr,
      "the strike delt %i damage to target\n",
      user->baseAtk
    );
    fprintf(
      stderr,
      "%s hp is now %i!!!\n",
      target->id.c_str(),
      target->hp
    );
    
  }
  user->energy -= energyCost;
  // fprintf(stderr, "%s performed [Strike]!!!\n", user->id.c_str());
  return animationDuration;
};