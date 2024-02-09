#pragma once
#include "../Unit.h"

class Unit;

class Token {
  public:
    Token() {};
    virtual ~Token() = default;

    int stack;
    int tokenID;
    Texture2D sprite;

    virtual int onTurnStart(Unit& unit) = 0;
    virtual int onTurnEnd(Unit& unit) = 0;
    virtual int onRoundStart(Unit& unit) = 0;
    virtual int onRoundEnd(Unit& unit) = 0;
};
