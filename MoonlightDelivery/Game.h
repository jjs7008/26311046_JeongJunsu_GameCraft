#pragma once
#include "Player.h"
#include "FallingObject.h"

enum class GameScreen { Title, Playing, GameOver, Clear };

class Game {
public:
    void Load();
    void Update();
    void Draw() const;
    void Unload();
private:
    GameScreen screen = GameScreen::Title;
    Player player;
    FallingObject parcel;
    FallingObject hazard;
    int courierTexture = -1, parcelTexture = -1, hazardTexture = -1;
    int titleTexture = -1, backgroundTexture = -1;
    int gameOverTexture = -1, clearTexture = -1;
    bool previousEnter = false, previousSpace = false, previousEsc = false;
    void StartPreview();
};
