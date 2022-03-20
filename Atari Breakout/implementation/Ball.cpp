#include "../include/Ball.h"

Ball::Ball(const Vector2& ballPos, const Color& palette) {
    if(ballPos.x > 0 && ballPos.y > 0) {
        pos.x = ballPos.x;
        pos.y = ballPos.y;
    } else {
        pos.x = GetScreenWidth() / 2;
        pos.y = GetScreenHeight() - 200;
    }
    this->palette.a = palette.a;
    this->palette.r = palette.r;
    this->palette.g = palette.g;
    this->palette.b = palette.b;
}

const Vector2& Ball::getPos() const {return pos;}
const int Ball::getRadius() const {return RADIUS;}
const bool Ball::isGameOver() const {return didGameEnd;}

void Ball::move(const Paddle& paddle) {
    if(didGameStart) {
        pos.y += velY;
    } else {
        pos.x += velX;
        pos.y += velY;
    }

    if(pos.x - RADIUS <= 0 || pos.x + RADIUS >= GetScreenWidth()) {
        velX = -velX;
    }

    if(CheckCollisionCircleRec(pos, RADIUS, paddle.getPaddleRect())) {
        float paddleWidth = paddle.getPaddleRect().width;
        if(pos.x >= paddleWidth / 2) {
            updatePositionRight();
        } else {
            updatePositionLeft();
        }
        pos.y -= 3;
    }

    if(pos.y >= GetScreenHeight()) didGameEnd = true;
    didGameStart = false;
}

void Ball::updateOnCollision(const Rectangle& rect) {
    if(pos.x >= (rect.width / 2)) {
        updatePositionRight();
    } else {
        updatePositionLeft();
    }
}

void Ball::updateOnCollisionTop(const Rectangle& rect) {
    updateOnCollision(rect);
    pos.y += 10;
}

void Ball::draw() const {
    DrawCircleV(pos, RADIUS, palette);
    DrawCircleLines(pos.x, pos.y, RADIUS, DARKGRAY);
}

void Ball::winTransform() {
    palette = {224, 255, 255, 255};
}

void Ball::updatePositionRight() {
    velY += ACCELERATION;
    velY = -velY;
    pos.x += 3;
}

void Ball::updatePositionLeft() {
    velX += ACCELERATION;
    velY += ACCELERATION;
    velX = -velX;
    velY = -velY;
    pos.x -= 3;
}