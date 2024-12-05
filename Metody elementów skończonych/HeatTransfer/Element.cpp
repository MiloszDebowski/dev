#include "Element.h"

//tworzy element
Element::Element(int id, const std::vector<int>& nodes) : id(id), node_ids(nodes) {}

//wypisywanie 
void Element::print() const {
    std::cout << "ID[";
    for (size_t i = 0; i < node_ids.size(); ++i) {
        std::cout << node_ids[i];
        if (i < node_ids.size() - 1) std::cout << ",";
    }
    std::cout << "]" << std::endl;
}

//wczytywanie elementów z pliku
std::vector<Element> Element::readElements(const std::string& grid_file) {
    std::ifstream file(grid_file);
    std::string line;
    std::vector<Element> elements;
    bool element_section = false;

    while (getline(file, line)) {
        if (line.find("*Element") != std::string::npos) {
            element_section = true;
            continue;
        }
        if (line.find("*BC") != std::string::npos)break;
        if (element_section) {
            std::istringstream iss(line);
            int element_id, n1, n2, n3, n4;
            char comma;
            if (iss >> element_id >> comma >> n1 >> comma >> n2 >> comma >> n3 >> comma >> n4) {
                elements.emplace_back(element_id, std::vector<int>{n1, n2, n3, n4});
            }
        }
    }
    return elements;
}

//liczenie macierzy H
std::vector<std::vector<double>> Element::calculateHMatrix(double conductivity, const std::vector<Node>& nodes, int gauss_points_count) const {
    std::vector<double> gauss_points, gauss_weights;
    if (gauss_points_count == 2) {
        gauss_points = { -1.0 / sqrt(3), 1.0 / sqrt(3) };
        gauss_weights = { 1.0, 1.0 };
    }
    else if (gauss_points_count == 3) {
        gauss_points = { -sqrt(3.0 / 5.0), 0.0, sqrt(3.0 / 5.0) };
        gauss_weights = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
    }
    else {
        throw std::invalid_argument("Unsupported number of Gauss points.");
    }

    std::vector<std::vector<double>> H_local(4, std::vector<double>(4, 0.0));

    for (double xi : gauss_points) {
        for (double eta : gauss_points) {
            //pochodne funkcji kszta³tu - lokalne
            std::vector<double> dN_dxi = { -0.25 * (1 - eta), 0.25 * (1 - eta), 0.25 * (1 + eta), -0.25 * (1 + eta) };
            std::vector<double> dN_deta = { -0.25 * (1 - xi), -0.25 * (1 + xi), 0.25 * (1 + xi), 0.25 * (1 - xi) };

            //Macierz Jakobiego
            double J11 = 0, J12 = 0, J21 = 0, J22 = 0;
            for (int i = 0; i < 4; i++) {
                J11 += dN_dxi[i] * nodes[node_ids[i] - 1].x;
                J12 += dN_dxi[i] * nodes[node_ids[i] - 1].y;
                J21 += dN_deta[i] * nodes[node_ids[i] - 1].x;
                J22 += dN_deta[i] * nodes[node_ids[i] - 1].y;
            }
            //jakobian
            double detJ = J11 * J22 - J12 * J21;

            //odwrócona macierz Jakobiego
            double invJ11 = J22 / detJ;
            double invJ12 = -J12 / detJ;
            double invJ21 = -J21 / detJ;
            double invJ22 = J11 / detJ;

            //pochodne funkcji kszta³tu - globalne
            std::vector<double> dN_dx(4), dN_dy(4);
            for (int i = 0; i < 4; i++) {
                dN_dx[i] = invJ11 * dN_dxi[i] + invJ12 * dN_deta[i];
                dN_dy[i] = invJ21 * dN_dxi[i] + invJ22 * dN_deta[i];
            }

            //sk³adanie lokalnej macierzy H
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    H_local[i][j] += conductivity * (dN_dx[i] * dN_dx[j] + dN_dy[i] * dN_dy[j]) * detJ;
                }
            }
        }
    }

    return H_local;
}
