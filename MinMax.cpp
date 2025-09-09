#include "MinMax.h"

#include "GenMoves.h"
#include "MakeMove.h"
#include "RNG.h"

#include <random>
#include <iostream>
#include <ctime>
#include <atomic>

namespace chessAI {
    //const int checkmate_barrier = 100000000;

    static std::atomic<bool> terminated{false}; //!!!!!! for iterative deepening;

    bool is_better(int new_eval, int old_eval, int color){
        if(new_eval > checkmate_barrier && old_eval > checkmate_barrier)
            return false; //theyre equal
        if(new_eval < -checkmate_barrier && old_eval < -checkmate_barrier)
            return false; //theyre equal
        if(color == 1)
            return (new_eval > old_eval);
        return (new_eval < old_eval);
    }
    bool are_equal(int new_eval, int old_eval, int color){
        return !is_better(new_eval, old_eval, color) && !is_better(old_eval, new_eval, color);
    }
    Move MinMax(Chessboard &Board, int color, int depth, int add_depth, bool checkDraw, int alpha, int beta)
    {
        if(terminated)return Move(0, 0, 0, 0, 0);
        //if(depth == 3)srand(time(0));

        std::vector<Move> moves = GenMoves(Board, color);

        int best_eval;
        if(color == 1)
            best_eval = -2*KING_VALUE;
        else
            best_eval = 2*KING_VALUE;

        std::vector<Move> best_moves;
        best_moves.emplace_back(-1, -1, -1, -1);

        //check if its a draw
        
        if(color == 1){
            if(checkDraw && MinMax(Board, -1, 0).m_Value > - checkmate_barrier && MinMax(Board, 1, 1).m_Value <= -checkmate_barrier){
                return Move(-1, -1, -1, -1, 0);
            }
        }
        else {
            if(checkDraw && MinMax(Board, 1, 0).m_Value < checkmate_barrier && MinMax(Board, -1, 1).m_Value >= checkmate_barrier){
                return Move(-1, -1, -1, -1, 0);
            }
        }

        int iter = 0;
        for(Move move : moves)
        {
            /*if(depth == 3){
                std::cout << alpha << ' ' << beta << '\n';
            }*/
            if(color == 1){
                alpha = std::max(alpha, best_eval);
            }
            else {
                beta = std::min(beta, best_eval);
            }
            Chessboard NewBoard = Board;
            MakeMove(NewBoard, move);

            int current_eval;

            current_eval = Evaluate(NewBoard);

            if(depth > 0) {
                if((color == 1 && current_eval >= checkmate_barrier) || (color == -1 && current_eval <= -checkmate_barrier)){
                    //kings capture -> end game
                    Move ending_move = move;
                    ending_move.m_Value = current_eval;
                    return ending_move;
                }
                if(terminated)return Move(0, 0, 0, 0, 0);
                current_eval = MinMax(NewBoard, -color, depth-1, add_depth, checkDraw, alpha, beta).m_Value;
            }

            //deeper calculation for forcing moves - captures
            if(depth == 0 && add_depth > 0 && move.m_Value > 0){
                if((color == 1 && current_eval >= checkmate_barrier) || (color == -1 && current_eval <= -checkmate_barrier)){
                    //kings capture -> end game
                    Move ending_move = move;
                    ending_move.m_Value = current_eval;
                    return ending_move;
                }
                if(terminated)return Move(0, 0, 0, 0, 0);
                current_eval = MinMax(NewBoard, -color, 0, add_depth-1, checkDraw, alpha, beta).m_Value;
            }

            if(are_equal(current_eval, best_eval, color)){
                best_moves.push_back(move);
            }
            if(is_better(current_eval, best_eval, color)){
                best_eval = current_eval;
                best_moves.clear();
                best_moves.push_back(move);
            }

            iter++;

            if(color == 1 && best_eval > beta)
                break;
            if(color == -1 && best_eval < alpha)
                break;
            if(depth == 3){
                //std::cout << ((double)iter / (double)moves.size())*100 << "% ";
                //std::cout << "OPCJA " << current_eval << ": " << move.m_Value << ' ' << move;
            }
            
        }
        if(depth < DEPTH || best_moves.size() == 1){
            Move result = best_moves[0];
            result.m_Value = best_eval;
            return result;
        }
        //jesli kilka takich samych ruchow -> rozwaz ten z najlepszych Evaluate(Move)
        //rezultat: bardziej agresywna gra, ale mniej "tracenia czasu", odsuwania w czasie wykonanie dobrego ruchu
        std::vector<Move> faster_moves;
        int best_fast_eval = (color == 1) ? -2*KING_VALUE : 2*KING_VALUE;
        for(auto move : best_moves){
            Chessboard NewBoard = Board;
            MakeMove(NewBoard, move);
            int curr_eval = MinMax(NewBoard, -color, 0, 0, true).m_Value;

            if(is_better(curr_eval, best_fast_eval, color)){
                best_fast_eval = curr_eval;
                faster_moves.clear();
            }
            if(are_equal(curr_eval, best_fast_eval, color)){
                faster_moves.push_back(move);
            }
        }

        if(faster_moves.size() == 0)
            std::cout << "MinMax:57 ERROR: vector size == 0, dividing by 0 in modulo operation!!!\n";
        int index = rand() % faster_moves.size();
        //int index = GetRandomInt() % faster_moves.size();

        Move result = faster_moves[index];
        result.m_Value = best_eval;

        return result;
    }
    void StartMinMax()
    {
        terminated = false;
    }
    void StopMinMax()
    {
        terminated = true;
    }
}