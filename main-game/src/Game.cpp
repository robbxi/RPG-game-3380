// Game.cpp
#include "Game.h"
#include <cstdio>
#include "World/Inventory.h"
Game::Game() {
  InitWindow(settings.screenWidth, settings.screenHeight, "Project: Fox");
  // SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  SetTargetFPS(60);

  // IMPORTANT: Any texture loading have to go after InitWindow

  // set initial game state
  gameOver = false;
  gameWin = false;
  GameState* newState = new MainMenu();
  currentState = newState;
}

Game::~Game() {
  delete currentState;
  delete world;

  CloseWindow();
}


void Game::run() {
  while (!WindowShouldClose()) {
    if (currentState != nullptr) {
      currentState->processInput(*this);
      currentState->update(*this);
      currentState->render(*this);
    }
  }
}

void Game::changeState(GameState* newGameState) {
  if (newGameState == currentState) return;
  if (currentState != world) {
    delete currentState;
  }
  currentState = newGameState;
}

void Game::renderDialog() {
  bool isHover = (GetMousePosition().y / settings.gridHeight) >= 12;
  if (!dialogQueue.empty()) {
    // Draw a dialogue box
    DrawRectangle(
        0,
        settings.screenHeight - settings.overworldUIHeight,
        settings.screenWidth,
        settings.overworldUIHeight,
        DARKGRAY
        );
    if (isHover) {
      Color highlightColor = {255, 255, 255, 75}; // Adjust the alpha value as needed
      DrawRectangle(
          0,
          settings.screenHeight - settings.overworldUIHeight,
          settings.screenWidth,
          settings.overworldUIHeight,
          highlightColor
          );
    }
    else {
    }
    // Draw the current dialog text
    DrawText(
        dialogQueue.front().c_str(),
        10,  // X position of the text
        settings.screenHeight - settings.overworldUIHeight + 10,  // Y position of the text
        20,  // Font size
        WHITE
        );
  }
}


// TODO: Remember to construct room background filepaths when loading room vector from save
void Game::loadSave(const std::string& filename) {
  const std::string saveFilePath = "./save/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = saveFilePath + filename + jsonFileType;
  nlohmann::json root;

  // Read the JSON data from the file
  std::ifstream inputFile(fullFilePath);

  if (inputFile.is_open()) {
    // Parse the JSON data
    try {
      inputFile >> root;

      // World Data
      nlohmann::json worldData = root["WorldData"];
      dynamic_cast<World*>(world)->players.clear();
      for (const auto& pc : worldData["Players"]) {
        std::string pcId = pc["id"];
        int pcX = pc["x"];
        int pcY = pc["y"];
        std::string pcFacing = pc["facing"];
        Inventory pcInventory;
        for (const auto& jsonItem : pc["Inventory"]) {
          pcInventory.AddItem(jsonItem["id"], jsonItem["quantity"]);
        }
        pcInventory.addKeys(pc["Keys"]);
        Player* PC = new Player(
          pcId, pcX, pcY, pcFacing, pcInventory
        );
        dynamic_cast<World*>(world)->players.push_back(PC);
        // TODO: If we add more "player" objects, then we need to alter this. We've only ever had 1, so this works fine.
        dynamic_cast<World*>(world)->player = PC;
      }
      dynamic_cast<World*>(world)->rooms.clear();
      for (const auto& room : worldData["Rooms"]) {
        Room* newRoom = dynamic_cast<World*>(world)->buildRoom(room["room"], room);
        dynamic_cast<World*>(world)->rooms.push_back(newRoom);
      }
      Room* roomToSet = dynamic_cast<World*>(world)->findRoom(worldData["currentRoomId"]);
      dynamic_cast<World*>(world)->endNarration();
      dynamic_cast<World*>(world)->setRoom(roomToSet);

      inputFile.close();
    }
    catch (const std::exception& e) {
      fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      inputFile.close();
    }
  }
  else {
    fprintf(stderr, "Unable to open file for reading\n");
  }
}

void Game::saveSave(const std::string& filename) {
  const std::string saveFilePath = "./save/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = saveFilePath + filename + jsonFileType;
  nlohmann::json root;

  // Serialize member data to JSON
  root["WorldData"] = nlohmann::json::object();
  root["WorldData"]["currentRoomId"] = dynamic_cast<World*>(world)->currentRoom->roomId;

  // -------- WorldData members
  root["WorldData"]["Players"] = nlohmann::json::array();
  root["WorldData"]["Rooms"] = nlohmann::json::array();

  for (Player* player : dynamic_cast<World*>(world)->players) {
    nlohmann::json playerInfo = nlohmann::json::object( {
      {"id", player->id},
      {"x", player->x},
      {"y", player->y},
      {"facing", player->facing}
    });
    playerInfo["Inventory"] = nlohmann::json::array();
    for (const auto& item : player->inventory.GetItems()) {
      nlohmann::json jsonItem = nlohmann::json::object({
        {"id", item.first},
        {"quantity", item.second}
      });
      playerInfo["Inventory"].push_back(jsonItem);
    }
    playerInfo["Keys"] = player->inventory.getKeys();
    root["WorldData"]["Players"].push_back(playerInfo);
  }

  // Fill room data
  for (Room* room : dynamic_cast<World*>(world)->rooms) {
    nlohmann::json roomData = nlohmann::json::object({
      {"room", room->roomId}, {"roomInfo", room->roomInfo}
    });

    roomData["specialTiles"] = nlohmann::json::array();
    for (Tile* tile : room->tiles) {
      roomData["specialTiles"].push_back(nlohmann::json::array({
        tile->id, tile->isBlockMovement, tile->x, tile->y
      }));
    }
    roomData["transitionTiles"] = nlohmann::json::array();
    for (TransitionTile* transitionTile : room->transitionTiles) {
      roomData["transitionTiles"].push_back(nlohmann::json::array({
        transitionTile->destinationRoomId,
        transitionTile->x, transitionTile->y,
        transitionTile->enterX, transitionTile->enterY
      }));
    }
    root["WorldData"]["Rooms"].push_back(roomData);
  }
  //Inventory

  // Create a JSON writer
  std::ofstream outputFile(fullFilePath);

  if (outputFile.is_open()) {
    // Write JSON to the output file
    outputFile << root.dump(2); // Pretty print with 2 spaces
    outputFile.close();
  }
  else {
    fprintf(stderr, "Unable to open the file for writing\n");
  }
}

void Game::startNewGame() {
  world = new World(startingRoomId);
  changeState(world);
}