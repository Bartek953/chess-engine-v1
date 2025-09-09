#pragma once
#include "DataTypes.h"

namespace chessAI {
    //static const int checkmate_barrier = 100000000;
    void CheckIfCheckmated(Chessboard& Board, int color);
}