#include "Evaluate.h"
#include <vector>
#include "PSQT.h"

#include "GenMoves/GenKnightMoves.h"
#include "GenMoves/GenBishopMoves.h"
#include "GenMoves/GenRookMoves.h"
#include "GenMoves/GenQueenMoves.h"

namespace chessAI {
    std::vector<int> piece_values = {0, 100, 300, 310, 500, 900, KING_VALUE};

    const int CASTLE_BONUS = 50;
    const int CASTLE_POSSIBILITY_BONUS = 10;
    const int DOUBLE_BISHOPS_BONUS = 30;

    const int LIGHT_PIECE_ACTIVITY_BONUS = 6;
    const int HEAVY_PIECE_ACTIVITY_BONUS = 1;

    int DOUBLED_PAWNS_PENALTY = 30;
    int PROMOTION_RATIO = 10;
    int PAWN_PSQT_BONUS = 15;
    int LIGHT_PIECE_PSQT_BONUS = 10;

    int bishops_number = 0;
    std::vector<Move> moves;

    int EvaluateColor(Chessboard& Board, int color){
        int score = 0;
        int piece_type, piece_color;

        int pawnsInColumn[8] = {0, 0, 0, 0, 0, 0, 0, 0};

        for(int y = 0; y <= 7; y++){
            for(int x = 0; x <= 7; x++){
                piece_type = abs(Board.GetPieceType({x, y}));
                piece_color = Board.GetPieceColor({x, y});

                if(piece_color != color)continue;

                //counting material
                score += piece_values[piece_type];

                moves.clear();
                //PSQT and activity of light pieces
                if(piece_type == 1){ //pawn
                    //should be interpolation between game phases
                    score += CentralPSQT({x, y}, PAWN_PSQT_BONUS);
                    score += PromotionPSQT({x, y}, color, PROMOTION_RATIO);

                    pawnsInColumn[x]++;
                    if(pawnsInColumn[x] > 1){
                        score -= DOUBLED_PAWNS_PENALTY;
                    }
                }
                if(piece_type == 2){ //knight
                    score += CentralPSQT({x, y}, LIGHT_PIECE_PSQT_BONUS);
                    GenKnightMoves(Board, {x, y}, color, moves);
                    score += moves.size() * LIGHT_PIECE_ACTIVITY_BONUS;
                }
                if(piece_type == 3){ //bishop
                    score += CentralPSQT({x, y}, LIGHT_PIECE_PSQT_BONUS);
                    GenBishopMoves(Board, {x, y}, color, moves)    ;
                    score += moves.size() * LIGHT_PIECE_ACTIVITY_BONUS;
                    bishops_number++;
                }

                if(piece_type == 4){ //rook
                    score += CentralPSQT({x, y}, -2);
                    GenRookMoves(Board, {x, y}, color, moves);
                    score += moves.size() * HEAVY_PIECE_ACTIVITY_BONUS;
                }
                if(piece_type == 5){ //queen
                    GenQueenMoves(Board, {x, y}, color, moves);
                    score += moves.size() * HEAVY_PIECE_ACTIVITY_BONUS;    
                }
            }
        }
        if(bishops_number >= 2){
            score += DOUBLE_BISHOPS_BONUS;
        }

        //castles
        if(Board.m_DidCastle[index(color)]){
            score += CASTLE_BONUS;
            //std::cout << "CASTLE BONUS for " << color << '\n';
        }
        else if(Board.m_LeftCastle[index(color)] || Board.m_RightCastle[index(color)]){
            score += CASTLE_POSSIBILITY_BONUS;
        }

        return score;
    }

    int Evaluate(Chessboard &Board)
    {
        
        return EvaluateColor(Board, 1) - EvaluateColor(Board, -1);
    }
}