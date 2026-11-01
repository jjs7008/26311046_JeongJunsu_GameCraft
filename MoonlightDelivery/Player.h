#pragma once
#include "glc2d.h"
#include <algorithm>
class Player {
public:
    float x = 372.0f, y = 490.0f;
    float speed = 2.4f; // units per fixed 1/60-second simulation step
    int hp = 3;
    int invincibleFrames = 0;
    void Reset() { x=372; y=490; hp=3; invincibleFrames=0; }
    void Update(const KEYCODE* keys) {
        if (keys['A'] || keys[VK_LEFT]) x -= speed;
        if (keys['D'] || keys[VK_RIGHT]) x += speed;
        if (keys['W'] || keys[VK_UP]) y -= speed;
        if (keys['S'] || keys[VK_DOWN]) y += speed;
        x = (std::max)(25.0f,(std::min)(719.0f,x));
        y = (std::max)(95.0f,(std::min)(530.0f,y));
        if(invincibleFrames>0) --invincibleFrames;
    }
    bool TakeDamage() {
        if(invincibleFrames>0) return false;
        --hp; invincibleFrames=65; return true;
    }
    void Draw(int texture) const {
        if(invincibleFrames>0 && (invincibleFrames/5)%2==0) return;
        VEC2 position(x,y); g2_Draw2D(texture,NULL,&position);
    }
};
