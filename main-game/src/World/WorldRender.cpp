#include "World.h"

void World::render(Game& game) {
  BeginDrawing();
  // ClearBackground(RAYWHITE);
  ClearBackground(DARKGRAY);
  // DrawTexture(overworldBg, 0, 0, WHITE);

  Rectangle srcRect = {
    0,
    0,
    static_cast<float>(background.width),
    static_cast<float>(background.height)
  };
  Rectangle destRect = {
    0,
    0,
    static_cast<float>(game.settings.screenWidth),
    static_cast<float>((game.settings.screenHeight - game.settings.overworldUIHeight))
  };
  // DrawTexture(overworldBg, 0, 0, WHITE);
  DrawTexturePro(
      background,
      srcRect,
      destRect,
      { 0, 0 },
      0.0f,
      WHITE
      );

  // // Draw the grid (debug only)
  // for (int x = 0; x < columns; x++) {
  //   for (int y = 0; y < rows; y++) {
  //     // DrawRectangleLines(x, y, gridSize, gridSize, DARKGRAY);
  //     DrawRectangleLines(
  //         x * game.settings.gridWidth,
  //         y * game.settings.gridHeight,
  //         game.settings.gridWidth,
  //         game.settings.gridHeight,
  //         BLACK
  //         );
  //     //}
  //   }
  // }

  //Placeholder for testing
  // There should ideally be nothing to render, but this works as a placeholder
  for (TransitionTile* tTile : transitionTiles) {
    DrawRectangle(
      tTile->x * game.settings.gridWidth,
      tTile->y * game.settings.gridHeight,
      game.settings.gridWidth,
      game.settings.gridHeight,
      Color {100, 100, 100, 100}
      );
  }

  for (Entity* entity : entities) {
    // Call the render method for each object through the pointer
    entity->render(game.settings.gridWidth, game.settings.gridHeight);
  }

  // TODO: draw currentRoomId-fg.png here

  Vector2 mousePosition = GetMousePosition();
  int gridX = mousePosition.x / game.settings.gridWidth;
  int gridY = mousePosition.y / game.settings.gridHeight;
  for (int x = 0; x < columns; x++) {
    for (int y = 0; y < rows; y++) {
      // Check if mouse is over this grid tile
      if (x == gridX && y == gridY) {
        // DrawRectangle(x, y, settings.gridWidth, settings.gridHeight, ColorAlpha(WHITE, 30));
        Color highlightColor = {255, 255, 255, 75}; // Adjust the alpha value as needed
        DrawRectangle(
            x * game.settings.gridWidth,
            y * game.settings.gridHeight,
            game.settings.gridWidth,
            game.settings.gridHeight,
            highlightColor
            );
      }
    }
  }
  game.renderDialog();
  EndDrawing();
}

