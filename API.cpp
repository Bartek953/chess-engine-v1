#include "API.h"
#include <string>
#include <iostream>
#include <chrono>
#include <random>
#include <unistd.h>

#include "CheckMove.h"
#include "MakeMove.h"
#include "Evaluate.h"
#include "MinMax.h"
#include "CheckIfCheckmated.h"
#include "IterativeDeepening.h"

#include "cstdlib"

namespace chessAI {
    static Chessboard MainBoard;

    double WholeTime = 0;
    int NofTimes = 0;

    Move UserInput(int color) {
        std::string color_str;
        if(color == 1)
            color_str = "white";
        else
            color_str = "black";
        std::cout << "Please enter " << color_str << " move (x0 y0 x1 y1): ";
        int x0, y0, x1, y1;
        std::cin >> x0 >> y0 >> x1 >> y1;
        while(!CheckMove(MainBoard, color, Move({x0, y0}, {x1, y1}))){
            std::cout << "Incorrect move. Please try again: ";
            std::cin >> x0 >> y0 >> x1 >> y1;
        }
        return Move({x0, y0}, {x1, y1});
    }

    void Init()
    {
        std::cout << "You're using chess engine v1! Good luck!\n";
        std::cout << "DEPTH: " << DEPTH << " + " << ADD_DEPTH << " (" << (DEPTH+1)/2 << " + " << ADD_DEPTH/2 << " moves)\n";
        std::cout << "Time for checking more depths: " << TIME << "s\n";
        std::cout << KING_VALUE <<'\n' << checkmate_barrier <<'\n';
        int k1 = 2*KING_VALUE, k2 = -2*KING_VALUE;
        std::cout << k1 << ' ' << k2 << '\n';
        srand(getpid()); //okay????
        MainBoard.Print();
    }

    void WhiteMove()
    {
        Move move = UserInput(1);
        MakeMove(MainBoard, move);
    }

    bool WhiteMove(Move move)
    {
        CheckIfCheckmated(MainBoard, 1);

        if(!CheckMove(MainBoard, 1, move)){
            return false;
        }
        Chessboard NewBoard = MainBoard;
        MakeMove(NewBoard, move);
        if(MinMax(NewBoard, -1, 0).m_Value <= -checkmate_barrier){
            return false;
        }
        
        MakeMove(MainBoard, move);
            
        CheckIfCheckmated(MainBoard, -1);
        return true;
    }

    void BlackMove()
    {
        std::cout << "Evaluatiopn: " << Evaluate(MainBoard) << '\n';
        auto start = std::chrono::high_resolution_clock::now();

        //Move move = MinMax(MainBoard, -1, DEPTH, ADD_DEPTH, true);
        Move move = IterativeDeepening(MainBoard, -1, TIME);

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        double time = (double)duration.count() / 1000;
        std::cout << "MinMax took " << time << "seconds\n";


        std::cout << "BLACK: " << move.m_Value << ": " << move;
        MakeMove(MainBoard, move);

        WholeTime += time;
        NofTimes++;
        std::cout << "MinMax average time: " << (WholeTime / NofTimes) << " seconds\n";
        std::cout << "Evaluation: " << Evaluate(MainBoard) << "\n\n";
    }
    Chessboard GetBoard()
    {
        return MainBoard;
    }
    std::array<std::array<int, 8>, 8> GetBoardAsArray()
    {
        std::array<std::array<int, 8>, 8> result;

        for(int y = 0; y <= 7; y++){
            for(int x = 0; x <= 7; x++){
                result[x][y] = MainBoard.GetPieceType({x, y});
            }
        }

        return result;
    }
    int GetEvaluation()
    {
        return Evaluate(MainBoard);
    }
}