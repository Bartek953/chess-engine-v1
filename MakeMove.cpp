#include "MakeMove.h"

//Pawn promotion X
//EnPassant handling X
//EnPassant removing X
//Castles
//Castles possibility removing

namespace chessAI {
    void JustMovePiece(Chessboard& Board, Move move){
        bool remove = (move.m_End.m_X == -1);

        int color = Board.GetPieceColor(move.m_Start);
        int piece_type = abs(Board.GetPieceType(move.m_Start));
        uint64_t start_ptr = PointToBitboard(move.m_Start);

        if(piece_type == 0)return;

        uint64_t* piece_ptr[] = {nullptr, Board.m_Pawns, Board.m_Knights, Board.m_Bishops, Board.m_Rooks, Board.m_Queen, Board.m_King};

        piece_ptr[piece_type][index(color)] ^= start_ptr;

        if(!remove) {
            int enemy_piece_type = abs(Board.GetPieceType(move.m_End));
            uint64_t end_ptr = PointToBitboard(move.m_End);

            piece_ptr[piece_type][index(color)] ^= end_ptr;
            if(enemy_piece_type != 0){
                piece_ptr[enemy_piece_type][index(-color)] ^= end_ptr;

                //removing castle possibility if rook captured
                if(enemy_piece_type == 4){
                    int ENEMY_START_Y;
                    if(color == 1)ENEMY_START_Y = 7;
                    else ENEMY_START_Y = 0;

                    if(move.m_End.m_X == 0 && move.m_End.m_Y == ENEMY_START_Y)
                        Board.m_LeftCastle[index(-color)] = false;
                    if(move.m_End.m_X == 7 && move.m_End.m_Y == ENEMY_START_Y)
                        Board.m_RightCastle[index(-color)] = false;
                }
            }
        }

    }
    void MakeMove(Chessboard &Board, Move move)
    {
        //clearing EnPassant
        Board.m_EnPassantTarget = 0;

        int color = Board.GetPieceColor(move.m_Start);
        int piece_type = abs(Board.GetPieceType(move.m_Start));
        uint64_t start_ptr = PointToBitboard(move.m_Start);
        uint64_t end_ptr = PointToBitboard(move.m_End);

        if(piece_type == 1){ //pawn
            //promotion
            if(move.m_End.m_Y == 0 || move.m_End.m_Y == 7){
                JustMovePiece(Board, Move(move.m_End, {-1, -1}));
                Board.m_Pawns[index(color)] ^= start_ptr;
                Board.m_Queen[index(color)] ^= end_ptr;
                return;
            }
            //start position's jump
            if(abs(move.m_Start.m_Y - move.m_End.m_Y) == 2){
                //setting enPassantTarget - move will be executed later
                Board.m_EnPassantTarget = PointToBitboard(average(move.m_Start, move.m_End));
            }
            //en passant
            if(move.m_Start.m_X != move.m_End.m_X && Board.GetPieceType(move.m_End) == 0){
                //removing enemy's pawn - move will be executed later
                JustMovePiece(Board, Move({move.m_End.m_X, move.m_Start.m_Y}, {-1, -1}));
            }
        }
        //removing castle possibility after rook move
        if(piece_type == 4){ //rook
            int START_Y;
            if(color == 1)START_Y = 0;
            else START_Y = 7;

            if(move.m_Start.m_X == 0 && move.m_Start.m_Y == START_Y)
                Board.m_LeftCastle[index(color)] = false;
            if(move.m_Start.m_X == 7 && move.m_Start.m_Y == START_Y)
                Board.m_RightCastle[index(color)] = false;
        }

        if(piece_type == 6){ //king
            Board.m_LeftCastle[index(color)] = false;
            Board.m_RightCastle[index(color)] = false;

            if(move.m_Start.m_X - move.m_End.m_X == 2){ //left castle
                JustMovePiece(Board, Move({0, move.m_Start.m_Y}, {3, move.m_Start.m_Y}));
                Board.m_DidCastle[index(color)] = true;
            }
            if(move.m_End.m_X - move.m_Start.m_X == 2){ //right castle
                JustMovePiece(Board, Move({7, move.m_Start.m_Y}, {5, move.m_Start.m_Y}));
                Board.m_DidCastle[index(color)] = true;
            }
        }

        

        JustMovePiece(Board, move);
    }
}