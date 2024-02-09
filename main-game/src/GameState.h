// GameState.h
#pragma once

class Game;

class GameState {
  public:
    // GameState() {};
    virtual ~GameState() = default; // destructor

    virtual void processInput(Game& game) = 0;
    virtual void update(Game& game) = 0;
    virtual void render(Game& game) = 0;

    // virtual void initialize() = 0;
    // virtual void exit() = 0;
};

