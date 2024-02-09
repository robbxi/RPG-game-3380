#pragma once
#include <string>

struct TransitionTile {
    int x, y;
    int enterX, enterY;
    std::string destinationRoomId;

    TransitionTile(
        int x,
        int y,
        int enterX,
        int enterY,
        const std::string& destinationRoomId
        ) :
      x(x),
      y(y),
      enterX(enterX),
      enterY(enterY),
      destinationRoomId(destinationRoomId) {}
};