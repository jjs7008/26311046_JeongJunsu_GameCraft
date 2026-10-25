#pragma once
#include "glc2d.h"

class Player {
public:
    float x = 375.0f;
    float y = 475.0f;
    float speed = 4.0f;

    void Reset() { x = 375.0f; y = 475.0f; }
    void Update(const KEYCODE* keys) {
        if (keys['A'] || keys[VK_LEFT]) x -= speed;
        if (keys['D'] || keys[VK_RIGHT]) x += speed;
        if (keys['W'] || keys[VK_UP]) y -= speed;
        if (keys['S'] || keys[VK_DOWN]) y += speed;
        if (x < 20.0f) x = 20.0f;
        if (x > 730.0f) x = 730.0f;
        if (y < 100.0f) y = 100.0f;
        if (y > 530.0f) y = 530.0f;
    }
    void Draw(int texture) const { VEC2 position(x, y); g2_Draw2D(texture, NULL, &position); }
};
