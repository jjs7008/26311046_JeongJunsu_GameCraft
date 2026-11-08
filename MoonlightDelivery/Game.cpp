#include "Game.h"
#include <cstdio>
#include <cmath>

void Game::Load() {
    courierTexture=g2_TextureLoad("Texture/courier.png");
    parcelTexture=g2_TextureLoad("Texture/parcel.png");
    hazardTexture=g2_TextureLoad("Texture/hazard.png");
    titleTexture=g2_TextureLoad("Texture/title.png");
    backgroundTextures[0]=g2_TextureLoad("Texture/background.png");
    backgroundTextures[1]=g2_TextureLoad("Texture/background_stage2.png");
    backgroundTextures[2]=g2_TextureLoad("Texture/background_stage3.png");
    gameOverTexture=g2_TextureLoad("Texture/gameover.png");
    clearTexture=g2_TextureLoad("Texture/clear.png");
    uiFont=g2_FontCreate("Arial",22,0);
    screen=GameScreen::Title;
}

int Game::TargetScore() const {
    static const int thresholds[3]={50,110,180};
    return thresholds[stage-1];
}

void Game::Respawn(FallingObject& obj, bool isHazard) {
    std::uniform_int_distribution<int> lanePick(0,2);
    std::uniform_int_distribution<int> offset(0,140);
    int lane=lanePick(randomEngine);
    if(isHazard && lane==parcel.lane) lane=(lane+1)%3;
    float baseSpeed=isHazard?1.55f:1.30f;
    baseSpeed+=(stage-1)*(isHazard?0.46f:0.28f);
    obj.Reset(lane,-60.0f-static_cast<float>(offset(randomEngine)),baseSpeed,isHazard);
}

void Game::StartStage(int nextStage) {
    stage=nextStage;
    stageFrames=0;
    stageIntroFrames=120; // two-second stage label
    player.invincibleFrames=90; // avoid instant repeated damage on transition
    Respawn(parcel,false);
    Respawn(hazard,true);
    if(stage>=2) {
        Respawn(hazard2,true);
        hazard2.y=-390.0f; // stagger the two obstacles
    } else {
        hazard2.active=false;
    }
}

void Game::NewGame() {
    player.Reset();
    score=0;
    elapsedFrames=0;
    effectFrames=0;
    stage=1;
    StartStage(1);
    // Initial spacing makes the first seconds of the game approachable.
    parcel.Reset(0,-80.0f,1.30f,false);
    hazard.Reset(2,-350.0f,1.55f,true);
    hazard2.active=false;
    screen=GameScreen::Playing;
    accumulator=0.0;
}

bool Game::Collides(const FallingObject& obj,float playerSize,float objectSize) const {
    if(!obj.active) return false;
    return player.x < obj.x+objectSize &&
           player.x+playerSize > obj.x &&
           player.y < obj.y+objectSize &&
           player.y+playerSize > obj.y;
}

void Game::Update() {
    using Clock = std::chrono::steady_clock;
    const auto now=Clock::now();
    if(!clockStarted) {previousTick=now; clockStarted=true;}
    double frameSeconds=std::chrono::duration<double>(now-previousTick).count();
    previousTick=now;
    if(frameSeconds>0.10) frameSeconds=0.10;
    accumulator+=frameSeconds;
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
    constexpr double fixedStep=1.0/60.0;
    // Clamp accumulated time to prevent long catch-up loops.
    if(accumulator>0.15) accumulator=0.15;
    while(accumulator>=fixedStep) {
        if(screen==GameScreen::Playing) Step(key);
        accumulator-=fixedStep;
    }
}

