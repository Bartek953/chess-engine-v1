#pragma once
#include <vector>
#include "../DataTypes.h"

namespace chessAI {
    //1 - white
    //0 - empty
    //-1 - black
    void GenBishopMoves(Chessboard& Board, Point P, int color, std::vector<Move>& results);
    void GenBishopBlocks(Chessboard& Board, Point P, int color, std::vector<Move>& results);
}