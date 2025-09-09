#include "PSQT.h"

namespace chessAI {
    int CentralPSQT(Point P, int delta)
    {
        int x = P.m_X, y = P.m_Y;
        x = (x <= 3) ? x : (7 - x);
        y = (y <= 3) ? y : (7 - y);

        return std::min(x, y) * delta;
    }
    int PromotionPSQT(Point P, int color, int delta)
    {
        int ratios[] = {0, 1, 2, 5, 12, 0};
        if(color == 1){
            return delta * ratios[std::max(0, P.m_Y - 2)];
        }
        else {
            return delta * ratios[std::max(0, 5 - P.m_Y)];
        }
    }
}