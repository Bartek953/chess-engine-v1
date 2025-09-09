#include "IterativeDeepening.h"

#include "MinMax.h"

#include <chrono>
#include <thread>
#include <atomic>

namespace chessAI {
    static std::atomic<bool> terminated{false};

    void TerminateMinMax(int time_limit){
        std::this_thread::sleep_for(std::chrono::seconds(time_limit));
        StopMinMax();
        terminated = true;

    }
    Move IterativeDeepening(Chessboard &Board, int color, int time_limit)
    {
        StartMinMax();
        terminated = false;
        Move best_move = MinMax(Board, color, DEPTH, ADD_DEPTH, true);
        std::cout << "depth: " << DEPTH << " passed\n";
        std::cout << best_move.m_Value << ": " << best_move;

        std::thread t1(TerminateMinMax, time_limit);
        //t1.detach();

        for(int depth = DEPTH+2; depth <= 10; depth += 2){
            if(terminated)
                break;
            Move current_move = MinMax(Board, color, depth, ADD_DEPTH);
            if(!terminated){
                best_move = current_move;
                std::cout << "depth: " << depth << " passed\n\n";
                std::cout << best_move.m_Value << ": " << best_move;
            }
        }

        if(t1.joinable())
            t1.join();
        return best_move;
    }
}