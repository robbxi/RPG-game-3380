#include "Player.h"

void Player::processInput(Game& game, World& world) {
  if (IsKeyPressed(KEY_SPACE)) {
    if (movable) {
    int targetX = x;
    int targetY = y;

    if (facing == "up") {
      targetY--;
    }
    else if (facing == "down") {
      targetY++;
    }
    else if (facing == "left") {
      targetX--;
    }
    else if (facing == "right") {
      targetX++;
    }
    else {
      fprintf(stderr, "invalid player->facing direction");
      return;
    }

    for (Entity* entity : world.entities) {
      bool isAtTile =
        entity->x == targetX &&
        entity->y == targetY
        ;
      if (!isAtTile) {
        continue;
      }
      Tile* tile = dynamic_cast<Tile*>(entity);
      if (tile != nullptr) {
          std::pair<std::string, std::string> tileData = tile->interact();
          std::string tileType = tileData.first;
          std::string tileText = tileData.second;
          if (tileType == "battle") {
            if (tile->id == world.finalBattleId) {
              world.finalBattleSequence(game);
              break;
            }
            world.enterCombat(game, tile->id);
            world.removeEntity(tile->id);
            world.currentRoom->removeTile(tile->id);
            break;
            }
          else if (tileType == "npc") {
            for (const std::string& dialogueLine : dynamic_cast<NpcTile*>(entity)->getDialogue()) {
              game.dialogQueue.push(dialogueLine);
            }
            break;
          }
          else if (tileType == "chest") {
            inventory.addKeys(tile->inventory.getKeys());
            takeItems(tile->inventory);

            world.removeEntity(tile->id);
            world.currentRoom->removeTile(tile->id);
            game.dialogQueue.push(tileText);
            break;
          }
          else if (tileType == "door") {
            if (inventory.hasKey()) {
              game.dialogQueue.push("Unlocking door");
              // Remove one key from the player
              inventory.removeKey();
              // Remove door
              int doorX = tile->x,
                  doorY = tile->y;
              world.removeDoor(doorX, doorY);
              world.currentRoom->removeDoor(doorX, doorY);
            }
            else {
              game.dialogQueue.push("Cannot unlock door! No keys!");
            }
            break;
          }
        }
      }
    }
    else if (!game.dialogQueue.empty()) {
      game.dialogQueue.pop();
      if (game.dialogQueue.empty()) {
        movable = true;
      }
    }
  }

  if (movable) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      Vector2 mousePosition = GetMousePosition();
      int targetX = mousePosition.x / game.settings.gridWidth;
      int targetY = mousePosition.y / game.settings.gridHeight;

      fprintf(stderr, "mousePosition: %d, %d\n", targetX, targetY);

      // If player hit the UI/Dialog area
      if (targetY >= 12) {
        if (!game.dialogQueue.empty()) {
          game.dialogQueue.pop();
          return;
        }
        // NOTE: UI button interaction should go here
      }

      std::queue<std::pair<int, int>>().swap(pathQueue); // empty the queue
      // pathQueue = {};
      findShortestPath(world, x, y, targetX, targetY);
      if (!pathQueue.empty()) {
        animationDuration = 0;
      }
    }

    int newX = x;
    int newY = y;
    std::string direction = inputHelper(facing);

    if (direction == "none") return;
    if (direction == "right") {
      facing = "right";
      newX++;
    }
    else if (direction == "left") {
      facing = "left";
      newX--;
    }
    else if (direction == "down") {
      facing = "down";
      newY++;
    }
    else if (direction == "up") {
      facing = "up";
      newY--;
    }
    else {
      fprintf(stderr, "error direction\n");
    }

    if (animationDuration > 0) return;
    if (animationFrame == 0) animationFrame = 2;
    else animationFrame -= 1;


    std::queue<std::pair<int, int>>().swap(pathQueue); // empty the queue

    // Check if the new position is out of bounds
    bool isOutOfBound = newX < 0 ||
      newX >= world.columns ||
      newY < 0 ||
      newY >= world.rows;
    if (isOutOfBound) {
      fprintf(stderr, "out of bound: %d, %d\n", newX, newY);
    }
    else if (world.grid[newX][newY] == 1) {
      // no movement, terrain or tile block
      return;
    }
    else {
      // NOTE: player's depth/y may have changed. If so we need to sort the GameObjects vector
      if (y != newY) {
        move(newX, newY);
        world.sortGameObjects();
      }
      else move(newX, newY);
      resetAnimationDuration();
      for (TransitionTile* transition : world.transitionTiles) {
        bool isAtTransition =
          transition->x == this->x &&
          transition->y == this->y
          ;
        if (isAtTransition) {
          world.transitionRoom(transition);
          return;
        }
      }
      for (Entity* entity : world.entities) {
        bool isAtTile =
          entity->x == x &&
          entity->y == y
          ;
        if (!isAtTile) {
          continue;
        }
        Tile* tile = dynamic_cast<Tile*>(entity);
        if (tile != nullptr) {
          std::pair<std::string, std::string> tileData = tile->interact();
          std::string tileType = tileData.first;
          std::string tileText = tileData.second;
          if (tileType == "battle") {
            // fprintf(stderr, "Entering Combat\n");
            world.enterCombat(game, tile->id);
            world.removeEntity(tile->id);
            world.currentRoom->removeTile(tile->id);
          }
        }
      }
    }
  }
}

