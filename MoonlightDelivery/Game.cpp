#include "Game.h"
#include <cstdio>
#include <cmath>

void Game::Load() {
    courierTexture=g2_TextureLoad("Texture/courier.png");
    parcelTexture=g2_TextureLoad("Texture/parcel.png");
    hazardTexture=g2_TextureLoad("Texture/hazard.png");
    titleTexture=g2_TextureLoad("Texture/title.png");
    backgroundTexture=g2_TextureLoad("Texture/background.png");
    gameOverTexture=g2_TextureLoad("Texture/gameover.png");
    clearTexture=g2_TextureLoad("Texture/clear.png");
    uiFont=g2_FontCreate("Arial",22,0);
    screen=GameScreen::Title;
}

void Game::Respawn(FallingObject& obj, bool isHazard) {
    std::uniform_int_distribution<int> lanePick(0,2);
    std::uniform_int_distribution<int> offset(0,130);
    int lane=lanePick(randomEngine);
    if(isHazard && lane==parcel.lane) lane=(lane+1)%3;
    const float baseSpeed=isHazard?1.55f:1.30f;
    obj.Reset(lane,-60.0f-static_cast<float>(offset(randomEngine)),baseSpeed,isHazard);
}

void Game::NewGame() {
    player.Reset(); score=0; elapsedFrames=0;
    nextTarget=100;
    parcel.Reset(0,-80.0f,1.30f,false);
    hazard.Reset(2,-350.0f,1.55f,true);
    screen=GameScreen::Playing;
}

bool Game::Collides(const FallingObject& obj,float playerSize,float objectSize) const {
    // Images are positioned by their upper-left corner.
    return player.x < obj.x+objectSize &&
           player.x+playerSize > obj.x &&
           player.y < obj.y+objectSize &&
           player.y+playerSize > obj.y;
}

void Game::Update() {
    using Clock = std::chrono::steady_clock;
    const auto now = Clock::now();
    if(!clockStarted) { previousTick=now; clockStarted=true; }
    double frameSeconds = std::chrono::duration<double>(now-previousTick).count();
    previousTick = now;
    // Do not fast-forward the game after an inactive/pause window.
    if(frameSeconds > 0.10) frameSeconds = 0.10;
    accumulator += frameSeconds;
    const KEYCODE* key=g2_GetKeyboard();
    const bool enter=key[VK_RETURN]!=0;
    const bool esc=key[VK_ESCAPE]!=0;
    if(screen==GameScreen::Title) {
        if(enter && !previousEnter) NewGame();
    } else if(screen==GameScreen::Playing) {
        if(esc && !previousEsc) screen=GameScreen::Title;
    } else {
        if(enter && !previousEnter) NewGame();
        if(esc && !previousEsc) screen=GameScreen::Title;
    }
    previousEnter=enter;
    previousEsc=esc;

    // Fixed 60-Hz simulation, independent of monitor refresh rate / FPS.
    constexpr double fixedStep = 1.0 / 60.0;
    while(accumulator >= fixedStep) {
        if(screen==GameScreen::Playing) Step(key);
        accumulator -= fixedStep;
    }
}

void Game::Step(const KEYCODE* key) {
    ++elapsedFrames;
    player.Update(key);
    parcel.Update();
    hazard.Update();
    if(Collides(parcel,56.0f,40.0f)) {
        score+=10;
        Respawn(parcel,false);
    } else if(parcel.IsOffScreen()) Respawn(parcel,false);
    if(Collides(hazard,56.0f,48.0f)) {
        if(player.TakeDamage()) Respawn(hazard,true);
    } else if(hazard.IsOffScreen()) Respawn(hazard,true);
    if(player.hp<=0) screen=GameScreen::GameOver;
    else if(score>=nextTarget) screen=GameScreen::Clear;
}

void Game::Draw() const {
    RECT full={0,0,800,600};
    if(screen==GameScreen::Title) {
        g2_Draw2D(titleTexture,&full);
        if(uiFont>=0) g2_FontDrawText(uiFont,{220,520},0xFFFFFFFF,"ENTER - START");
        return;
    }
    if(screen==GameScreen::GameOver) {
        g2_Draw2D(gameOverTexture,&full);
        if(uiFont>=0) g2_FontDrawText(uiFont,{230,530},0xFFFFFFFF,"ENTER - RETRY / ESC - MENU");
        return;
    }
    if(screen==GameScreen::Clear) {
        g2_Draw2D(clearTexture,&full);
        if(uiFont>=0) g2_FontDrawText(uiFont,{230,530},0xFFFFFFFF,"ENTER - RETRY / ESC - MENU");
        return;
    }
    g2_Draw2D(backgroundTexture,&full);
    parcel.Draw(parcelTexture);
    hazard.Draw(hazardTexture);
    player.Draw(courierTexture);
    if(uiFont>=0) {
        g2_FontDrawText(uiFont,{640,16},0xFFFFFFFF,"SCORE: %d / %d",score,nextTarget);
        g2_FontDrawText(uiFont,{330,16},0xFFFFFFFF,"HP: %d",player.hp);
        g2_FontDrawText(uiFont,{540,16},0xFFFFFFFF,"TIME: %d",elapsedFrames/60);
        g2_FontDrawText(uiFont,{20,560},0xFFFFFFFF,"WASD / ARROWS: MOVE    ESC: MENU");
    }
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
