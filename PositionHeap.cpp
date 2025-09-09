#include "PositionHeap.h"
#include <deque>

namespace chessAI {
    std::deque<Chessboard> PositionHeap;
    void AddPosition(Chessboard &position)
    {  
        PositionHeap.push_back(position);
    }
    Chessboard UndoPosition()
    {
        Chessboard result = PositionHeap.back();
        PositionHeap.pop_back();

        return result;
    }
}