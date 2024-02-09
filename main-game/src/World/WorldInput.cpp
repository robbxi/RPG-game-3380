#include "World.h"

void World::processInput(Game& game) {
  player->processInput(game, *this);
  if (!(player->movable)) return;
  if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
    if (IsKeyPressed(KEY_ENTER)) {
      game.loadSave("savedata-01");
      game.dialogQueue.push("Loaded save data");
    }
    else if (IsKeyPressed(KEY_P)) {
      game.saveSave("savedata-01");
      game.dialogQueue.push("Saved game data");
    }
  }
  else if (game.dialogQueue.empty() && IsKeyPressed(KEY_U)) {
    startNarration(currentRoom->roomId);
  }
}