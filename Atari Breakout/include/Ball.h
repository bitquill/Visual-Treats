#ifndef BALL_H
#define BALL_H

#include "raylib.h"
#include "Paddle.h"

class Ball {
    public:
        Ball(const Vector2&, const Color& palette = ORANGE);
        const Vector2& getPos() const;
        const int getRadius() const;
        const bool isGameOver() const;
        void move(const Paddle& paddle);
        void updateOnCollision(const Rectangle& rect);
        void updateOnCollisionTop(const Rectangle& rect);
        void draw() const;
        void winTransform();
    private:
        const int RADIUS = 10;
        const float ACCELERATION = 0.5f;

        Vector2 pos;
        float velX = 2;
        float velY = 2;
        bool didGameEnd = false;
        bool didGameStart = true;
        Color palette;

        void updatePositionLeft();
        void updatePositionRight();
};

#endif