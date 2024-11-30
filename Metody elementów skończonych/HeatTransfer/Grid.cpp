#include "Grid.h"
#include<iomanip>

Grid::Grid(const std::vector<Node>& nodes, const std::vector<Element>& elements)
    : nodes(nodes), elements(elements) {}

void Grid::print() const {
    std::cout << std::endl << "\tNODES COORDINATES" << std::endl;
    for (int i = 0; i < nodes.size(); i++) {
        std::cout << i + 1 << ". ";
        if (i < 9) { std::cout << " "; }
        nodes[i].print();
    }

    std::cout << std::endl << "\tELEMENT NODES ID" << std::endl;
    for (int i = 0; i < elements.size(); i++) {
        std::cout << i + 1 << ". ";
        if (i < 9) { std::cout << " "; }
        elements[i].print();
    }
}

void Grid::printLocalHMatricesAndSum(double conductivity, int gauss_points_count) {
    std::vector<std::vector<double>> H_total(4, std::vector<double>(4, 0.0));

    for (const auto& element : elements) {
        auto H_local = element.calculateHMatrix(conductivity, nodes, gauss_points_count);

        std::cout << "\n\tLOCAL H MATRIX FOR ELEMENT: " << element.id << std::endl;
        for (const auto& row : H_local) {
            for (double value : row) {
                std::cout << std::setw(10) << std::fixed << std::setprecision(4) << value << " ";
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                H_total[i][j] += H_local[i][j];
            }
        }
    }

    std::cout << "\n\tTOTAL H MATRIX:" << std::endl;
    for (const auto& row : H_total) {
        for (double value : row) {
            std::cout << std::setw(10) << std::fixed << std::setprecision(4) << value << " ";
        }
        std::cout << std::endl;
    }
}
