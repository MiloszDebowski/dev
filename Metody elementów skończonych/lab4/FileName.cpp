#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <iomanip>
#include <cmath>
using namespace std;

struct GlobalData {
    double SimulationTime, SimulationStepTime, Conductivity, Alfa, Tot, InitialTemp, Density, SpecificHeat;
    int nN, nE;

    GlobalData(double simTime, double stepTime, double cond, double al, double to, double initTemp, double dens, double specHeat, int nodes, int elems)
        : SimulationTime(simTime), SimulationStepTime(stepTime), Conductivity(cond), Alfa(al), Tot(to), InitialTemp(initTemp), Density(dens), SpecificHeat(specHeat), nN(nodes), nE(elems) {}

    void print() const {
        cout << "\tGLOBAL DATA" << endl;
        cout << "SimulationTime: " << setprecision(11) << SimulationTime << endl;
        cout << "SimulationStepTime: " << SimulationStepTime << endl;
        cout << "Conductivity: " << Conductivity << endl;
        cout << "Alfa: " << Alfa << endl;
        cout << "Tot: " << Tot << endl;
        cout << "InitialTemp: " << InitialTemp << endl;
        cout << "Density: " << Density << endl;
        cout << "SpecificHeat: " << SpecificHeat << endl;
        cout << "nN (Nodes number): " << nN << endl;
        cout << "nE (Elements number): " << nE << endl;
    }

    static GlobalData readData(const string& grid_file) {
        ifstream file(grid_file);
        string line;
        double simTime, stepTime, cond, al, to, initTemp, dens, specHeat;
        int nodes, elems;

        while (getline(file, line)) {
            istringstream iss(line);
            string key,key1;
            double value;
            if (iss >> key >> value) {
                if (key == "SimulationTime") simTime = value;
                else if (key == "SimulationStepTime") stepTime = value;
                else if (key == "Conductivity") cond = value;
                else if (key == "Alfa") al = value;
                else if (key == "Tot") to = value;
                else if (key == "InitialTemp") initTemp = value;
                else if (key == "Density") dens = value;
                else if (key == "SpecificHeat") specHeat = value;
            }

            iss.clear();
            iss.str(line);

            if (iss >> key >> key1 >> value)
            {
                if (key == "Nodes" && key1 == "number")
                {
                    nodes = static_cast<int>(value);
                }
                else if (key == "Elements" && key1 == "number")
                {
                    elems = static_cast<int>(value);
                }
            }
        }
                return GlobalData(simTime, stepTime, cond, al, to, initTemp, dens, specHeat, nodes, elems);
    }
};

struct Node {
    double x, y;

    Node(double x, double y) : x(x), y(y) {}

    void print() const {
        cout << "x = " << x << "   Y = " << y << endl;
    }

