#pragma once
#include "Config.h"
#include <cstdint>
#include <iostream>
#include <utility>

namespace chessAI {
    int sgn(int x);
    int abs(int x);
    int index(int color);
    bool normalized(int coord);
    bool is_piece(uint64_t ptr, uint64_t piece);

    using Hash = std::pair<long long, long long>;

    class Point {
        public:
        int m_X;
        int m_Y;

        Point();
        Point(int x, int y);

        Point operator +(const Point& other) const;
        bool operator ==(const Point& other) const;
    };

    bool normalized(Point P);
    Point average(Point P1, Point P2);

    class Move {
        public:
        Point m_Start;
        Point m_End;
        int m_Value;

        Move();
        Move(Point P0, Point P1, int value = 0);
        Move(int x0, int y0, int x1, int y1, int value = 0);

        bool operator ==(const Move& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Move move);
    };

    uint64_t PointToBitboard(Point P);
    bool is_piece(Point P, uint64_t piece);

    class Chessboard {
        public:
        uint64_t m_Pawns[2];
        uint64_t m_Knights[2];
        uint64_t m_Bishops[2];
        uint64_t m_Rooks[2];
        uint64_t m_Queen[2];
        uint64_t m_King[2];

        uint64_t m_EnPassantTarget; //to track en passant possibility

        bool m_LeftCastle[2];
        bool m_RightCastle[2];
        bool m_DidCastle[2];

        Chessboard();

        int GetPieceType(Point P);
        int GetPieceColor(Point P);
        void Print();
    };
}