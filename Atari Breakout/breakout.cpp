#include "include/raylib.h"
#include <vector>
#include <iostream>

struct BreakoutTile {
    Rectangle rect;
    bool hasCollided = false;
    Color palette = ORANGE;
};

class Paddle {
    public:
        Paddle(const Color& paddleColor, float startX = 0, float startY = 0) {
            if(startX < 0) startX = 0;
            if(startY < 0) startY = 0;
            paddleRect = {startX, startY, PADDLE_WIDTH, PADDLE_HEIGHT};
            this->paddleColor.a = paddleColor.a;
            this->paddleColor.r = paddleColor.r;
            this->paddleColor.g = paddleColor.g;
            this->paddleColor.b = paddleColor.b;
        }

        const Rectangle& getPaddleRect() const {return paddleRect;}

        void draw() const {
            std::cout << paddleRect.x << " " << paddleRect.y << std::endl;
            DrawRectangleRec(paddleRect, paddleColor);
            DrawRectangleLinesEx(paddleRect, 1, BLACK);
            std::cout << "drawing paddle" << std::endl;
        }

        void move(bool didGameEnd) {
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

        void winTransform() {
            paddleColor = GREEN;
        }

    private:
        Rectangle paddleRect;
        float baseSpeed = 3;
        bool didGameEnd = false;


        const float ACCELERATION = 0.5f;
        const float PADDLE_WIDTH = 80;
        const float PADDLE_HEIGHT = 40;
        Color paddleColor;

};

class Ball {
    public:

        Ball(const Vector2& ballPos, const Color& palette = ORANGE) {
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

        const Vector2& getPos() const {return pos;}
        const int getRadius() const {return RADIUS;}
        const bool isGameOver() const {return didGameEnd;}

        void move(const Paddle& paddle) {
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

        void updateOnCollision(const Rectangle& rect) {
            if(pos.x >= (rect.width / 2)) {
                updatePositionRight();
            } else {
                updatePositionLeft();
            }
        }

        void updateOnCollisionTop(const Rectangle& rect) {
            updateOnCollision(rect);
            pos.y += 10;
        }

        void draw() const {
            DrawCircleV(pos, RADIUS, palette);
            DrawCircleLines(pos.x, pos.y, RADIUS, DARKGRAY);
        }

        void winTransform() {
            palette = {224, 255, 255, 255};
        }
    private:
        const int RADIUS = 10;
        const float ACCELERATION = 0.5f;

        Vector2 pos;
        float velX = 2;
        float velY = 2;
        bool didGameEnd = false;
        bool didGameStart = true;
        Color palette;

        void updatePositionRight() {
            velY += ACCELERATION;
            velY = -velY;
            pos.x += 3;
        }

        void updatePositionLeft() {
            velX += ACCELERATION;
            velY += ACCELERATION;
            velX = -velX;
            velY = -velY;
            pos.x -= 3;
        }
};

class Game {
    public:
        const int NUM_TILE_ROWS = 1;
        const float TILE_WIDTH_A = 80;
        const float TILE_WIDTH_B = 50;
        const float TILE_HEIGHT = 40;

        Game(int tileRowStart, const Vector2& paddlePos, const Vector2& ballPos): gridStart(tileRowStart),
        paddle(PURPLE, paddlePos.x, paddlePos.y), ball(ballPos) {
            initialPaddlePos = paddlePos;
            startRect = {0, 0, (float) GetScreenWidth(), (float) gridStart};
            initializeGrid(tileRowStart);
        }

        void tick() {
            bool gameEnd = ball.isGameOver();

            draw(gameEnd);
            paddle.move(gameEnd);
            ball.move(paddle);
            move(ball);
        }

        void draw(bool didGameEnd) {
            DrawRectangleRec(startRect, LIGHTGRAY);
            std::cout << tiles.at(0).size() << std::endl;
            
            for(const std::vector<BreakoutTile>& tileRow : tiles) {
                for(const BreakoutTile& tile : tileRow) {
                    if(!tile.hasCollided) {
                        DrawRectangleRec(tile.rect, tile.palette);
                        DrawRectangleLinesEx(tile.rect, 0.3f, BLACK);
                    }
                }
            }

            paddle.draw();
            ball.draw();

            bool gameCleared = checkTilesCleared();
            //bool gameCleared = true;

            if(gameCleared) {
                char winMessage[24] = "Congrats! Game Cleared!";
                int measuredWin = MeasureText(winMessage, 40);
                DrawText(winMessage, (GetScreenWidth() / 2) - (measuredWin / 2), 
                GetScreenHeight() / 2, 40, GREEN);
                ball.winTransform();
                paddle.winTransform();
            } 
            
            if(didGameEnd && !gameCleared) {
                char loseMessage[11] = "Game Over!";
                int measuredLose = MeasureText(loseMessage, 30);
                DrawText(loseMessage, (GetScreenWidth() / 2) - (measuredLose / 2), GetScreenHeight() / 2, 24, RED);
            }

        }

        void move(Ball& ball) {

            if(CheckCollisionCircleRec(ball.getPos(), ball.getRadius(), startRect)) {
                ball.updateOnCollisionTop(startRect);
            }

            for(std::vector<BreakoutTile>& tileRow : tiles) {
                for(BreakoutTile& tile : tileRow) {
                    if(CheckCollisionCircleRec(ball.getPos(), ball.getRadius(), tile.rect) && !tile.hasCollided) {
                        ball.updateOnCollision(tile.rect);
                        tile.hasCollided = true;
                    }
                }
            }
        }

    private:
        std::vector<std::vector<BreakoutTile> > tiles;
        int gridStart = 20;
        Vector2 initialPaddlePos;
        Rectangle startRect;

        Paddle paddle;
        Ball ball;

        void initializeGrid(int blockStart) {
            bool useTileA = true;
            int gridX = blockStart + 20;
            for(size_t i = 0; i < NUM_TILE_ROWS; i++) {
                bool rowFilled = false;
                float currentWidth = 0;
                std::vector<BreakoutTile> tileRow;
                while(!rowFilled) {
                    float tileWidth = useTileA ? TILE_WIDTH_A : TILE_WIDTH_B;
                    Color palette = useTileA ? (Color) {248, 187, 208, 255} : (Color) {200, 230, 201, 255};
                    float rectHeight = i == 0 ? (i * NUM_TILE_ROWS * TILE_HEIGHT) + gridX : (i * NUM_TILE_ROWS * TILE_HEIGHT);
                    Rectangle r = {currentWidth, rectHeight, tileWidth, TILE_HEIGHT};
                    
                    BreakoutTile t;
                    t.rect = r;
                    t.hasCollided = false;
                    t.palette = palette;
                    tileRow.push_back(t);

                    currentWidth += tileWidth;
                    useTileA = !useTileA;

                    if(currentWidth >= GetScreenWidth()) {
                        rowFilled = true;
                    }
                }
                tiles.push_back(tileRow);
            }
        }

        bool checkTilesCleared() const {
            int numTileRowsCleared = 0;
            int numTiles = 0;
            for(const std::vector<BreakoutTile>& tileRow : tiles) {
                for(const BreakoutTile& tile : tileRow) {
                    if(tile.hasCollided) numTileRowsCleared += 1;
                    numTiles += 1;
                }
            }
            
            return numTileRowsCleared == numTiles;
        }
};

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