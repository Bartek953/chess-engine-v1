#include "ZobristHashing.h"
#include "RNG.h"

namespace chessAI {
    //color_ind piece_type x y
    long long HashTable1[2][7][8][8];
    long long HashTable2[2][7][8][8];

    void HashInit()
    {
        for(int color_ind : {0, 1}){
            for(int piece_type : {1, 2, 3, 4, 5, 6}){
                for(int x=0;x<=7;x++){
                    for(int y=0;y<=7;y++){
                        HashTable1[color_ind][piece_type][x][y] = GetRandomLL();
                        HashTable2[color_ind][piece_type][x][y] = GetRandomLL();
                    }
                }
            }
        }
    }
    Hash HashPosition(Chessboard &Board)
    {
        int result1 = 0;
        int result2 = 0;
        for(int x=0;x<=7;x++){
            for(int y=0;y<=7;y++){
                if(Board.GetPieceType({x, y}) == 0)
                    continue;
                int color_ind = index(Board.GetPieceColor({x, y}));
                int piece_type = abs(Board.GetPieceType({x, y}));
                result1 ^= HashTable1[color_ind][piece_type][x][y];
                result2 ^= HashTable2[color_ind][piece_type][x][y];
            }
        }
        return {result1, result2};
    }
    Hash HashMove(Hash current_positions_hash, Chessboard &Board, Move &move)
    {
        int result1 = current_positions_hash.first;
        int result2 = current_positions_hash.second;

        //Start point
        int color_ind = index(Board.GetPieceColor(move.m_Start));
        int piece_type = abs(Board.GetPieceType(move.m_Start));
        int x = move.m_Start.m_X;
        int y = move.m_Start.m_Y;

        result1 ^= HashTable1[color_ind][piece_type][x][y];
        result2 ^= HashTable2[color_ind][piece_type][x][y];

        //End point
        if(Board.GetPieceColor({move.m_End}) != 0){
            int color_ind = index(Board.GetPieceColor(move.m_End));
            int piece_type = abs(Board.GetPieceType(move.m_End));
            int x = move.m_End.m_X;
            int y = move.m_End.m_Y;

            result1 ^= HashTable1[color_ind][piece_type][x][y];
            result2 ^= HashTable2[color_ind][piece_type][x][y];
        }


        return {result1, result2};
    }
}