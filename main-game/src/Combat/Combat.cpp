#include "Combat.h"
#include "Action/Actions.h"
#include "../../external-libs/nlohmann/json.hpp"
#include <cstdio>
#include <raylib.h>
#include <string>

Combat::Combat(std::string combatId, Inventory playerInventory, Game &game)
    : backgroundImage(LoadTexture("assets/CombatBackground.png")) // Load the background image
{
  combatInventory = playerInventory;
  loadBattle(combatId, game);
}

Combat::~Combat()
{
  return;
}

void Combat::render(Game &game)
{
  BeginDrawing();
  int screenWidth = game.settings.screenWidth;
  int screenHeight = game.settings.screenHeight;
  Rectangle sourceRect = {0.0f, 0.0f, (float)backgroundImage.width, (float)backgroundImage.height};
  Rectangle destRect = {0.0f, 0.0f, 1920 / 2, 1080 / 2};
  // Draw Backgroung Image
  DrawTexturePro(backgroundImage, sourceRect, destRect, (Vector2){0, 0}, 0.0f, WHITE);

  // Renders Menu Boxes containing selectable actions
  // Menu contains (1) actions and can scroll through them
  RenderUI(screenWidth, screenHeight);

  // Renders Heros and Foes and stat symbols
  // if theres a better way to initilize pos then replace it
  // for now the usage of pos will be considered a placeholder
  RenderUnits(
      heroes,
      foes,
      screenWidth,
      screenHeight);
  game.renderDialog();
  EndDrawing();
}

void Combat::loadBattle(const std::string &battleId, Game &game)
{
  const std::string battleFilePath = "./json/battle/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = battleFilePath + battleId + jsonFileType;
  nlohmann::json root;
  std::ifstream jsonFile(fullFilePath);

  // Loads textures used for tokens
  loadTokenTextures();

  if (jsonFile.is_open())
  {
    try
    {
      jsonFile >> root;

      // Empty the output vector
      unitsFromJSON.clear();

      rewardKey = root["keyReward"];

      // Parse Enemies
      for (const auto &foeData : root["enemies"])
      {
        std::string foeId = foeData["id"].get<std::string>();

        if (foeId == "BerryWizard")
          game.gameWin = true;

        Foe *newFoe = createFoe(foeId);
        if (newFoe != nullptr)
        {
          fprintf(stderr, "Added foe w/ id:%s to foes\n", foeId.c_str());
          for (std::pair<std::string, int> action : newFoe->getActionList())
          {
            newFoe->actions.push_back(createAction(action.first, action.second));
          }
          newFoe->sprite = loadTexture(newFoe->id);
          foes.push_back(newFoe);
        }
        else
        {
          fprintf(stderr, "Invalid foeId: %s\n", foeId.c_str());
        }
      }
    }
    catch (const std::exception &e)
    {
      fprintf(stderr, "JSON parsing failed: %s\n", e.what());
    }
  }
  Hero *foxHero = new FoxHero();
  foxHero->sprite = loadTexture(foxHero->id);
  for (std::pair<std::string, int> action : foxHero->getActionList())
  {
    foxHero->actions.push_back(createAction(action.first, action.second));
  }
  heroes.push_back(foxHero);
}
