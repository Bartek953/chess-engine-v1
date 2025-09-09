#include "GenKnightMoves.h"
#include <iostream>

namespace chessAI {
    //1 - white
    //0 - empty
    //-1 - black
    void GenKnightMoves(Chessboard &Board, Point P, int color, std::vector<Move> &results)
    {
        for(int dx : {-1, 1}){
            for(int dy : {-2, 2}){
                for(Point delta : {Point(dx, dy), Point(dy, dx)}){
                    Point endpoint = P + delta;

                    if(!normalized(endpoint)) continue;
                    if(Board.GetPieceColor(endpoint) == color) continue;

                    int value = abs(Board.GetPieceType(endpoint));
                    results.emplace_back(P, endpoint, value);
                }
            }
        }
    }
}