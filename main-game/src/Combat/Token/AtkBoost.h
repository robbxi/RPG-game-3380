#pragma once
#include "Token.h"

class AtkBoost : public Token {
  public:
    AtkBoost(int input, Texture2D newSprite) {
    stack = input;
    tokenID = GetRandomValue(100,199);
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
        unit.bonusAtk -= unit.baseAtk * 0.50;
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
