// Moonlight Delivery - Week 2: class structure and screen states.
// Based on the glc2d keyboard and texture examples.
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
#include "Game.h"

Game game;
int FrameMove() { game.Update(); return 0; }
int Render() { game.Draw(); return 0; }
int main() {
    g2_InitSdk();
    g2_SetClearColor(0xFF101A30);
    g2_SetFrameMove(FrameMove);
    g2_SetRender(Render);
    g2_CreateWin(100, 100, 800, 600, "Moonlight Delivery - Week 2");
    game.Load();
    g2_Run();
    game.Unload();
    g2_DestroyWin();
    return 0;
}
