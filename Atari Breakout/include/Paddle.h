#ifndef PADDLE_H
#define PADDLE_H

#include "raylib.h"

class Paddle {
    public:
        Paddle(const Color& paddleColor, float startX = 0, float startY = 0);
        const Rectangle& getPaddleRect() const;
        void draw() const;
        void move(bool didGameEnd);
        void winTransform();
    private:
        Rectangle paddleRect;
        float baseSpeed = 3;
        bool didGameEnd = false;
        Color paddleColor;

        const float ACCELERATION = 0.5f;
        const float PADDLE_WIDTH = 80;
        const float PADDLE_HEIGHT = 40;
};

#endif