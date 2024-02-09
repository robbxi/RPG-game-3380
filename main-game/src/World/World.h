// World.h
#pragma once

#include <string.h>
#include "../GameState.h"
#include "Room.h"
#include "Entity.h"
#include "Player.h"
#include "Tile.h"
#include "TransitionTile.h"
#include "../../external-libs/nlohmann/json.hpp"
#include "../Game.h"
#include "Inventory.h"
// class Game;
class Player;

class NarrationInfo {
  std::vector<std::string> dialogueLines;

  public:
    NarrationInfo() = default;
    ~NarrationInfo() = default;
    void addLine(const std::string& dialogueLine);
    void playNarrationLines(Game& game);
};

class World : public GameState {
  public:
    World(std::string roomId); // constructor
    ~World() override; // destructor

    void processInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

    int grid[20][12];
    // int rows = sizeof(grid) / sizeof(grid[0]);
    // int columns = sizeof(grid[0]) / sizeof(grid[0][0]);
    int columns = sizeof(grid) / sizeof(grid[0]);
    int rows = sizeof(grid[0]) / sizeof(grid[0][0]);

    std::vector<Room*> rooms;
    Room* currentRoom = nullptr;

    std::vector<Entity*> entities;
    std::vector<TransitionTile*> transitionTiles;
    std::vector<Player*> players;
    Player* player = nullptr;

    // these will only be used when starting a new game
    //// player data
    int playerX = 4;
    int playerY = 5;
    std::string playerFacing = "down";
    Inventory playerInventory;

    Texture2D background;

    void loadRoom(const std::string& roomId);

    // Helpers
    Room* buildRoom(const std::string& roomId, nlohmann::json source);
    void setRoom(Room* roomToSet);
    Room* findRoom(const std::string& roomId);
    // std::string inputHelper(std::string facing);
    // void findShortestPath(Game& game, int startX, int startY, int targetX, int targetY);

    void enterCombat(Game& game, const std::string& battleId);

    void sortGameObjects();
    void removeEntity(const std::string& tileId);
    void removeDoor(int doorX, int doorY);

    void transitionRoom(TransitionTile* transition);
    void startNarration(std::string roomId);
    void endNarration();

    void finalBattleSequence(Game& game);
    const std::string finalBattleId = "battle-005";

  private:
    int transitionTimer = -1;
    TransitionTile* destination = nullptr;
    Player* transitionPlayer = nullptr;
    void transitionHelper(Game& game);

    void setGridFromString(std::string roomInfo);
    void initializeWorld(std::string roomId);

    // -- Narrator data
    std::unordered_map<std::string, NarrationInfo*> narratorData; // Maps room id's to narration info
    bool narrationPlaying = false;
    bool timeToNarrate = false;
    void initializeNarrationData();
    void playNarrationSequence(Game& game);

    bool finalBattle = false;
};