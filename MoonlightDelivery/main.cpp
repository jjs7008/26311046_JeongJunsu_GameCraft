// Moonlight Delivery - Week 1 prototype
// Sample base: glc2d Ex04_Keyboard and Ex05_Animation.
// Week 1 scope: window, basic movement, falling objects, and drawing.
#if defined(_DEBUG)
 #if defined(_M_X64)
  #pragma comment(lib, "glc2d_x64_debug.lib")
 #elif defined(_M_IX86)
  #pragma comment(lib, "glc2d_win32_debug.lib")
 #endif
#else
 #if defined(_M_X64)
  #pragma comment(lib, "glc2d_x64_release.lib")
 #elif defined(_M_IX86)
  #pragma comment(lib, "glc2d_win32_release.lib")
 #endif
#endif

#include "glc2d.h"
#include <stdio.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const float PLAYER_SPEED = 4.0f;
int playerTexture = -1;
int parcelTexture = -1;
int hazardTexture = -1;
float playerX = 400.0f;
float playerY = 475.0f;
float parcelY = 50.0f;
float hazardY = -260.0f;
float parcelX = 200.0f;
float hazardX = 550.0f;
int objectCycle = 0;

int FrameMove()
{
    // Keyboard polling is based on the included glc2d SDK sample.
    const KEYCODE* key = g2_GetKeyboard();
    if (key['A'] || key[VK_LEFT]) playerX -= PLAYER_SPEED;
    if (key['D'] || key[VK_RIGHT]) playerX += PLAYER_SPEED;
    if (key['W'] || key[VK_UP]) playerY -= PLAYER_SPEED;
    if (key['S'] || key[VK_DOWN]) playerY += PLAYER_SPEED;
    if (playerX < 20.0f) playerX = 20.0f;
    if (playerX > 730.0f) playerX = 730.0f;
    if (playerY < 100.0f) playerY = 100.0f;
    if (playerY > 530.0f) playerY = 530.0f;

    // Movement preview only. Collection and collision are for Week 3.
    parcelY += 2.5f;
    hazardY += 3.0f;
    if (parcelY > HEIGHT) {
        parcelY = -40.0f;
        parcelX = 130.0f + float((objectCycle % 3) * 220);
        ++objectCycle;
    }
    if (hazardY > HEIGHT) {
        hazardY = -180.0f;
        hazardX = 130.0f + float((objectCycle % 3) * 220);
    }
    return 0;
}

int Render()
{
    // Positions and motion are already visible in Week 1.
    VEC2 p(playerX, playerY);
    VEC2 parcel(parcelX, parcelY);
    VEC2 hazard(hazardX, hazardY);
    g2_Draw2D(playerTexture, NULL, &p);
    g2_Draw2D(parcelTexture, NULL, &parcel);
    g2_Draw2D(hazardTexture, NULL, &hazard);
    return 0;
}

int main()
{
    g2_InitSdk();
    g2_SetClearColor(0xFF16213B);
    g2_SetFrameMove(FrameMove);
    g2_SetRender(Render);
    g2_CreateWin(100, 100, WIDTH, HEIGHT, "Moonlight Delivery - Week 1");

    playerTexture = g2_TextureLoad("Texture/courier.png");
    parcelTexture = g2_TextureLoad("Texture/parcel.png");
    hazardTexture = g2_TextureLoad("Texture/hazard.png");
    printf("Moonlight Delivery - week 1 prototype. Move: WASD or arrow keys.\n");
    printf("Week 1 preview only; collision/score/stages will come later.\n");
    g2_Run();
    g2_TextureRelease(playerTexture);
    g2_TextureRelease(parcelTexture);
    g2_TextureRelease(hazardTexture);
    g2_DestroyWin();
    return 0;
}
