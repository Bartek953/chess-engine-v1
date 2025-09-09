#include "GenRookMoves.h"
#include "GenSliderMoves.h"

namespace chessAI {
    void GenRookMoves(Chessboard &Board, Point P, int color, std::vector<Move> &results)
    {
        std::vector<Point> directions = {Point(-1, 0), Point(1, 0), Point(0, -1), Point(0, 1)};
        
        GenSliderMoves(Board, P, directions, color, results);
    }
    void GenRookBlocks(Chessboard &Board, Point P, int color, std::vector<Move> &results)
    {
        std::vector<Point> directions = {Point(-1, 0), Point(1, 0), Point(0, -1), Point(0, 1)};
        
        GenSliderBlocks(Board, P, directions, color, results);
    }
}