#include "GenBishopMoves.h"
#include "GenSliderMoves.h"

namespace chessAI {
    void GenBishopMoves(Chessboard &Board, Point P, int color, std::vector<Move> &results)
    {
        std::vector<Point> directions = {Point(-1, -1), Point(-1, 1), Point(1, -1), Point(1, 1)};

        GenSliderMoves(Board, P, directions, color, results);
    }
    void GenBishopBlocks(Chessboard &Board, Point P, int color, std::vector<Move> &results)
    {
        std::vector<Point> directions = {Point(-1, -1), Point(-1, 1), Point(1, -1), Point(1, 1)};

        GenSliderBlocks(Board, P, directions, color, results);
    }
}