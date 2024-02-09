#pragma once
#include "Token.h"

class Warning : public Token {
  public:
    Warning(int input, Texture2D newSprite) {
    stack = input;
    tokenID = GetRandomValue(300,399);
    sprite = newSprite;
  }
    int stack;

    int onTurnStart(Unit& unit) override {
      // TODO: How does this play a sound?
      // SOL1: pass Game to unit on... function then to this
      unit.energy = 0;
      if (stack != 1) unit.actionDialouge += "is charging. " + std::to_string(stack) + " turn(s) left!!";
      return 10;
    };
    virtual int onTurnEnd(Unit& unit) override {
      // TODO: How does this play a sound?
      // SOL1: pass Game to unit on... function then to this
      stack--;
      if (stack <= 0) {
            unit.actionDialouge += "Fires a burst of energy dealing 20 damage to the Hero";
            fprintf(stderr, "it gets to here\n");

            for (Unit* target : unit.chargedTarget) {
              if (target->getDef() < 20) target->hp -= 20 - target->getDef();
            }

            int i = 0;
            for(Token* pending : unit.tokens) {
                if (pending->tokenID == this->tokenID) {
                    unit.tokens.erase(unit.tokens.begin()+i);
                }
                i++;
            }
        }
      return 10;
    };
    virtual int onRoundStart(Unit& unit) override {
      // TODO: How does this play a sound?
      // SOL1: pass Game to unit on... function then to this

      return 0;
    };
    virtual int onRoundEnd(Unit& unit) override {
      // TODO: How does this play a sound?
      // SOL1: pass Game to unit on... function then to this
      return 0;
    };
};
