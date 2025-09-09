#include "CheckIfCheckmated.h"

#include "MinMax.h"
#include "GenMoves.h"
#include <iostream>
#include <cstdlib>

namespace chessAI {
    void CheckIfCheckmated(Chessboard &Board, int color)
    {
        std::vector<Move> moves = GenMoves(Board, color);

        if(color == 1){
            if(MinMax(Board, -1, 0).m_Value <= -checkmate_barrier){ //szach
                if(MinMax(Board, 1, 1).m_Value <= -checkmate_barrier || GenMoves(Board, 1).size()==0){ //szachmat
                    std::cout << "Checkmate! Black wins\n";
                    exit(0);
                }
            }
            else if(MinMax(Board, 1, 1).m_Value <= -checkmate_barrier){
                std::cout << "Remis!\n";
                exit(0);
            }
        }
        if(color == -1){
            if(MinMax(Board, 1, 0).m_Value >= checkmate_barrier){ //szach
                if(MinMax(Board, -1, 1).m_Value >= checkmate_barrier  || GenMoves(Board, -1).size()==0){ //szachmat
                    std::cout << "Checkmate! White wins\n";
                    exit(0);
                }
            }
            else if(MinMax(Board, -1, 1).m_Value >= checkmate_barrier){
                std::cout << "Remis!\n";
                exit(0);
            }
        }
        if(moves.size() == 0){
            std::cout << "Remis!\n";
            exit(0);
        }
    }
}