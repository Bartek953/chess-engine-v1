#include "RNG.h"
#include <random>

namespace chessAI {
    std::random_device rd;

    std::mt19937 rng32(rd());
    std::mt19937_64 rng64(rd());

    std::uniform_int_distribution<uint32_t> dist32(1, INT_MAX-1);
    std::uniform_int_distribution<uint64_t> dist64(1, __LONG_LONG_MAX__ - 1);

    int GetRandomInt()
    {
        return dist32(rng32);
    }

    long long GetRandomLL()
    {
        return dist64(rng64);
    }
}

