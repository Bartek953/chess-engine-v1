#include "CheckMove.h"

#include <vector>
#include "GenMoves/GenPawnMoves.h"
#include "GenMoves/GenKnightMoves.h"
#include "GenMoves/GenBishopMoves.h"
#include "GenMoves/GenRookMoves.h"
#include "GenMoves/GenQueenMoves.h"
#include "GenMoves/GenKingMoves.h"

namespace chessAI {
    bool CheckMove(Chessboard Board, int color, Move move)
    {
        if(!normalized(move.m_Start) || !normalized(move.m_End))
            return false;
        if(color != Board.GetPieceColor(move.m_Start))
            return false;
        if(color == Board.GetPieceColor(move.m_End))
            return false;

        std::vector<Move> moves_vec;
        switch(abs(Board.GetPieceType(move.m_Start))){
            case 1:
                GenPawnMoves(Board, move.m_Start, color, moves_vec);
                break;
            case 2:
                GenKnightMoves(Board, move.m_Start, color, moves_vec);
                break;
            case 3:
                GenBishopMoves(Board, move.m_Start, color, moves_vec);
                break;
            case 4:
                GenRookMoves(Board, move.m_Start, color, moves_vec);
                break;
            case 5:
                GenQueenMoves(Board, move.m_Start, color, moves_vec);
                break;
            case 6:
                GenKingMoves(Board, move.m_Start, color, moves_vec, true);
                break;
        }
        //opt?
        //generating moves is already in O(n)
        //so search in O(n) shouldn't hurt
        //also for better search it would need to be sorted, and that'll take O(nlogn), which is slower
        //solution might be to write different functions only for checking moves
        //but since check is only needed for user input, and not computer's minmax
        //then it shouldn't change performance
        for(Move move_i : moves_vec){
            if(move == move_i)return true;
        }
        return false;
    }
}