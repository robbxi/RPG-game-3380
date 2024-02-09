#pragma once
#include "Entity.h"
// #include "Combat/Unit.h"
// #include "enums.h"
#include <string>
#include "World.h"
#include <queue>

class World;

class Player : public Entity {
  public:
    std::string facing;

    // For stopping movement during dialogue and such
    bool movable;

    Player(
        const std::string& playerId,
        int playerX,
        int playerY,
        std::string facing,
        Inventory playerInventory
        );

    std::queue<std::pair<int, int>> pathQueue = {};

    void processInput(Game&, World&);
    void move(int newX, int newY);

    // Shared
    void render(int gridWidth, int gridHeight);
    void update();

    void takeItems(Inventory itemsToTake);

  private:
    // Animation duration
    int animationDuration = 0;

    // Private Helpers to reduce redundancy
    std::string inputHelper(std::string facing);
    void resetAnimationDuration();
    void slowAnimation();
    void findShortestPath(World& world, int startX, int startY, int targetX, int targetY);

    // Others
    // void deleteDoor(World& world, Tile* doorTile);
};