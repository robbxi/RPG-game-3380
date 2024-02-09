#include "Entity.h"

// For helping with rendering all types of entities
void Entity::renderHelper(int gridWidth, int gridHeight, bool flipped) {
  // As I am not sure where certain non-variable integers came from,
  // some things may need to be changed when we bring in a sprite
  Rectangle src = {
    static_cast<float>(animationFrame * gridWidth * xScale),
    static_cast<float>(spriteHeight * animationRow),
    static_cast<float>(gridWidth * xScale),
    static_cast<float>(gridHeight * yScale)
  };
  if (flipped) src.width *= -1;
  Rectangle dest = {
    static_cast<float>((x - offsetX) * gridWidth),
    static_cast<float>((y - offsetY) * gridHeight - offsetY),
    static_cast<float>(2 * gridWidth),
    static_cast<float>(3 * gridHeight),
  };
  DrawTexturePro(
      sprite,
      src,
      dest,
      {0, 0},
      0.0,
      WHITE
      );
  return;
}

std::pair<std::string, std::string> Entity::interact() {
  return std::make_pair("", "");
}