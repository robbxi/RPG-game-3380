#pragma once
#include "../GameState.h"
#include "../Game.h"

class MainMenu : public GameState {
   private:
    bool isNewGame = true;
    double menuStartTime;  
    Texture2D start_img;
    Font font;
    Font titlefont;
    Font winFont;
    Texture2D treeTexture;
    Texture2D foxTexture;
    Rectangle frameRec;
    Rectangle destRec;
    Rectangle destRec2;
    Rectangle foxFrameRec;
    Vector2 foxPosition;
    int foxFrameWidth;
    int foxFrameHeight;
    bool foxReachedCenter;  
    int framesCounter;      
    float bounceHeight;
    float bounceSpeed;
    float bounceTime;
    int frameWidth;
    int frameHeight;
    float scaleFactor;
    float foxSpeed;
    Texture2D exitButtonTexture;
    Rectangle exitButton;
    const char* exitButtonText;
    float titlePosY;
    Vector2 treePosition;
    Vector2 treePosition2;
    std::string projectText;
    std::string foxText;
    std::string startText;

    void updateGameOver(Game& game);
    void renderGameOver(Game& game);
    void updateMain(Game& game);
    void renderMain(Game& game);

  public:
    int screenWidth = 1920 / 2;
    int screenHeight = 1080 / 2;
    MainMenu();
    ~MainMenu() override; // destructor

    void processInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;
    //For button popup
     bool showConfirmationScreen = false;
    Rectangle yesButton;
    Rectangle noButton;
    const char* yesButtonText = "Yes";
    const char* noButtonText = "No";
    std::string confirmationText = "Are you sure?";
    int popupWidth;
    int popupHeight;

};


