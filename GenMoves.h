#pragma once
#include "DataTypes.h"
#include <vector>

namespace chessAI {
    //color: 
    //1 - white
    //0 - empty
    //-1 black
    std::vector<Move> GenMoves(Chessboard& Board, int color);
}