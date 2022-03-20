#include "include/raylib.h"
#include <iostream>

struct CollisionRect {
    Rectangle rect;
    bool didCollide = false;
};

int main() {
    InitWindow(600, 600, "test");
    SetTargetFPS(60);

    Vector2 pos = {(float) GetScreenWidth() / 4, (float) GetScreenHeight() / 4};
    float xVel = 0.4f;
    float yVel = 0.4f;
    int radius = 50;

    CollisionRect rects[5];

    for(size_t i = 0; i < 5; i++) {
        rects[i].rect = {static_cast<float>(GetRandomValue(20, GetScreenWidth() - 20)), 
        static_cast<float>(20, GetRandomValue(20, GetScreenHeight() - 20)), 50, 70};
    }


    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(PURPLE);

        pos.x += xVel;
        pos.y += yVel;

        if(pos.x + radius >= GetScreenWidth() || pos.x - radius <= 0) xVel = -xVel;
        if(pos.y + radius >= GetScreenHeight() || pos.y - radius <= 0) yVel = -yVel;

        if((int) GetTime() % 10 == 0) {
            xVel += 0.1f;
            yVel += 0.12f;
        }

        DrawCircleV(pos, radius, ORANGE);

        for(size_t i = 0; i < 5; i++) {
            if(!rects[i].didCollide) {
                DrawRectangleRec(rects[i].rect, RED);

                if(CheckCollisionCircleRec(pos, radius, rects[i].rect)) {
                    xVel = -xVel;
                    yVel = -yVel;
                    rects[i].didCollide = true;
                }
            }
        }
        EndDrawing();
    }

}