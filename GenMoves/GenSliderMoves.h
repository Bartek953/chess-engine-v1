#pragma once
#include <vector>
#include "../DataTypes.h"

namespace chessAI {
    //1 - white
    //0 - empty
    //-1 - black
    void GenSliderMoves(Chessboard& Board, Point P, std::vector<Point> directions, int color, std::vector<Move>& results);
    void GenSliderBlocks(Chessboard& Board, Point P, std::vector<Point> directions, int color, std::vector<Move>& results);
}