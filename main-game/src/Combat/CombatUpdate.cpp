#include "Combat.h"
#include <cstdio>
#include <raylib.h>

void Combat::update(Game& game) {
  if (animationDuration != 0) {
    animationDuration -= 1;
    fprintf(stderr, "[ANIMATION]: %d\n", animationDuration);
    return;
  }


  if (foes.empty()) {
        if (!combatConcluded) {
          while(!game.dialogQueue.empty()) game.dialogQueue.pop();
          game.dialogQueue.push("You WIN!!!");
          fprintf(stderr,"You WIN!!!");
          animationDuration += 40;
          combatConcluded = true;
          return;
          }
        // TODO: implement loot and exp gain
        // should delete tile/flag the tile as defeated
        dynamic_cast<World*>(game.world)->player->inventory = combatInventory;
        if(!game.dialogQueue.empty()) game.dialogQueue.pop();
        if(game.gameWin) {
          game.gameOver = true;
          game.changeState(new MainMenu());
        } 
        else {
          game.changeState(game.world);
          if (rewardKey) {
            game.dialogQueue.push("You got a key!\n");
            dynamic_cast<World*>(game.world)->player->inventory.addKeys(1);
          }
        }
        return;
      }

      if (heroes.empty()) {
        if (!combatConcluded){
          while(!game.dialogQueue.empty()) game.dialogQueue.pop();
          game.dialogQueue.push("Fen has been slain :(");
          fprintf(stderr,"You Died\n");
          animationDuration += 40;
          combatConcluded = true;
          return;
        }
          // TODO: implement game over
          // will likely consist of taken to a screen before being brough to the main menu
          if(!game.dialogQueue.empty()) game.dialogQueue.pop();
          game.gameOver = true;
          game.gameWin = false;
          game.changeState(new MainMenu());
          return;
      }

  if (isRoundOver) {
    // start new round
    fprintf(stderr, "[ROUND END]: %d\n", currentRound);
    currentRound += 1;
    fprintf(stderr, "----------------\n");
    fprintf(stderr, "[ROUND START]: %d\n", currentRound);
    for (Unit* hero : heroes) {
      animationDuration += hero->onRoundStart(combatConcluded);
      fprintf(stderr, "%s speed: %d\n maxHp: %d\n hp: %d\n", hero->id.c_str(), hero->getSpeed(), hero->getMaxHp(), hero->hp);
    }
    for (Unit* foe : foes) {
      animationDuration += foe->onRoundStart(combatConcluded);
      fprintf(stderr, "%s speed: %d\n maxHp: %d\n hp: %d\n", foe->id.c_str(), foe->getSpeed(), foe->getMaxHp(), foe->hp);
    }
    // sort by speed -> add to turnQueue

    // PLACEHOLDER: TO BE REPLACE. DO NOT USE //
    // turnQueue.push(heroes[0]);
    // // fprintf(stderr, "success\n");
    // turnQueue.push(foes[0]);
    // fprintf(stderr, "a\n");
    ///////////////////////////////
    // Sort characters by speed
    std::vector<Unit*> units;
    units.insert(units.end(), heroes.begin(), heroes.end());
    units.insert(units.end(), foes.begin(), foes.end());

    // favor player if same speed
    // std::sort(units.begin(), units.end(), [](Unit* a, Unit* b) {
    //     return a->getSpeed() > b->getSpeed();
    //     });

    // random sorting if same speed (need testing)
    std::sort(units.begin(), units.end(), [](Unit* a, Unit* b) {
        // Compare speeds
        if (a->getSpeed() > b->getSpeed()) {
        return true;
        }
        else if (a->getSpeed() < b->getSpeed()) {
        return false;
        }
        else {
        // If speeds are equal, favor player
        return true; // 50% chance for each unit to be first
        }
        });

    // Add characters to the turn queue
    for (Unit* unit : units) {
      turnQueue.push(unit);
    }
    isRoundOver = false;

    animationDuration += 8;
    return;
  }
  if (currentUnit == nullptr) {
    if (!turnQueue.empty()) {
      fprintf(stderr, "---\n");
      currentUnit = turnQueue.front();
      turnQueue.pop();
      fprintf(stderr, "turnStart being called for %s, current number of tokens: %d\n", currentUnit->id.c_str(), currentUnit->tokens.size());
      animationDuration += currentUnit->onTurnStart(combatConcluded);
      while(!game.dialogQueue.empty()) game.dialogQueue.pop();
      game.dialogQueue.push(currentUnit->actionDialouge);
      // currentUnit->animationTimer = 0.5;
      // currentUnit->startAnimationTime = GetTime();
      return;
    }

    animationDuration += 2;
    isRoundOver = true;
    return;
  }
  else {
    while(!game.dialogQueue.empty()) game.dialogQueue.pop();
    game.dialogQueue.push(currentUnit->actionDialouge);
    if (currentUnit->energy < 1) {
      animationDuration += currentUnit->onTurnEnd(combatConcluded);
      while(!game.dialogQueue.empty()) game.dialogQueue.pop();
      currentUnit->actionDialouge = "";

      currentUnit = nullptr;
      return;
    }
    if (isFoe(currentUnit)) {
      dynamic_cast<Foe*>(currentUnit)->decideAction(*this);
      if (currentUnit->selectedAction->targetType == "self") {
        targets = dynamic_cast<Foe*>(currentUnit)->decideTarget(foes);
      }
      else targets = dynamic_cast<Foe*>(currentUnit)->decideTarget(heroes);
    }
    Action* action = currentUnit->getAction();
    if (action == nullptr) return; // extra, maybe need later?
    if (action != nullptr && !targets.empty()) {
      animationDuration += action->perform(currentUnit, targets, game);

      while(!game.dialogQueue.empty()) game.dialogQueue.pop();
      game.dialogQueue.push(currentUnit->actionDialouge);
      fprintf(stderr, "actionDialouge: %s\n", currentUnit->actionDialouge.c_str());

      if (currentUnit->selectedAction->targetType == "charge") {
        currentUnit->chargedTarget = targets;
      }
      //reseting values for next decided action
      currentUnit->selectedAction = nullptr;
      currentUnit->selectedTargets = {};
      highlightedAction = nullptr;
      highlightedTarget = nullptr;
      highlightedItem = "";
      numberOfTargets = NULL;
      targets = {};
      availableTargets = {};
      action = nullptr;
    }

    foes = unitsVanquished(foes);
    heroes = unitsVanquished(heroes);

    return;
  }
}

