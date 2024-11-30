#include "Node.h"

Node::Node(double x, double y) : x(x), y(y) {}

void Node::print() const {
    std::cout << " x = " << x << " ; y = " << y << std::endl;
}

std::vector<Node> Node::readNodes(const std::string& grid_file) {
    std::ifstream file(grid_file);
    std::string line;
    std::vector<Node> nodes;
    bool node_section = false;

    while (getline(file, line)) {
        if (line.find("*Node") != std::string::npos) {
            node_section = true;
            continue;
        }
        if (line.find("*Element") != std::string::npos) break;
        if (node_section) {
            std::istringstream iss(line);
            int node_id;
            double x, y;
            char comma;
            if (iss >> node_id >> comma >> x >> comma >> y) {
                nodes.emplace_back(x, y);
            }
        }
    }
    return nodes;
}
