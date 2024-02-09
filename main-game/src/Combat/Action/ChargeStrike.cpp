#include "ChargeStrike.h"

ChargeStrike::ChargeStrike(int stack) {
    targetType = "charge";
    amount = stack;
    actionDesc = {
      ""
    };
}

ChargeStrike::~ChargeStrike() {
}

int ChargeStrike::perform(Unit* user, std::vector<Unit*> targets, Game& game) {
  user->actionDialouge += "Is Charging up a devestating Attack! Prepare within the next 3 turns ";
  
    // perform algorithm for the action
    Token* new_token = user->createToken("Warning", amount);
    if (user->tokens.size() == 0) {
      user->tokens.push_back(new_token);
    } 
    else if (user->tokens.size() <= 4) {
      for (Token* pending : user->tokens) {
        if (pending->tokenID == new_token->tokenID) {
          new_token->tokenID++;
          pending = user->tokens[0];
        }
      }
      user->tokens.push_back(new_token);
    }    
  user->energy -= energyCost;
  return animationDuration;
};