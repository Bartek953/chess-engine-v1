#pragma once
#include "DataTypes.h"

namespace chessAI {
    int CentralPSQT(Point P, int delta);
    int PromotionPSQT(Point P, int color, int delta);
}