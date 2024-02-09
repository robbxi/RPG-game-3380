#pragma once
#include <cstdio>
#include <raylib.h>
#include <string>
#include <vector>
// #include "Combat.h"
#include "Token/Token.h"
// #include "Action/Action.h"
// #include "Action/Actions.h"

class Action;
class Token;
class Combat;

class Unit {

  public:
    Unit() {};
    virtual ~Unit() {};

    //character stats
    std::string id;
    int hp;
    int maxHp = 0;
    int bonusMaxHp;

    int baseAtk;
    int bonusAtk;
    int baseDef;
    int bonusDef;

    int baseEnergy = 1;
    int energy = 0;

    std::vector<Token*> tokens = {};
    std::vector<Action*> actions = {};
    std::vector<std::pair<std::string,int>> actionList = {};

    Action* selectedAction = nullptr;
    std::vector<Unit*> selectedTargets = {};
    std::vector<Unit*> chargedTarget = {};
    std::string actionDialouge;

    int baseSpeed = 0;
    int bonusSpeed = 0;
    
    //ability stats
    // Unit(
    //     std::string name,
    //     int health,
    //     int damage,
    //     int initiative
    //     );

    // double lockOut = 0;
    //
    double startAnimationTime = 0;
    double animationTimer = 0;

    int getMaxHp() {
      if(maxHp == 0) return 0;
      return maxHp;
    }
    int getDef() {
      return baseDef + bonusDef;
    }
    int getAtk() {
      return baseAtk + bonusAtk;
    }
    int getSpeed() {
      return baseSpeed + bonusSpeed;
    }

    std::vector<std::pair<std::string,int>> getActionList(){
      return actionList;
    }

    Action* getAction() {
      Action* action = selectedAction;
      return action;
    };

    Token* createToken(const std::string& tokenId, int stack);

    // void takeDmg(int dmg) {
    //   fprintf(stderr, "Take %d damage\n", dmg);
    // }

    int onTurnStart(bool combatConcluded) {
      int totalAnimationDuration = 10;
      fprintf(stderr, "%s's Turn\n", id.c_str());
      if (!combatConcluded) actionDialouge = (id+"'s Turn --- ");

      int i = 0;
      for (Token* token : tokens) {
        if (token->tokenID / 100 == 0) i++;
        totalAnimationDuration += token->onTurnStart(*this);
      }
      if(i > 0 && !combatConcluded) actionDialouge += id + " is being drained by poison!!! -"
                                + std::to_string(5 * i) + " health";
      // for (Equipment* equipment : equipments) {
      // }
      return totalAnimationDuration;
    }
    int onTurnEnd(bool combatConcluded) {
      int totalAnimationDuration = 2;
      fprintf(stderr, "%s's Turn Ended\n", id.c_str());
      for (Token* token : tokens) {
        totalAnimationDuration += token->onTurnEnd(*this);
      }

      return totalAnimationDuration;
      // for (Equipment* equipment : equipments) {
      // }
    }

      int onRoundStart(bool combatConcluded) {
        int totalAnimationDuration = 0;
        energy = baseEnergy;
        bonusSpeed = GetRandomValue(0, 6);
        // get speed modifier from other

        for (Token* token : tokens) {
          totalAnimationDuration += token->onRoundStart(*this);
        }
        return totalAnimationDuration;
      }
      int onRoundEnd(bool combatConcluded) {
        int totalAnimationDuration = 0;
        for (Token* token : tokens) {
          totalAnimationDuration += token->onRoundEnd(*this);
        }
      return totalAnimationDuration;
    }

    // virtual void playAnimation();

    // void playAnimation() {
    //   double currentTime = GetTime();
    //   double deltaTimeSinceLastMove = currentTime - startAnimationTime;
    //   if (deltaTimeSinceLastMove > animationTimer) {
    //     fprintf(stderr, "Animation completed: %f\n", deltaTimeSinceLastMove);
    //     animationTimer = 0;
    //     return;
    //   }
    //   fprintf(stderr, "Animation playing: %f\n", deltaTimeSinceLastMove);
    // }


    virtual void assasdasdasd() {};
    // virtual void takeTurn(Combat* combat) {};

    // void passTurn() {
    //   // Implement logic to pass the turn
    //   // hasTakenTurn = true;
    //   fprintf(stderr, "Character %s passed their turn\n", name.c_str());
    // }

    Texture2D sprite;
    bool item = false;

    //helper function for rendering
    void RenderSprite(
      Texture2D sprite,
      int hp,
      int maxHp,
      int energy,
      int screenWidth,
      int screenHeight, 
      int pos,
      std::vector<Token*> tokens,
      bool isHero,
      bool isFoe
      );
    // void RenderActions(
    //   int screenWidth,
    //   int screenHeight,
    //   int selectedAction,
    //   std::vector<Action*> actions
    // );
};
