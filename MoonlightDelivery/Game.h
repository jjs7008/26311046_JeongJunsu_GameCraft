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
    FallingObject parcel, hazard;
    int score=0, elapsedFrames=0, nextTarget=100;
    int courierTexture=-1,parcelTexture=-1,hazardTexture=-1;
    int titleTexture=-1, backgroundTexture=-1,gameOverTexture=-1, clearTexture=-1;
    int uiFont=-1;
    bool previousEnter=false,previousEsc=false;
    std::mt19937 randomEngine{2026};
    using Clock = std::chrono::steady_clock;
    Clock::time_point previousTick{};
    bool clockStarted=false;
    double accumulator=0.0;
    void Step(const KEYCODE* key);
    void NewGame();
    void Respawn(FallingObject& obj, bool isHazard);
    bool Collides(const FallingObject& obj, float playerSize, float objectSize) const;
};
