#include "World.h"
#include <cstdio>
#include <raylib.h>
#include "../../external-libs/nlohmann/json.hpp"
#include <algorithm>
#include "Inventory.h"
World::World(
    std::string roomId
    ) {
  initializeWorld(roomId);
}

World::~World() {
  return;
}

void World::loadRoom(const std::string& roomId) {
  Room* roomToLoad = findRoom(roomId);
  // If the room does not exist, construct it
  if (roomToLoad == nullptr) {
    // fprintf(stderr, "Creating new Room...\n");
    const std::string saveFilePath = "./json/room/";
    const std::string jsonFileType = ".json";
    const std::string fullFilePath = saveFilePath + roomId + jsonFileType;
    nlohmann::json root;
    std::ifstream jsonFile(fullFilePath);

    if (jsonFile.is_open()) {
      try {
        jsonFile >> root;

        roomToLoad = buildRoom(roomId, root["roomData"]);
        rooms.push_back(roomToLoad);
      }
      catch (const std::exception& e) {
        fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      }
    }
  }
  // else fprintf(stderr, "Room already exists\n");

  setRoom(roomToLoad);
  // fprintf(stderr, "Successful loadRoom\n");
}


void World::update(Game& game) {
  if (transitionTimer > -1) {
    if (transitionTimer == 0) transitionHelper(game);
    --transitionTimer;
    return;
  }
  if (game.dialogQueue.empty()) {
    if (timeToNarrate) {
      (narratorData.at(currentRoom->roomId))->playNarrationLines(game);
      timeToNarrate = false;
      narrationPlaying = true;
    }
    else if (finalBattle) {
      enterCombat(game, finalBattleId);
    }
  }
  else player->movable = false;
  if (narrationPlaying) playNarrationSequence(game);
  player->update();
}

void World::enterCombat(Game& game, const std::string& battleId) {
  GameState* combat = new Combat(battleId, playerInventory, game);
  game.changeState(combat);
}

void World::transitionRoom(TransitionTile* transition) {
  destination = transition;
  transitionTimer = 30;
  player->movable = false;
}

void World::transitionHelper(Game& game) {
  player->movable = true;
  player->move(destination->enterX, destination->enterY);
  std::string destinationRoomId = destination->destinationRoomId;
  loadRoom(destinationRoomId);
}

void World::playNarrationSequence(Game& game) {
  // end the narration sequence if there is nothing left in the dialogue queue
  if (game.dialogQueue.empty()) {
      endNarration();
      return;
  }
  // Otherwise, update the rendering values for the narrator
}

void World::finalBattleSequence(Game& game) {
  finalBattle = true;
  game.dialogQueue.push("Evil Wizard: Fen? You are here to challenge me?");
  game.dialogQueue.push("Evil Wizard: You will never defeat me! I have all the power!\nEven a fox cannot defeat me!");
  game.dialogQueue.push("Evil Wizard: I will destroy you!");
}