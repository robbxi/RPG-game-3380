#include "InflictPoison.h"

InflictPoison::InflictPoison(int stack) {
    targetType = "enemy";
    amount = stack;
    animationDuration = 92;
    actionDesc = {
      "Poisons a target dealing 5 damage",
      "For " + std::to_string(amount) + " Turns"
    };
}

InflictPoison::~InflictPoison() {
}

int InflictPoison::perform(Unit* user, std::vector<Unit*> targets, Game& game) {
  user->actionDialouge += "Has Inflicted Poison onto ";
  for (Unit* target : targets) {
    
    user->actionDialouge += target->id + ", ";

    // perform algorithm for the action
    Token* new_token = target->createToken("Poison", amount);
    if (target->tokens.size() == 0) target->tokens.push_back(new_token);
    else if (target->tokens.size() <= 10) {
      for (Token* pending : target->tokens) {
        if (pending->tokenID == new_token->tokenID) {
          new_token->tokenID++;
          pending = target->tokens[0];
        }
      }
      target->tokens.push_back(new_token);
    }

    //will need to modigy for actions containing multiple
    fprintf(
      stderr,
      "%s performed [InflictPoison] on %s!!!\n",
      user->id.c_str(),
      target->id.c_str()
    );
    // fprintf(
    //   stderr,
    //   "the strike delt %i damage to target\n",
    //   user->baseAtk
    // );
    fprintf(
      stderr,
      "%s hp is now %i!!!\n",
      target->id.c_str(),
      target->hp
    );
    
  }
  user->actionDialouge += " for " + std::to_string(amount) + " turns";
  user->energy -= energyCost;
  // fprintf(stderr, "%s performed [Strike]!!!\n", user->id.c_str());
  return animationDuration;
};