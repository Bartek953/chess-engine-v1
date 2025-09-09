#include "GenSliderMoves.h"

namespace chessAI {
    void GenSliderMoves(Chessboard &Board, Point P, std::vector<Point> directions, int color, std::vector<Move> &results)
    {
        Point endpoint;
        for(Point dir : directions){
            endpoint = P + dir;
            while(normalized(endpoint)){
                if(Board.GetPieceColor(endpoint) == color)
                    break;

                int value = abs(Board.GetPieceType(endpoint));
                results.emplace_back(P, endpoint, value);
                if(value != 0)
                    break;

                endpoint = endpoint + dir;
            }
        }
    }
    void GenSliderBlocks(Chessboard &Board, Point P, std::vector<Point> directions, int color, std::vector<Move> &results)
    {
        Point endpoint;
        for(Point dir : directions){
            endpoint = P + dir;
            while(normalized(endpoint)){
                int value = abs(Board.GetPieceType(endpoint));
                results.emplace_back(P, endpoint, value);
                if(value != 0)
                    break;
                if(Board.GetPieceColor(endpoint) == color)
                    break;

                endpoint = endpoint + dir;
            }
        }
    }
}