#include "CalculateGlobalHMatrix.h"

void CalculateGlobalHMatrix::calculate(const Grid& grid, double conductivity, int gauss_points_count) {
    int NodeCount = int(grid.nodes.size());
    globalHMatrix = std::vector<std::vector<double>>(NodeCount, std::vector<double>(NodeCount, 0.0));

    for (const auto& element : grid.elements) {
        auto H_local = element.calculateHMatrix(conductivity, grid.nodes, gauss_points_count);

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int global_i = element.node_ids[i] - 1;
                int global_j = element.node_ids[j] - 1;
                globalHMatrix[global_i][global_j] += H_local[i][j];
            }
        }
    }
}

void CalculateGlobalHMatrix::printGlobalHMatrix() const {
    std::cout << "\n\tGLOBAL H MATRIX:" << std::endl;
    for (const auto& row : globalHMatrix) {
        for (double value : row) {
            std::cout << std::setw(10) << std::fixed << std::setprecision(4) << value << " ";
        }
        std::cout << std::endl;
    }
}