std::string Player::inputHelper(std::string facing) {
  std::string lastDirection = facing;

  if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) return "right";
  if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) return "left";
  if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) return "up";
  if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) return "down";

  bool isNoMovementKeyHeld = !(
      IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) ||
      IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) ||
      IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S) ||
      IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)
      );

  if (isNoMovementKeyHeld) {
    return "none";
  }

  bool isNoChange =
    (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && lastDirection == "right" ||
    (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && lastDirection == "left" ||
    (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && lastDirection == "down" ||
    (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && lastDirection == "up";

  if (isNoChange) {
    return lastDirection;
  }
  else {
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
      return "right";
    }
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
      return "left";
    }
    else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
      return "down";
    }
    else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
      return "up";
    }
  }

  return "error";
}

/*
TODO: This can be optimized further by keeping track of the target
the player is walking to then decide if the current path is "good"
if good -> calculate from old target to new target instead
if bad -> same as before
*/
void Player::findShortestPath(World& world, int startX, int startY, int targetX, int targetY) {
  std::pair<int, int> start = { startX, startY};
  std::pair<int, int> target = { targetX, targetY};
  int dx[] = {1, -1, 0, 0};  // Possible movements in x-direction
  int dy[] = {0, 0, 1, -1};  // Possible movements in y-direction
  std::vector<std::vector<std::pair<int, int>>> parent(20, std::vector<std::pair<int, int>>(12, {-1, -1}));
  std::queue<std::pair<int, int>> q;
  q.push(start);

  if (world.grid[targetX][targetY] != 0) {
    fprintf(stderr, "Not reachable!\n");
    return;
  }

  while (!q.empty()) {
    std::pair<int, int> curr = q.front();
    q.pop();

    if (curr == target) {
      // Reconstruct the path from target to start
      std::vector<std::pair<int, int>> path;
      while (curr.first != start.first || curr.second != start.second) {
        path.push_back(curr);
        curr = parent[curr.first][curr.second];
      }
      path.push_back(start);

      // update the pathQueue
      for (int i = path.size() - 1; i >= 0; --i) {
        pathQueue.push(path[i]);
      }
      return;
    }

    for (int i = 0; i < 4; ++i) {
      int newX = curr.first + dx[i];
      int newY = curr.second + dy[i];
      bool isValid =
        newX >= 0 &&
        newX < 20 &&
        newY >= 0 &&
        newY < 12 &&
        world.grid[newX][newY] == 0;

      if (isValid && parent[newX][newY].first == -1) {
        q.push({newX, newY});
        parent[newX][newY] = curr;
      }
    }
  }

  fprintf(stderr, "No path found!\n");
}

