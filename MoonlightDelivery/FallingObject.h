#pragma once
#include "glc2d.h"
class FallingObject {
public:
    float x=100.0f, y=-60.0f, speed=1.30f;
    int lane=0;
    bool hazard=false;
    void Reset(int whichLane, float startY, float fallSpeed, bool isHazard) {
        lane=whichLane%3; x=120.0f+220.0f*lane;
        y=startY; speed=fallSpeed; hazard=isHazard;
    }
    // The game decides when to respawn to ensure scoring happens only once.
    void Update() { y+=speed; }
    bool IsOffScreen() const {return y>620.0f;}
    void Draw(int texture) const { VEC2 pos(x,y); g2_Draw2D(texture,NULL,&pos); }
};
