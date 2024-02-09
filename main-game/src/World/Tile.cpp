// Tile.cpp
#include "Tile.h"
#include "../Helper.h"

Tile::Tile(
    const std::string& tileId,
    int tileX,
    int tileY,
    bool isBlockMovement
    ) :
  isBlockMovement(isBlockMovement)
{
  id = tileId;
  x = tileX;
  y = tileY;
}

std::pair<std::string, std::string> Tile::interact() {
  std::string tileType = Helper::parseGameObjectType(id);
  return std::make_pair(tileType, tileText);
}

void Tile::render(int gridWidth, int gridHeight) {
  renderHelper(gridWidth, gridHeight);
}
