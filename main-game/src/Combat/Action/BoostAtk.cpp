#include "BoostAtk.h"

BoostAtk::BoostAtk(int stack) {
    targetType = "self";
    amount = stack;
    actionDesc = {
      "Boosts targets' Attack by 50%",
      "For " + std::to_string(amount) + " Turns"
    };
}

BoostAtk::~BoostAtk() {
}

int BoostAtk::perform(Unit* user, std::vector<Unit*> targets, Game& game) {
  user->actionDialouge += "has boosted ";
  for (Unit* target : targets) {

    user->actionDialouge += target->id + "'s, ";

    // perform algorithm for the action
    Token* new_token = target->createToken("AtkBoost", amount);
    if (target->tokens.size() == 0) {
      target->bonusAtk += target->baseAtk * 0.50;
      target->tokens.push_back(new_token);
    } 
    else if (target->tokens.size() <= 10) {
      for (Token* pending : target->tokens) {
        if (pending->tokenID == new_token->tokenID) {
          new_token->tokenID++;
          pending = target->tokens[0];
        }
      }
      target->bonusAtk += target->baseAtk * 1.20;
      target->tokens.push_back(new_token);
    }

    //will need to modigy for actions containing multiple
    fprintf(
      stderr,
      "%s performed [Boost Attack] on %s!!!\n",
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
      "%s attack is now %i!!!\n",
      target->id.c_str(),
      target->getAtk()
    );
    
  }
  user->actionDialouge += "Def by 50%";
  user->energy -= energyCost;
  // fprintf(stderr, "%s performed [Strike]!!!\n", user->id.c_str());
  return animationDuration;
};