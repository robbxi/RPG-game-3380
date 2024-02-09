//CombatRender.cpp
//Helper Class
#include "Combat.h"
#include "Unit.h"
#include <cstdio>
#include <raylib.h>


std::vector<std::string> combatInputTutorial =
{
  "p --- select",
  "o --- confirm selection",
  "l --- cancels selection"
};

void rUnitSprite(Texture2D sprite, int pos, int screenWidth, int screenHeight)
{
    int spriteWidth = 171;
    int spriteHeight = 236;
    Rectangle src = {
      0,
      0,
      static_cast<float>(spriteWidth),
      static_cast<float>(spriteHeight)
    };

    Rectangle dest = {
      static_cast<float>(pos),
      static_cast<float>(0.30 * screenHeight),
      static_cast<float>(screenWidth/10), //sizes are planned to change
      static_cast<float>(screenHeight/4), //sizes are planned to change
    };

    //render's hero's position
    DrawTexturePro(
    sprite,
    src,
    dest,
    {0, 0},
    0.0,
    WHITE
    );
}

void rTokenSprite (Texture2D sprite, int pos, int screenWidth, int screenHeight)
{
  int spriteWidth = 80;
  int spriteHeight = 80;
  Rectangle src = {
      0,
      0,
      static_cast<float>(spriteWidth),
      static_cast<float>(spriteHeight)
    };

  Rectangle dest = {
      static_cast<float>(pos),
      static_cast<float>(0.18 * screenHeight),
      static_cast<float>(spriteWidth/4), //sizes are planned to change
      static_cast<float>(spriteHeight/4), //sizes are planned to change
    };
  
  DrawTexturePro(
    sprite,
    src,
    dest,
    {0, 0},
    0.0,
    WHITE
    );
}


// Combat Helpers //
//loadTexture
Texture2D Combat::loadTexture(std::string filePath) 
{
  std::string fileType = ".png";
  std::string fullFilePath = "./assets/combat/" + filePath + fileType;
  return LoadTexture(fullFilePath.c_str());
}

//RenderUI
void Combat::RenderUI(int screenWidth, int screenHeight)
{
  //first renders the boxes
    //Stat box bellow units
  DrawRectangle(
    screenWidth - screenWidth*0.98,
    screenHeight - screenHeight*0.40,
    screenWidth*0.96,
    screenHeight*0.28,
    GRAY
  );
    //Box Showing Available Actions
  DrawRectangle(
    screenWidth - screenWidth*0.96,
    screenHeight - screenHeight*0.38,
    screenWidth*0.30,
    screenHeight*0.25,
    ORANGE
  );
    //Box containing actions descriptions
  DrawRectangle(
    screenWidth - screenWidth*0.65,
    screenHeight - screenHeight*0.38,
    screenWidth*0.62,
    screenHeight*0.25,
    ORANGE
  );

  //renders the actions
  if(currentUnit != nullptr && isHero(currentUnit)) {
    std::vector<std::string> actionBox = {};
    for(std::pair<std::string,int> list : currentUnit->actionList)
    {
      actionBox.push_back(list.first);
    }

    if (selected > 3) {
      for (int i = selected - 3 ; i>0 ; i--) {
        actionBox.erase(actionBox.begin());
      }
    }

    while (actionBox.size() > 4) actionBox.pop_back();

    int pos = 0;
    if(currentUnit->item) {
      for(std::string item : itemList) {
        std::string itemText = item + "     " + std::to_string(combatInventory.GetItem(item));
        DrawText(
          itemText.c_str(),
          screenWidth - (screenWidth*0.96 - 20),  // X position of the text
          screenHeight - (screenHeight*0.38 - (25*pos)),  // Y position of the text
          28,  // Font size
          WHITE
          );
          pos++;
      }
    }
    else {
      for(std::string actions : actionBox) {
          DrawText(
          actions.c_str(),
          screenWidth - (screenWidth*0.96 - 20),  // X position of the text
          screenHeight - (screenHeight*0.38 - (25*pos)),  // Y position of the text
          28,  // Font size
          WHITE
          );
        pos++;
      }
    }

    Action* action = currentUnit->getAction();
    
    //renders the action descriptions
    int i = 0;
    if (highlightedAction != nullptr || action != nullptr && !action->actionDesc.empty()) {
      std::vector<std::string> actionDesc = currentUnit->actions[selected]->actionDesc;
      for (std::string line : actionDesc) {
        DrawText(
        line.c_str(),
        screenWidth - screenWidth*0.64,  // X position of the text
        screenHeight - (screenHeight*0.38 - (25*i)),  // Y position of the text
        28,  // Font size
        WHITE
      );
      i++;
      }   
    }
    else {
      // shows instructions
      for (std::string line : combatInputTutorial) {
        DrawText(
        line.c_str(),
        screenWidth - screenWidth*0.64,  // X position of the text
        screenHeight - (screenHeight*0.38 - (25*i)),  // Y position of the text
        28,  // Font size
        WHITE
      );
      i++;
      }
    }
    //renders the pointer (use selected)
    if (action == nullptr && highlightedAction != nullptr) {
      int pos = selected;
      if (selected > 3) pos = 3;
      DrawRectangle(
        screenWidth - (screenWidth*0.96),
        screenHeight - (screenHeight*0.38 - (25*pos)),
        10,
        10,
        BLUE
      );
    }
    else if (highlightedTarget != nullptr) {
      DrawRectangle(
        screenWidth/2 + (96*(selected) + 32*(selected+1)),
        screenHeight*0.10,
        10,
        10,
        RED
      );
    }
  }  

  

}

