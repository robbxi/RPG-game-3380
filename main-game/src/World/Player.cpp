// Player.cpp
#include "Player.h"
#include "../Helper.h"
#include <cstdio>
#include "Inventory.h"
Player::Player(
    const std::string& playerId,
    int playerX,
    int playerY,
    std::string facing,
    Inventory playerInventory
    ) :
  facing(facing)
{
  id = playerId;
  x = playerX;
  y = playerY;
  inventory = playerInventory;
  sprite = Helper::loadTexture("fox.png");
  movable = true;

  // Rendering values
  offsetX = 0.5;
  offsetY = 2;
  spriteWidth = 192; // 96 * 2
  spriteHeight = 240; // 80 * 3
  xScale = 4;
  yScale = 6;
  ItemAssets::Initialize();
}

void Player::render(int gridWidth, int gridHeight) {
  // BUG: left-facing fox animates backwards

  if (animationFrame > 2 || animationFrame < 0) {
    fprintf(stderr, "Player animation frame (%i) invalid\n", animationFrame);
    animationFrame = 0;
  }

  bool flipped = false;
  if (facing == "right") {
    animationRow = 0;
  }
  else if (facing == "down") {
    animationRow = 1;
  }
  else if (facing == "up") {
    animationRow = 2;
  }
  else if (facing == "left") {
    animationRow = 0;
    flipped = true;
  }
  renderHelper(gridWidth, gridHeight, flipped);
  return;
}

void Player::move(int newX, int newY) {
  x = newX;
  y = newY;
}

void Player::update() {
  if (animationDuration > 0) {
    animationDuration -= 1;
    return;
  }
  else if (!movable) slowAnimation();
  else resetAnimationDuration();
  if (animationFrame > 0) animationFrame -= 1;
  else animationFrame = 2;

  // Continue moving along the path until the queue is empty
  while (!pathQueue.empty()) {
    std::pair<int, int> nextPos = pathQueue.front();
    pathQueue.pop();
    if (nextPos.first < x) {
      facing = "left";
    }
    else if (nextPos.first > x) {
      facing = "right";
    }
    else if (nextPos.second < y) {
      facing = "up";
    }
    else if (nextPos.second > y) {
      facing = "down";
    }
    move(nextPos.first, nextPos.second);
    resetAnimationDuration();
    break;
  }
}

void Player::resetAnimationDuration() {
  animationDuration += 10;
}
void Player::slowAnimation() {
  animationDuration += 30;
}

void Player::takeItems(Inventory itemsToTake) {
  for (const auto& item : itemsToTake.GetItems()) {
    inventory.AddItem(item.first, item.second);
  }
}