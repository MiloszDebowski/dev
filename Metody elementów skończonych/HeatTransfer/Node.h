#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

struct Node {
    double x, y;

    Node(double x, double y);
    void print() const;

    static std::vector<Node> readNodes(const std::string& grid_file);
};