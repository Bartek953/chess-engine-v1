#include "GenMoves.h"

#include "GenMoves/GenPawnMoves.h"
#include "GenMoves/GenKnightMoves.h"
#include "GenMoves/GenBishopMoves.h"
#include "GenMoves/GenRookMoves.h"
#include "GenMoves/GenQueenMoves.h"
#include "GenMoves/GenKingMoves.h"

namespace chessAI {
    bool cmp(Move A, Move B){
        return A.m_Value > B.m_Value;
    }

    std::vector<Move> GenMoves(Chessboard &Board, int color)
    {
        std::vector<Move> results;

        for(int y = 0; y <= 7; y++){
            for(int x = 0; x <= 7; x++){
                uint64_t ptr = PointToBitboard({x, y});

                if(is_piece(ptr, Board.m_Pawns[index(color)])){
                    GenPawnMoves(Board, {x, y}, color, results);
                    continue;
                }
                if(is_piece(ptr, Board.m_Knights[index(color)])){
                    GenKnightMoves(Board, {x, y}, color, results);
                    continue;
                }
                if(is_piece(ptr, Board.m_Bishops[index(color)])){
                    GenBishopMoves(Board, {x, y}, color, results);
                    continue;
                }
                if(is_piece(ptr, Board.m_Rooks[index(color)])){
                    GenRookMoves(Board, {x, y}, color, results);
                    continue;
                }
                if(is_piece(ptr, Board.m_Queen[index(color)])){
                    GenQueenMoves(Board, {x, y}, color, results);
                    continue;
                }
                if(is_piece(ptr, Board.m_King[index(color)])){
                    GenKingMoves(Board, {x, y}, color, results, true);
                    continue;
                }

            }
        }
        //sort results based on values
        sort(results.begin(), results.end(), cmp);
        return results;
    }
}

