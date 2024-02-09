#include "DoNothing.h"

DoNothing::DoNothing() {
  targetType = "all";
  animationDuration = 92;
  actionDesc = {
      "Does Nothing Lol"
    };
}

DoNothing::~DoNothing() {
}

int DoNothing::perform(Unit* user, std::vector<Unit*> targets, Game& game) {
  user->actionDialouge += "Is loafing Around";
  for (Unit* target : targets) {
    fprintf(
      stderr,
      "%s performed [Do Nothing] on %s!!!\n",
      user->id.c_str(),
      target->id.c_str()
    );
  }
  user->energy -= energyCost;
  // fprintf(stderr, "%s performed [Do Nothing]!!!\n", user->id.c_str());
  return animationDuration;
};
