#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdexcept>

#include "Node.h"

struct Element {
    int id;
    std::vector<int> node_ids;

    Element(int id, const std::vector<int>& nodes);
    void print() const;

    static std::vector<Element> readElements(const std::string& grid_file);

    std::vector<std::vector<double>> calculateHMatrix(double conductivity, const std::vector<Node>& nodes, int gauss_points_count) const;
};