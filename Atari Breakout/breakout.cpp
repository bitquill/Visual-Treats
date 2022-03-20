#include "include/raylib.h"
#include "include/Game.h"

const int GAME_WIDTH = 1000;
const int GAME_HEIGHT = 600;

int main() {
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "Atari Breakout!");
    SetTargetFPS(60);
    Vector2 paddlePos = {static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() - 50)};
    Vector2 ballPos = {static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() - 100)};

    Game g(20, paddlePos, ballPos);

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        g.tick();

        EndDrawing();
    }
}