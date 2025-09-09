#include "GenPawnMoves.h"

//1 - white
//0 - empty
//-1 - black

namespace chessAI {
    void GenPawnMoves(Chessboard& Board, Point P, int color, std::vector<Move>& results){
        int start_location, direction;
        if(color == 1){
            start_location = 1;
            direction = 1;
        }
        else {
            start_location = 6;
            direction = -1;
        }

        Point endpoint;
        int value;

        //bicia
        for(int dx : {-1, 1}){
            endpoint = P + Point(dx, direction);
            if(normalized(endpoint) && (Board.GetPieceColor(endpoint) == -color || Board.m_EnPassantTarget == PointToBitboard(endpoint))){
                value = std::max(abs(Board.GetPieceType(endpoint)), 1);
                results.emplace_back(P, endpoint, value);
            }
        }
        //1 do przodu
        endpoint = P + Point(0, direction);
        if(Board.GetPieceColor(endpoint) == 0 && normalized(endpoint)){
            results.emplace_back(P, endpoint, 0);
        }
        else return;
        //2 do przodu
        endpoint = P + Point(0, 2 * direction);
        if(P.m_Y == start_location && Board.GetPieceColor(endpoint)  == 0 && normalized(endpoint)){
            results.emplace_back(P, endpoint, 0);
        }
        return;
    }
    void GenPawnBlocks(Chessboard &Board, Point P, int color, std::vector<Move> &results)
    {
        int start_location, direction;
        if(color == 1){
            start_location = 1;
            direction = 1;
        }
        else {
            start_location = 6;
            direction = -1;
        }
        Point endpoint;
        int value;
        for(int dx : {-1, 1}){
            endpoint = P + Point(dx, direction);
            if(normalized(endpoint)){
                value = std::max(abs(Board.GetPieceType(endpoint)), 1);
                results.emplace_back(P, endpoint, value);
            }
        }
    }
}
