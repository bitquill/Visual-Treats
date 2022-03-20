#include "../include/Game.h"

Game::Game(int tileRowStart, const Vector2& paddlePos, const Vector2& ballPos): 
    tileManager(tileRowStart), paddle(PURPLE, paddlePos.x, paddlePos.y), ball(ballPos) {}

void Game::tick() {
    bool gameEnd = ball.isGameOver();

    draw(gameEnd);
    move(gameEnd);
}

void Game::draw(bool didGameEnd) {

    paddle.draw();
    ball.draw();
    tileManager.draw();

    bool gameCleared = tileManager.checkTilesCleared();
    //bool gameCleared = true;

    checkWinLoseCondition(didGameEnd, gameCleared);
}

void Game::move(bool didGameEnd) {
    paddle.move(didGameEnd);
    ball.move(paddle);
    tileManager.checkCollision(ball);
}

void Game::checkWinLoseCondition(bool isGameOver, bool isGameCleared) {
    if(isGameCleared) {
        char winMessage[24] = "Congrats! Game Cleared!";
        int measuredWin = MeasureText(winMessage, 40);
        DrawText(winMessage, (GetScreenWidth() / 2) - (measuredWin / 2), 
        GetScreenHeight() / 2, 40, GREEN);
        ball.winTransform();
        paddle.winTransform();
    } 
    
    if(isGameOver && !isGameCleared) {
        char loseMessage[11] = "Game Over!";
        int measuredLose = MeasureText(loseMessage, 30);
        DrawText(loseMessage, (GetScreenWidth() / 2) - (measuredLose / 2), GetScreenHeight() / 2, 24, RED);
    }
}