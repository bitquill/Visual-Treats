#include "../include/TileManager.h"
#include <iostream>

TileManager::TileManager(int topRectHeight): fillerRectHeight(topRectHeight) {
    startRect = {0, 0, (float) GetScreenWidth(), (float) topRectHeight};
    initializeGrid(topRectHeight);
}

void TileManager::draw() const {
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
}

void TileManager::checkCollision(Ball& ball) {
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

bool TileManager::checkTilesCleared() const {
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

void TileManager::initializeGrid(int startingRectPos) {
    bool useTileA = true;
    int gridX = startingRectPos + 20;
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