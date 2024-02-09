#pragma once
#include <string>
#include "Entity.h"
#include "Tile.h"
#include "TransitionTile.h"
#include "raylib.h"

struct Room {
    std::string roomId;

    Room() = default;

    Room(
      std::string id,
      std::string roomInfo,
      std::vector<Tile*> roomTiles,
      std::vector<TransitionTile*> roomTransitions,
      Texture2D roomBackground
    );

    std::string roomInfo;
    std::vector<Tile*> tiles;
    std::vector<TransitionTile*> transitionTiles;
    Texture2D background;

    void removeTile(const std::string& tileId);
    void removeDoor(int doorX, int doorY);
};