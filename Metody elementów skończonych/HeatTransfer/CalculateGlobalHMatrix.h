#pragma once
#include <vector>
#include <iomanip>
#include <iostream>
#include "Grid.h"

struct CalculateGlobalHMatrix {
    std::vector<std::vector<double>> globalHMatrix;

    void calculate(const Grid& grid, double conductivity, int gauss_points_count);
    void printGlobalHMatrix() const;
};