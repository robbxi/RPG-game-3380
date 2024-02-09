#include "Strike.h"

Strike::Strike() {
  targetType = "enemy";
  animationDuration = 92;
  actionDesc.push_back("Strikes the Target with your Might!!");
  actionDesc.push_back("All that can stop this force is your");
  actionDesc.push_back("Opponent's Defense!!!");
}

Strike::~Strike() {
}

Strike::Strike(int value) {
  targetType = "enemy";
  animationDuration = 92;
  tempBoost = value;
}

int Strike::perform(Unit* user, std::vector<Unit*> targets, Game& game) {
  user->actionDialouge += "Strikes the target(s) ";
  for (Unit* target : targets) {

    // perform algorithm
    user->bonusAtk += tempBoost;

    int damage;
    if (user->getAtk() <= target->getDef()) damage = 0;
    else damage = (user->getAtk() - target->getDef());
    target->hp -= damage;

    user->actionDialouge += target->id + " -" 
                         + std::to_string(user->getAtk() - target->getDef()) + ", ";

    user->bonusAtk -= tempBoost;

    fprintf(
      stderr,
      "%s performed [Strike] on %s!!!\n",
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