//Render Units
void Combat::RenderUnits
(
  std::vector<Unit*> heroes,
  std::vector<Unit*> foes,
  int screenWidth,
  int screenHeight
)
{
  int pos = 0;
  for (Unit* hero : heroes)
  {
    hero->RenderSprite(
      hero->sprite,
      hero->hp,
      hero->getMaxHp(),
      hero->energy,
      screenWidth,
      screenHeight,
      pos,
      hero->tokens,
      isHero(hero),
      isFoe(hero)
    );
    pos++;
  }
  pos = 0;
  for (Unit* foe : foes)
  {
    foe->RenderSprite(
      foe->sprite,
      foe->hp,
      foe->getMaxHp(),
      foe->energy,
      screenWidth,
      screenHeight, 
      pos,
      foe->tokens,
      isHero(foe),
      isFoe(foe));
    pos++;
  }
}

// Unit Helpers //
//Render Unit Sprites
void Unit::RenderSprite
( 
  Texture2D sprite,
  int hp,
  int maxHp,
  int energy,
  int screenWidth,
  int screenHeight, 
  int pos,
  std::vector<Token*> tokens,
  bool isHero,
  bool isFoe
)
{
  if(isHero)
  {
    pos = screenWidth/2 - (96*(pos+1) + (32*pos+1));
    rUnitSprite(sprite, pos, screenWidth, screenHeight);

    //render's hero's stats
    //health TODO: improve this line?
    const std::string healthText = (std::to_string(hp) + "/" + std::to_string(maxHp));
    DrawText(
      healthText.c_str(),
      pos,  // X position of the text
      0.25 * screenHeight,  // Y position of the text
      20,  // Font size
      WHITE
      );
    //energy
    //TODO: add energy render

    //renders tokens if available
    int i = 0;
    for(Token* token : tokens) {
      int tokenPos = pos + (i * 21);
      rTokenSprite(
        token->sprite,
        tokenPos,
        screenWidth,
        screenHeight
        );
      i++;
      }      
    }
  else if (isFoe) 
  {
    pos = screenWidth/2 + (96*(pos) + 32*(pos+1));
    rUnitSprite(sprite, pos, screenWidth, screenHeight);

    //render's foe's stats
    //health
    //TODO: improve this line of code
    const std::string healthText = (std::to_string(hp) + "/" + std::to_string(maxHp));
    DrawText(
        healthText.c_str(),
        pos,  // X position of the text
        0.25 * screenHeight,  // Y position of the text
        20,  // Font size
        WHITE
        );
    //energy
    //TODO: add energy render
    //renders tokens if available
    int i = 0;
    for(Token* token : tokens) {
      int tokenPos = pos + (i * 21);

      rTokenSprite(
        token->sprite,
        tokenPos,
        screenWidth,
        screenHeight
        );
      i++;
    }
  }
  return;
}