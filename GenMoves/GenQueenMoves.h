#pragma once
#include <vector>
#include "../DataTypes.h"

namespace chessAI {
    //1 - white
    //0 - empty
    //-1 - black
    void GenQueenMoves(Chessboard& Board, Point P, int color, std::vector<Move>& results);
    void GenQueenBlocks(Chessboard& Board, Point P, int color, std::vector<Move>& results);
}