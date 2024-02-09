#pragma once

#include <raylib.h>
#include <string>
#include "Inventory.h"
class Entity {
  public:
    std::string id;
    int x;
    int y;
    Inventory inventory;

    virtual std::pair<std::string, std::string> interact();
    virtual void render(int gridWidth, int gridHeight) = 0;
  protected:
    // Use this to render
    int animationFrame = 0;
    int animationRow = 0;
    int spriteWidth = 50; // Default value for preventing problems
    int spriteHeight = 50; // Default value for preventing problems
    float offsetX = 0;
    float offsetY = 0;
    float xScale = 1;
    float yScale = 1;
    Texture2D sprite;
    void renderHelper(int gridWidth, int gridHeight, bool flipped = false);
};