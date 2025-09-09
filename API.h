#pragma once

#include "DataTypes.h"
#include <array>

namespace chessAI {
    void Init();
    void WhiteMove();
    bool WhiteMove(Move move);
    void BlackMove();
    Chessboard GetBoard();
    std::array<std::array<int, 8>, 8> GetBoardAsArray();
    int GetEvaluation();
}