#pragma once
#include "glc2d.h"
#include <cmath>

class FallingObject {
public:
    float x=100.0f, y=-60.0f, speed=1.30f;
    float phase=0.0f;
    int lane=0;
    bool hazard=false;
    bool active=true;
    void Reset(int whichLane, float startY, float fallSpeed, bool isHazard) {
        lane=whichLane%3;
        x=120.0f+220.0f*lane;
        y=startY;
        speed=fallSpeed;
        hazard=isHazard;
        phase=0.0f;
        active=true;
    }
    // Simulation updates run at a fixed 60 Hz.
    // Stage 3 adds a mild left/right sweeping hazard pattern.
    void Update(int stage) {
        if(!active) return;
        y+=speed;
        phase+=0.047f;
        if(hazard && stage>=3) {
            const float center=120.0f+220.0f*lane;
            x=center+48.0f*std::sin(phase);
        }
    }
    bool IsOffScreen() const {return y>620.0f;}
    void Draw(int texture) const {
        if(!active) return;
        VEC2 pos(x,y); g2_Draw2D(texture,NULL,&pos);
    }
};
