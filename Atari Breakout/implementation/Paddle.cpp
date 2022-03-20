#include "../include/Paddle.h"
#include <iostream>

Paddle::Paddle(const Color& paddleColor, float startX, float startY) {
            if(startX < 0) startX = 0;
            if(startY < 0) startY = 0;
            paddleRect = {startX, startY, PADDLE_WIDTH, PADDLE_HEIGHT};
            this->paddleColor.a = paddleColor.a;
            this->paddleColor.r = paddleColor.r;
            this->paddleColor.g = paddleColor.g;
            this->paddleColor.b = paddleColor.b;
        }

const Rectangle& Paddle::getPaddleRect() const {return paddleRect;}

void Paddle::draw() const {
    std::cout << paddleRect.x << " " << paddleRect.y << std::endl;
    DrawRectangleRec(paddleRect, paddleColor);
    DrawRectangleLinesEx(paddleRect, 1, BLACK);
    std::cout << "drawing paddle" << std::endl;
}

void Paddle::move(bool didGameEnd) {
    if(!didGameEnd) {
        if(IsKeyDown(KEY_LEFT)) {
            paddleRect.x -= baseSpeed;
            baseSpeed += ACCELERATION;
        }

        if(IsKeyDown(KEY_RIGHT)) {
            paddleRect.x += baseSpeed;
            baseSpeed -= ACCELERATION;
        }
        

        if(IsKeyUp(KEY_LEFT)) baseSpeed = 3;
        if(IsKeyDown(KEY_RIGHT)) baseSpeed = 3;

        if(paddleRect.x < 0) paddleRect.x = 0;
        if(paddleRect.x + paddleRect.width >= GetScreenWidth()) paddleRect.x = GetScreenWidth() - paddleRect.width;
    }
}

void Paddle::winTransform() {
    paddleColor = GREEN;
}