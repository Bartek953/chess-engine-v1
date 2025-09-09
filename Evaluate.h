#pragma once

#include "DataTypes.h"

namespace chessAI {
    //int to avoid floating points' errors
    //const int KING_VALUE = 1000000009; //bilion and nine
    int Evaluate(Chessboard& Board);
}