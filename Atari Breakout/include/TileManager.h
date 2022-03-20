#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include "raylib.h"
#include "Ball.h"
#include <vector>

struct BreakoutTile {
    Rectangle rect;
    bool hasCollided = false;
    Color palette = ORANGE;
};

class TileManager {
    public:
        const int NUM_TILE_ROWS = 1;
        const float TILE_WIDTH_A = 80;
        const float TILE_WIDTH_B = 50;
        const float TILE_HEIGHT = 40;

        TileManager(int topRectHeight);
        void draw() const;
        void checkCollision(Ball& ball);
        bool checkTilesCleared() const;
    private:
        std::vector<std::vector<BreakoutTile> > tiles;
        int fillerRectHeight = 20;
        Rectangle startRect;

        void initializeGrid(int startingRectPos);
};

#endif