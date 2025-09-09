#pragma once
#include "DataTypes.h"

namespace chessAI {
    void HashInit();
    Hash HashPosition(Chessboard& Board);
    Hash HashMove(Hash current_positions_hash, Chessboard& Board, Move& move);

    //should I also hash depth connected to the position?
}