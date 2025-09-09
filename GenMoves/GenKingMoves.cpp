#include "GenKingMoves.h"

#include "GenPawnMoves.h"
#include "GenKnightMoves.h"
#include "GenBishopMoves.h"
#include "GenRookMoves.h"
#include "GenQueenMoves.h"

#include <iostream>

namespace chessAI {
    bool is_blocked(Point P, Chessboard Board, uint64_t blocked_places){
        if(Board.GetPieceType(P) != 0)return true;
        if((PointToBitboard(P) & blocked_places) > 0) return true;
        return false;
    }
    bool are_blocked(int x0, int x1, int y, Chessboard Board, uint64_t blocked_places){
        for(int x = x0; x <= x1; x++){
            if(is_blocked(Point(x, y), Board, blocked_places))
                return true;
        }
        return false;
    }

    void GenKingMoves(Chessboard &Board, Point P, int color, std::vector<Move> &results, bool BeAccurate)
    {
        uint64_t blocked_places;
        //blocked by freindly pieces
        blocked_places = Board.m_Pawns[index(color)] | Board.m_Knights[index(color)] | Board.m_Bishops[index(color)] | Board.m_Rooks[index(color)] | Board.m_Queen[index(color)];

        //opts?
        //1. not checking enemy moves in minmax (if can't castle)
        //2. only checking what changed in last enemys move
        //enemy moves
        if(BeAccurate){ //caution - functtion refers to itself
            std::vector<Move> enemy_moves;
            for(int x = 0; x <= 7; x++){
                for(int y = 0; y <= 7; y++){
                    uint64_t ptr = PointToBitboard({x, y});

                    if(is_piece(ptr, Board.m_Pawns[index(-color)])){
                        GenPawnBlocks(Board, {x, y}, -color, enemy_moves);
                        continue;
                    }
                    if(is_piece(ptr, Board.m_Knights[index(-color)])){
                        GenKnightMoves(Board, {x, y}, -color, enemy_moves);
                        continue;
                    }
                    if(is_piece(ptr, Board.m_Bishops[index(-color)])){
                        GenBishopBlocks(Board, {x, y}, -color, enemy_moves);
                        continue;
                    }
                    if(is_piece(ptr, Board.m_Rooks[index(-color)])){
                        GenRookBlocks(Board, {x, y}, -color, enemy_moves);
                        continue;
                    }
                    if(is_piece(ptr, Board.m_Queen[index(-color)])){
                        GenQueenBlocks(Board, {x, y}, -color, enemy_moves);
                        continue;
                    }
                    if(is_piece(ptr, Board.m_King[index(-color)])){
                        GenKingMoves(Board, {x, y}, -color, enemy_moves, false);
                        continue;
                    }
                }
            }
            for(Move move : enemy_moves){
                blocked_places |= PointToBitboard(move.m_End);
            }
        }

        //normal moves
        for(int dx : {-1, 0, 1}){
            for(int dy : {-1, 0, 1}){
                if(dx == 0 && dy == 0)
                    continue;
                Point endpoint = P + Point(dx, dy);
                if(!normalized(endpoint))
                    continue;
                if((PointToBitboard(endpoint) & blocked_places) > 0)
                    continue;
                int value = abs(Board.GetPieceType(endpoint));
                results.emplace_back(P, endpoint, value);
            }
        }

        blocked_places ^= Board.m_Rooks[index(color)];
        //Right Castle
        if(Board.m_RightCastle[index(color)] && !are_blocked(5, 6, P.m_Y, Board, blocked_places)
        && (PointToBitboard(P) & blocked_places) == 0 && (PointToBitboard({7, P.m_Y}) & blocked_places) == 0){
            results.emplace_back(P, Point(6, P.m_Y), 1);
        }
        //Left Castle
        if(Board.m_LeftCastle[index(color)] && !are_blocked(1, 3, P.m_Y, Board, blocked_places)
        && (PointToBitboard(P) & blocked_places) == 0 && (PointToBitboard({0, P.m_Y}) & blocked_places) == 0){
            results.emplace_back(P, Point(2, P.m_Y), 1);
        }
    }
}