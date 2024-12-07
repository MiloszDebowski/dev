#pragma once
#include <vector>
#include <iostream>
#include<iomanip>
#include "Node.h"
#include "Element.h"

struct Grid {
    std::vector<Node> nodes;
    std::vector<Element> elements;

    Grid(const std::vector<Node>& nodes, const std::vector<Element>& elements);
    void print() const;
    void printLocalHMatricesAndSum(double conductivity, int gauss_points_count);
};