void Game::Step(const KEYCODE* key) {
    ++elapsedFrames;
    ++stageFrames;
    if(stageIntroFrames>0) --stageIntroFrames;
    if(effectFrames>0) --effectFrames;
    player.Update(key);
    parcel.Update(stage);
    hazard.Update(stage);
    if(stage>=2) hazard2.Update(stage);

    if(Collides(parcel,56.0f,40.0f)) {
        score+=10;
        effectFrames=35;
        Respawn(parcel,false);
    } else if(parcel.IsOffScreen()) Respawn(parcel,false);

    if(Collides(hazard,56.0f,48.0f)) {
        if(player.TakeDamage()) {
            effectFrames=-20; // short hit feedback, count back toward zero below
            Respawn(hazard,true);
        }
    } else if(hazard.IsOffScreen()) Respawn(hazard,true);

    if(stage>=2) {
        if(Collides(hazard2,56.0f,48.0f)) {
            if(player.TakeDamage()) {
                effectFrames=-20;
                Respawn(hazard2,true);
            }
        } else if(hazard2.IsOffScreen()) Respawn(hazard2,true);
    }
    if(effectFrames<0) ++effectFrames;
    if(player.hp<=0) {
        screen=GameScreen::GameOver;
        return;
    }
    if(score>=TargetScore()) {
        if(stage>=3) screen=GameScreen::Clear;
        else StartStage(stage+1);
    }
}

void Game::Draw() const {
    RECT full={0,0,800,600};
    if(screen==GameScreen::Title) {
        g2_Draw2D(titleTexture,&full);
        if(uiFont>=0) {
            g2_FontDrawText(uiFont,{215,510},0xFFFFFFFF,"ENTER - START");
            g2_FontDrawText(uiFont,{175,545},0xFFFFFFFF,"3 STAGES / COLLECT PARCELS / DODGE");
        }
        return;
    }
    if(screen==GameScreen::GameOver) {
        g2_Draw2D(gameOverTexture,&full);
        if(uiFont>=0) g2_FontDrawText(uiFont,{220,530},0xFFFFFFFF,"ENTER - RETRY / ESC - MENU");
        return;
    }
    if(screen==GameScreen::Clear) {
        g2_Draw2D(clearTexture,&full);
        if(uiFont>=0) {
            g2_FontDrawText(uiFont,{240,490},0xFFFFFFFF,"ALL 3 STAGES CLEARED!");
            g2_FontDrawText(uiFont,{220,530},0xFFFFFFFF,"ENTER - RETRY / ESC - MENU");
        }
        return;
    }
    g2_Draw2D(backgroundTextures[stage-1],&full);
    parcel.Draw(parcelTexture);
    hazard.Draw(hazardTexture);
    if(stage>=2) hazard2.Draw(hazardTexture);
    player.Draw(courierTexture);
    if(uiFont>=0) {
        g2_FontDrawText(uiFont,{20,16},0xFFFFFFFF,"STAGE: %d / 3",stage);
        g2_FontDrawText(uiFont,{185,16},0xFFFFFFFF,"SCORE: %d / %d",score,TargetScore());
        g2_FontDrawText(uiFont,{440,16},0xFFFFFFFF,"HP: %d",player.hp);
        g2_FontDrawText(uiFont,{535,16},0xFFFFFFFF,"TIME: %d",elapsedFrames/60);
        g2_FontDrawText(uiFont,{20,560},0xFFFFFFFF,"WASD / ARROWS: MOVE     ESC: MENU");
        if(stageIntroFrames>0) g2_FontDrawText(uiFont,{280,260},0xFFFFFF77,"STAGE %d - GO!",stage);
        if(effectFrames>0) g2_FontDrawText(uiFont,{340,90},0xFF70FFAD,"+10");
        if(effectFrames<0) g2_FontDrawText(uiFont,{335,90},0xFFFF7272,"HIT!");
        if(stage==3) g2_FontDrawText(uiFont,{24,54},0xFFFFD984,"WATCH THE SWEEPING HAZARDS!");
    }
}

void Game::Unload() {
    g2_TextureRelease(courierTexture);
    g2_TextureRelease(parcelTexture);
    g2_TextureRelease(hazardTexture);
    g2_TextureRelease(titleTexture);
    for(int i=0;i<3;++i) g2_TextureRelease(backgroundTextures[i]);
    g2_TextureRelease(gameOverTexture);
    g2_TextureRelease(clearTexture);
}
