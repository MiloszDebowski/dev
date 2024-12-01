#pragma once
#include <vector>

struct Solve {
    std::vector<std::vector<double>> globalHMatrix;

    Solve(std::vector<std::vector<double>> calculatedGlobalHMatrix);
};