#pragma once
#include "glc2d.h"

class FallingObject {
public:
    float x = 200.0f;
    float y = -60.0f;
    float speed = 2.5f;
    int lane = 0;

    void Reset(float startX, float startY, float fallSpeed) {
        x = startX; y = startY; speed = fallSpeed; lane = 0;
    }
    void Update() {
        y += speed;
        if (y > 600.0f) {
            y = -60.0f;
            lane = (lane + 1) % 3;
            x = 130.0f + 220.0f * lane;
        }
    }
    void Draw(int texture) const { VEC2 position(x, y); g2_Draw2D(texture, NULL, &position); }
};
