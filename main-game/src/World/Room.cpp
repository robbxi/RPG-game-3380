#include "Room.h"
#include <algorithm>

Room::Room(
  std::string id,
  std::string roomInfo,
  std::vector<Tile*> roomTiles,
  std::vector<TransitionTile*> roomTransitions,
  Texture2D roomBackground
) {
  roomId = id;
  this->roomInfo = roomInfo;
  tiles = roomTiles;
  transitionTiles = roomTransitions;
  background = roomBackground;
}

void Room::removeTile(const std::string& tileId) {
  auto found = [tileId](Tile* tile) {
    return (tile->id == tileId);
  };
  auto foundTile = std::find_if(tiles.begin(), tiles.end(), found);
  tiles.erase(foundTile);
}

void Room::removeDoor(int doorX, int doorY) {
  auto tileIt = tiles.begin();
  // Delete the door and all adjacent doors
  while (tileIt !=  tiles.end()) {
    int checkX = (*tileIt)->x;
    int checkY = (*tileIt)->y;
    if (  (*tileIt)->id == "door" &&
        (
          ( checkX == doorX + 1 && checkY == doorY     ) ||
          ( checkX == doorX - 1 && checkY == doorY     ) ||
          ( checkX == doorX     && checkY == doorY + 1 ) ||
          ( checkX == doorX     && checkY == doorY - 1 ) ||
          ( checkX == doorX     && checkY == doorY     )
        ) ) {
      tileIt = tiles.erase(tileIt);
    }
    else ++tileIt;
  }
}