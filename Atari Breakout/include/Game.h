#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "Ball.h"
#include "Paddle.h"
#include "TileManager.h"

class Game {
    public:
        Game(int tileRowStart, const Vector2& paddlePos, const Vector2& ballPos);
        void tick();
        void draw(bool didGameEnd);
        void move(bool didGameEnd);
        void checkWinLoseCondition(bool isGameOver, bool isGameCleared);
    private:
        Paddle paddle;
        Ball ball;
        TileManager tileManager;
};

#endif