    static vector<Node> readNodes(const string& grid_file) {
        ifstream file(grid_file);
        string line;
        vector<Node> nodes;
        bool node_section = false;

        while (getline(file, line)) {
            if (line.find("*Node") != string::npos) {
                node_section = true;
                continue;
            }
            if (line.find("*Element") != string::npos) break;
            if (node_section) {
                istringstream iss(line);
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
};

struct Element {
    int id;
    array<int, 4> node_ids;

    Element(int id, array<int, 4> nodes) : id(id), node_ids(nodes) {}

    void print() const {
        cout << "ID[" << node_ids[0] << "," << node_ids[1] << "," << node_ids[2] << "," << node_ids[3] << "]" << endl;
    }

    static vector<Element> readElements(const string& grid_file) {
        ifstream file(grid_file);
        string line;
        vector<Element> elements;
        bool element_section = false;

        while (getline(file, line)) {
            if (line.find("*Element") != string::npos) {
                element_section = true;
                continue;
            }
            if (line.find("*BC") != string::npos)
            {
                break;
            }
            if (element_section) {
                istringstream iss(line);
                int element_id, n1, n2, n3, n4;
                char comma;
                if (iss >> element_id >> comma >> n1 >> comma >> n2 >> comma >> n3 >> comma >> n4) {
                    elements.emplace_back(element_id, array<int, 4>{n1, n2, n3, n4});
                }
            }
        }
        return elements;
    }

    vector<vector<double>> computeLocalHMatrix(double conductivity, const vector<Node>& nodes) const {
        // 2x2 Gaussian quadrature points and weights for integration
        const array<double, 2> gauss_points = { -1.0 / sqrt(3), 1.0 / sqrt(3) };
        const array<double, 2> gauss_weights = { 1.0, 1.0 };

        vector<vector<double>> H_local(4, vector<double>(4, 0.0));

        // Loop over Gaussian points
        for (double xi : gauss_points) {
            for (double eta : gauss_points) {
                // Shape function derivatives in local coordinates
                array<double, 4> dN_dxi = { -0.25 * (1 - eta), 0.25 * (1 - eta), 0.25 * (1 + eta), -0.25 * (1 + eta) };
                array<double, 4> dN_deta = { -0.25 * (1 - xi), -0.25 * (1 + xi), 0.25 * (1 + xi), 0.25 * (1 - xi) };

                // Calculate Jacobian and its determinant
                double J11 = 0, J12 = 0, J21 = 0, J22 = 0;
                for (int i = 0; i < 4; i++) {
                    J11 += dN_dxi[i] * nodes[node_ids[i] - 1].x;
                    J12 += dN_dxi[i] * nodes[node_ids[i] - 1].y;
                    J21 += dN_deta[i] * nodes[node_ids[i] - 1].x;
                    J22 += dN_deta[i] * nodes[node_ids[i] - 1].y;
                }
                double detJ = J11 * J22 - J12 * J21;

                // Inverse Jacobian
                double invJ11 = J22 / detJ;
                double invJ12 = -J12 / detJ;
                double invJ21 = -J21 / detJ;
                double invJ22 = J11 / detJ;

                // Shape function derivatives in global coordinates
                array<double, 4> dN_dx, dN_dy;
                for (int i = 0; i < 4; i++) {
                    dN_dx[i] = invJ11 * dN_dxi[i] + invJ12 * dN_deta[i];
                    dN_dy[i] = invJ21 * dN_dxi[i] + invJ22 * dN_deta[i];
                }

                // Compute contributions to the H matrix at this integration point
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        H_local[i][j] += conductivity * (dN_dx[i] * dN_dx[j] + dN_dy[i] * dN_dy[j]) * detJ;
                    }
                }
            }
        }

        return H_local;
    }
};

struct Grid {
    vector<Node> nodes;
    vector<Element> elements;
    vector<vector<double>> globalHMatrix;

    Grid(const vector<Node>& nodes, const vector<Element>& elements)
        : nodes(nodes), elements(elements), globalHMatrix(nodes.size(), vector<double>(nodes.size(), 0.0)) {}

    void assembleGlobalHMatrix(double conductivity) {
        for (const auto& element : elements) {
            auto localH = element.computeLocalHMatrix(conductivity, nodes);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    globalHMatrix[element.node_ids[i] - 1][element.node_ids[j] - 1] += localH[i][j];
                }
            }
        }
    }

    void printGlobalHMatrix() const {
        cout << "\n       H globalna" << endl;
        for (const auto& row : globalHMatrix) {
            for (double value : row) {
                cout << setw(10) << fixed << setprecision(4) << value << " ";
            }
            cout << endl;
        }
    }

    void print() const {
        cout << endl << "\tNODES COORDINATES" << endl;
        for (int i = 0; i < nodes.size(); i++) {
            nodes[i].print();
        }
        
        cout<<endl << "\tELEMENT NODES ID" << endl;
        for (int i = 0;i<elements.size();i++) 
        {
            elements[i].print();
        }
    }

    void printLocalHMatricesAndSum(double conductivity) {
        vector<vector<double>> H_total(4, vector<double>(4, 0.0));

        for (const auto& element : elements) {
            auto H_local = element.computeLocalHMatrix(conductivity, nodes);

            cout << "\nLocal H matrix for Element ID: " << element.id << endl;
            for (const auto& row : H_local) {
                for (double value : row) {
                    cout << setw(10) << fixed << setprecision(4) << value << " ";
                }
                cout << endl;
            }

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    H_total[i][j] += H_local[i][j];
                }
            }
        }

        cout << "\nTotal H matrix (Sum of all local H matrices):" << endl;
        for (const auto& row : H_total) {
            for (double value : row) {
                cout << setw(10) << fixed << setprecision(4) << value << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    //string grid_file = "Test1_4_4.txt";
    string grid_file = "Test2_4_4_MixGrid.txt";

    GlobalData global_data = GlobalData::readData(grid_file);
    global_data.print();

    vector<Node> nodes = Node::readNodes(grid_file);
    vector<Element> elements = Element::readElements(grid_file);

    Grid grid(nodes, elements);
    grid.print();

    
    grid.printLocalHMatricesAndSum(global_data.Conductivity);

    return 0;
}
