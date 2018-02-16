#include "rng.h"

namespace Rng {
    std::mt19937 gen(time(nullptr));
    int IntInRange(int low, int high) {
        std::uniform_int_distribution<> dis(low, high);
        return dis(gen);
    }
}
