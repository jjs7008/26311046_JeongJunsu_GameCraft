#pragma once
#include "Player.h"
#include "FallingObject.h"
#include <random>
#include <chrono>

enum class GameScreen { Title, Playing, GameOver, Clear };

class Game {
public:
    void Load();
    void Update();
    void Draw() const;
    void Unload();
private:
    GameScreen screen=GameScreen::Title;
    Player player;
    FallingObject parcel, hazard, hazard2;
    int score=0, elapsedFrames=0, stage=1;
    int stageFrames=0, stageIntroFrames=0, effectFrames=0;
    int courierTexture=-1,parcelTexture=-1,hazardTexture=-1;
    int titleTexture=-1,backgroundTextures[3]={-1,-1,-1};
    int gameOverTexture=-1, clearTexture=-1, uiFont=-1;
    bool previousEnter=false,previousEsc=false;
    std::mt19937 randomEngine{2026};
    using Clock = std::chrono::steady_clock;
    Clock::time_point previousTick{};
    bool clockStarted=false;
    double accumulator=0.0;
    void Step(const KEYCODE* key);
    void NewGame();
    void StartStage(int nextStage);
    void Respawn(FallingObject& obj, bool isHazard);
    bool Collides(const FallingObject& obj, float playerSize, float objectSize) const;
    int TargetScore() const;
};
