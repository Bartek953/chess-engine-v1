#pragma once

#include "DataTypes.h"
#include "Evaluate.h"

namespace chessAI {
    Move MinMax(Chessboard& Board, int color, int depth, int add_depth = 0, bool checkDraw = false, int alpha = -2*KING_VALUE, int beta = 2*KING_VALUE);
    void StartMinMax();
    void StopMinMax();
}