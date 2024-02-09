#include "Tile.h"
#include "../../external-libs/nlohmann/json.hpp"
#include "../Helper.h"

// ---------------------------------------------- Combat Tile
CombatTile::CombatTile(
    const std::string& tileId,
    int tileX,
    int tileY,
    bool isBlockMovement
) : Tile(tileId, tileX, tileY, isBlockMovement)
{
  // Additional constructor functionality to add to base constructor

  // Rendering values
  offsetX = 0;
  offsetY = 1;
  spriteWidth = 192; // 96 * 2
  spriteHeight = 240; // 80 * 3
  xScale = 6;
  yScale = 8;
  sprite = Helper::loadTexture("Overworld_Enemy.png");
}

std::pair<std::string, std::string> CombatTile::interact() {

  return Tile::interact();
}

// ---------------------------------------------- NPC Tile
NpcTile::NpcTile(
    const std::string& tileId,
    int tileX,
    int tileY,
    bool isBlockMovement
) : Tile(tileId, tileX, tileY, isBlockMovement)
{
  // Additional constructor functionality to add to base constructor
  const std::string npcFilePath = "./json/npc/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = npcFilePath + id + jsonFileType;
  nlohmann::json root;
  std::ifstream jsonFile(fullFilePath);
  std::string name;
  if (jsonFile.is_open()) {
    try {
      jsonFile >> root;
      // Parse NPC data
      name = root["name"].get<std::string>();

      for (const std::string& dialogueLine : root["text"]) {
        dialogueLines.push_back(name + ": " + dialogueLine.c_str());
      }
    }
    catch (const std::exception& e) {
      fprintf(stderr, "%s JSON parsing failed: %s\n", id, e.what());
    }
  }

  // Rendering values
  offsetX = 0;
  offsetY = 1;
  spriteWidth = 192; // 96 * 2
  spriteHeight = 240; // 80 * 3
  xScale = 6;
  yScale = 8;
  sprite = Helper::loadTexture(name + ".png");
}

std::vector<std::string> NpcTile::getDialogue() {
  return dialogueLines;
}

std::pair<std::string, std::string> NpcTile::interact() {
  return Tile::interact();
}

// ---------------------------------------------- Chest Tile
ChestTile::ChestTile(
    const std::string& tileId,
    int tileX,
    int tileY,
    bool isBlockMovement
) : Tile(tileId, tileX, tileY, isBlockMovement)
{
  const std::string chestFilePath = "./json/chest/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = chestFilePath + id + jsonFileType;
  nlohmann::json root;
  std::ifstream jsonFile(fullFilePath);
  if (jsonFile.is_open()) {
    try {
      jsonFile >> root;

      tileText = "Obtained:";

      int chestKeys = root["keys"];
      inventory.setKeys(chestKeys);
      if (inventory.hasKey()) tileText = tileText + " " + std::to_string(chestKeys) + " key \\\\";

      // Parse Chest
      for (const auto& itemData : root["items"]) {
        std::string itemID = itemData["id"].get<std::string>();
        int quantity = itemData["quantity"].get<int>();
        tileText = tileText + " " + std::to_string(quantity) + " " + itemID.c_str() + " \\\\";

        // TODO: Fill chest inventory here:
        inventory.AddItem(itemID, quantity);
      }
    }
    catch (const std::exception& e) {
      fprintf(stderr, "JSON parsing failed: %s\n", e.what());
    }
  }

  // Rendering values
  offsetX = 0.8;
  offsetY = 1.1;
  spriteWidth = 16;
  spriteHeight = 14;
  xScale = 0.8;
  yScale = 1.2;
  sprite = Helper::loadTexture("Chest.png");
}

// ---------------------------------------------- Door Tile
DoorTile::DoorTile(
    const std::string& tileId,
    int tileX,
    int tileY,
    bool isBlockMovement
) : Tile(tileId, tileX, tileY, isBlockMovement)
{
  // Additional constructor functionality to add to base constructor

  // Rendering values
  spriteWidth = 400;
  spriteHeight = 400;
  sprite = Helper::loadTexture("door.png");
}

void DoorTile::render(int gridWidth, int gridHeight) {
  Rectangle src = {
    static_cast<float>(0),
    static_cast<float>(0),
    static_cast<float>(spriteWidth),
    static_cast<float>(spriteHeight)
  };
  Rectangle dest = {
    static_cast<float>(x * gridWidth),
    static_cast<float>(y * gridHeight),
    static_cast<float>(gridWidth),
    static_cast<float>(gridHeight),
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