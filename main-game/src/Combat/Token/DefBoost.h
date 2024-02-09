#pragma once
#include "Token.h"

class DefBoost : public Token {
  public:
    DefBoost(int input, Texture2D newSprite) {
    stack = input;
    tokenID = GetRandomValue(200,299);
    sprite = newSprite;
  }
    int stack;

    int onTurnStart(Unit& unit) override {
      // TODO: How does this play a sound?
      // SOL1: pass Game to unit on... function then to this
      return 0;
    };
    virtual int onTurnEnd(Unit& unit) override {
      // TODO: How does this play a sound?
      // SOL1: pass Game to unit on... function then to this
      stack--;
      if (stack <= 0) {
        int i = 0;
        fprintf(stderr, "current baseDef: %d, bonusDef: %d, 0.50 of baseDef: %d\n", unit.baseDef, unit.bonusDef, unit.baseDef * 0.50);
        unit.bonusDef -= unit.baseDef * 0.50;
        fprintf(stderr, "new bonusDef: %d\n",unit.bonusDef);
        for(Token* pending : unit.tokens) {
          if (pending->tokenID == this->tokenID) {
            unit.tokens.erase(unit.tokens.begin()+i);
          }
          i++;
        }
      }
      return 0;
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
