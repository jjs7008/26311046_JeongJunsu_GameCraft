#include "Game.h"

void Game::Load() {
    courierTexture = g2_TextureLoad("Texture/courier.png");
    parcelTexture = g2_TextureLoad("Texture/parcel.png");
    hazardTexture = g2_TextureLoad("Texture/hazard.png");
    titleTexture = g2_TextureLoad("Texture/title.png");
    backgroundTexture = g2_TextureLoad("Texture/background.png");
    gameOverTexture = g2_TextureLoad("Texture/gameover.png");
    clearTexture = g2_TextureLoad("Texture/clear.png");
    StartPreview();
    screen = GameScreen::Title;
}

void Game::StartPreview() {
    player.Reset();
    parcel.Reset(200.0f, -30.0f, 2.5f);
    hazard.Reset(550.0f, -280.0f, 3.0f);
}

void Game::Update() {
    const KEYCODE* key = g2_GetKeyboard();
    const bool enter = (key[VK_RETURN] != 0);
    const bool space = (key[VK_SPACE] != 0);
    const bool esc = (key[VK_ESCAPE] != 0);
    if (screen == GameScreen::Title) {
        if (enter && !previousEnter) { StartPreview(); screen = GameScreen::Playing; }
    } else if (screen == GameScreen::Playing) {
        player.Update(key);
        parcel.Update();
        hazard.Update();
        // Temporary screen previews for Week 2, not gameplay win/loss rules.
        if (space && !previousSpace) screen = GameScreen::GameOver;
        if (esc && !previousEsc) screen = GameScreen::Title;
    } else {
        if (enter && !previousEnter) screen = GameScreen::Title;
        if (esc && !previousEsc) screen = GameScreen::Title;
    }
    previousEnter = enter; previousSpace = space; previousEsc = esc;
}

void Game::Draw() const {
    if (screen == GameScreen::Title) { { RECT full = {0, 0, 800, 600}; g2_Draw2D(titleTexture, &full); } return; }
    if (screen == GameScreen::GameOver) { { RECT full = {0, 0, 800, 600}; g2_Draw2D(gameOverTexture, &full); } return; }
    if (screen == GameScreen::Clear) { { RECT full = {0, 0, 800, 600}; g2_Draw2D(clearTexture, &full); } return; }
    { RECT full = {0, 0, 800, 600}; g2_Draw2D(backgroundTexture, &full); }
    parcel.Draw(parcelTexture);
    hazard.Draw(hazardTexture);
    player.Draw(courierTexture);
}

void Game::Unload() {
    g2_TextureRelease(courierTexture);
    g2_TextureRelease(parcelTexture);
    g2_TextureRelease(hazardTexture);
    g2_TextureRelease(titleTexture);
    g2_TextureRelease(backgroundTexture);
    g2_TextureRelease(gameOverTexture);
    g2_TextureRelease(clearTexture);
}
