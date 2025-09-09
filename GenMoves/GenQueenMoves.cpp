#include "GenQueenMoves.h"
#include "GenSliderMoves.h"

namespace chessAI {
    void GenQueenMoves(Chessboard &Board, Point P, int color, std::vector<Move> &results)
    {
        std::vector<Point> directions;
        directions.reserve(8);

        for(int dx : {-1, 0, 1}){
            for(int dy : {-1, 0, 1}){
                if(dx == 0 && dy == 0)
                    continue;
                directions.emplace_back(dx, dy);
            }
        }
        GenSliderMoves(Board, P, directions, color, results);
    }
    void GenQueenBlocks(Chessboard &Board, Point P, int color, std::vector<Move> &results)
    {
        std::vector<Point> directions;
        directions.reserve(8);

        for(int dx : {-1, 0, 1}){
            for(int dy : {-1, 0, 1}){
                if(dx == 0 && dy == 0)
                    continue;
                directions.emplace_back(dx, dy);
            }
        }
        GenSliderBlocks(Board, P, directions, color, results);
    }
}