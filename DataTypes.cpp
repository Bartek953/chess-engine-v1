#include "DataTypes.h"
#include <initializer_list>
#include <iostream>
#include <string>

int chessAI::sgn(int x){
    if(x>0)return 1;
    if(x==0)return 0;
    return -1;
}

int chessAI::abs(int x)
{
    if(x>0)return x;
    return -x;
}

int chessAI::index(int color)
{
    if(color == 1)return 0;
    return 1;
}

bool chessAI::normalized(int coord)
{
    if(0 <= coord && coord <= 7)return true;
    return false;
}

bool chessAI::is_piece(uint64_t ptr, uint64_t piece)
{
    return (ptr & piece) > 0;
}

chessAI::Point::Point() 
    : m_X(0), m_Y(0) {}

chessAI::Point::Point(int x, int y)
{
    m_X = x;
    m_Y = y;
}

chessAI::Point chessAI::Point::operator +(const Point &other) const
{
    return Point(m_X + other.m_X, m_Y + other.m_Y);
}

bool chessAI::Point::operator==(const Point &other) const
{
    return (m_X == other.m_X && m_Y == other.m_Y);
}

chessAI::Move::Move()
    : m_Start(Point()), m_End(Point()), m_Value(0)
{
}

chessAI::Move::Move(Point P0, Point P1, int value)
{
    m_Start = P0;
    m_End = P1;
    m_Value = value;
}

chessAI::Move::Move(int x0, int y0, int x1, int y1, int value)
{
    m_Start = {x0, y0};
    m_End = {x1, y1};
    m_Value = value;
}

bool chessAI::Move::operator==(const Move &other) const
{
    return (m_Start == other.m_Start && m_End == other.m_End);
}

chessAI::Chessboard::Chessboard()
{
    m_Pawns[0] = 0;
    for(int x=0;x<=7;x++)
        m_Pawns[0] += PointToBitboard({x, 1});
    m_Knights[0] = PointToBitboard({1, 0}) + PointToBitboard({6, 0});
    m_Bishops[0] = PointToBitboard({2, 0}) + PointToBitboard({5, 0});
    m_Rooks[0] = PointToBitboard({0, 0}) + PointToBitboard({7, 0});
    m_Queen[0] = PointToBitboard({3, 0});
    m_King[0] = PointToBitboard({4, 0});

    m_Pawns[1] = 0;
    for(int x=0;x<=7;x++){
        m_Pawns[1] += PointToBitboard({x, 6});
    }
    m_Knights[1] = PointToBitboard({1, 7}) + PointToBitboard({6, 7});
    m_Bishops[1] = PointToBitboard({2, 7}) + PointToBitboard({5, 7});
    m_Rooks[1] = PointToBitboard({0, 7}) + PointToBitboard({7, 7});
    m_Queen[1] = PointToBitboard({3, 7});
    m_King[1] = PointToBitboard({4, 7});
    
    m_EnPassantTarget = 0;

    m_LeftCastle[0] = true;
    m_RightCastle[0] = true;
    m_LeftCastle[1] = true;
    m_RightCastle[1] = true;
    
    m_DidCastle[0] = false;
    m_DidCastle[1] = false;

    /*{//test
        m_Pawns[0] = 0; m_Pawns[1] = 0;
        m_Knights[0] = 0; m_Knights[1] = 0;
        m_Bishops[0]=0;m_Bishops[1]=0;
        m_Rooks[0]=0;m_Rooks[1]=0;
        m_Queen[0]=0;m_Queen[1]=0;
    }*/
}

bool chessAI::normalized(Point P)
{
    if(normalized(P.m_X) && normalized(P.m_Y))return true;
    return false;
}

chessAI::Point chessAI::average(Point P1, Point P2)
{
    return Point((P1.m_X + P2.m_X)/2, (P1.m_Y + P2.m_Y)/2);
}

std::ostream &chessAI::operator<<(std::ostream &os, const Move move)
{
    os << "(" << move.m_Start.m_X << ", " << move.m_Start.m_Y << ") -> (" << move.m_End.m_X << ", " << move.m_End.m_Y << ")\n"; 
    return os;
}

uint64_t chessAI::PointToBitboard(Point P)
{
    uint64_t one = 1;
    uint64_t x = P.m_X;
    uint64_t y = P.m_Y;
    return (one << (x + 8*y));
}
bool chessAI::is_piece(Point P, uint64_t piece)
{
    return (PointToBitboard(P) & piece) > 0;
}

int chessAI::Chessboard::GetPieceType(Point P)
{
    uint64_t bb_tracker = PointToBitboard(P);
    int index;

    index = -6;
    for(uint64_t piece : {
        m_King[1], m_Queen[1], m_Rooks[1], m_Bishops[1], m_Knights[1], m_Pawns[1]
    }){
        if((piece & bb_tracker) > 0)
            return index;
        index++;
    }
    index = 1;
    for(uint64_t piece : {
        m_Pawns[0], m_Knights[0], m_Bishops[0], m_Rooks[0], m_Queen[0], m_King[0]
    }){
        if((piece & bb_tracker) > 0)
            return index;
        index++;
    }
   return 0;
}

int chessAI::Chessboard::GetPieceColor(Point P)
{
    return sgn(GetPieceType(P));
}

void chessAI::Chessboard::Print()
{
    char pieces[7] = {'0', 'P', 'K', 'B', 'R', 'Q', '+'};
    std::string signatures[3] = {"\033[31m", "\033[37m", "\033[32m"}; //red white green
    int type;
    for(int y=7;y>=0;y--){
        for(int x=0;x<=7;x++){
            type = GetPieceType({x, y});
            std::cout << signatures[1 + sgn(type)];

            if(is_piece({x, y}, m_EnPassantTarget))
                std::cout << "\033[34m";
            std::cout << pieces[abs(type)];
            std::cout << ' ';
        }
        std::cout << '\n';
    }
    std::cout << signatures[1];
}

