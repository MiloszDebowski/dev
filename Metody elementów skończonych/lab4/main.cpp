#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <cstring>
using namespace std;

struct GlobalData {
    double SimulationTime, SimulationStepTime, Conductivity, Alfa, Tot, InitialTemp, Density, SpecificHeat;
    int nN, nE;

    GlobalData(double simTime, double stepTime, double cond, double al, double to, double initTemp, double dens, double specHeat, int nodes, int elems)
        : SimulationTime(simTime), SimulationStepTime(stepTime), Conductivity(cond), Alfa(al), Tot(to), InitialTemp(initTemp), Density(dens), SpecificHeat(specHeat), nN(nodes), nE(elems) {}

    void print() const {
        cout << "\tGLOBAL DATA" << endl;
        cout << "Simulation Time: " << setprecision(11) << SimulationTime << endl;
        cout << "Simulation Step Time: " << SimulationStepTime << endl;
        cout << "Conductivity: " << Conductivity << endl;
        cout << "Alfa: " << Alfa << endl;
        cout << "Tot: " << Tot << endl;
        cout << "Initial Temperature: " << InitialTemp << endl;
        cout << "Density: " << Density << endl;
        cout << "SpecificHeat: " << SpecificHeat << endl;
        cout << "nN (Nodes number): " << nN << endl;
        cout << "nE (Elements number): " << nE << endl;
    }

    static GlobalData readData(const string& grid_file) {
        ifstream file(grid_file);
        string line;
        double simTime = 0, stepTime = 0, cond = 0, al = 0, to = 0, initTemp = 0, dens = 0, specHeat = 0;
        int nodes = 0, elems = 0;

        while (getline(file, line)) {
            istringstream iss(line);
            string key, key1;
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

            if (iss >> key >> key1 >> value) {
                if (key == "Nodes" && key1 == "number") {
                    nodes = static_cast<int>(value);
                }
                else if (key == "Elements" && key1 == "number") {
                    elems = static_cast<int>(value);
                }
            }
        }
        return GlobalData(simTime, stepTime, cond, al, to, initTemp, dens, specHeat, nodes, elems);
    }
};

struct Node {
    double x, y;
    bool BC;

    Node(double x, double y) : x(x), y(y), BC(0) {}

    void print() const {
        cout << " x = " << x << " ; y = " << y << "; BC = " << (BC ? "True" : "False") << endl;
    }

    static vector<Node> readNodes(const string& grid_file) {
        ifstream file(grid_file);
        string line;
        vector<Node> nodes;
        bool node_section = false;
        vector<int> boundary_conditions;
        bool BC_section = false;


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

        while (getline(file, line)) {
            if (line.find("*BC") != string::npos) {
                BC_section = true;
                continue;
            }
            if (BC_section) {
                istringstream iss(line);
                int node_id;
                while (iss >> node_id) {
                    boundary_conditions.push_back(node_id);
                    if (iss.peek() == ',') {
                        iss.ignore();
                    }
                }
            }
        }

        for (int i = 0; i < nodes.size(); ++i) {
            for (const auto& condition : boundary_conditions) {
                if (i + 1 == condition) {
                    nodes[i].BC = true;
                }
            }
        }

        return nodes;
    }
};

double calculateEdgeLength(const Node& n1, const Node& n2) {
    return sqrt(pow(n2.x - n1.x, 2) + pow(n2.y - n1.y, 2));
}

struct Element {
    int id;
    vector<int> node_ids;

    Element(int id, const vector<int>& nodes) : id(id), node_ids(nodes) {}

    void print() const {
        cout << "ID[";
        for (size_t i = 0; i < node_ids.size(); ++i) {
            cout << node_ids[i];
            if (i < node_ids.size() - 1) cout << ",";
        }
        cout << "]" << endl;
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
            if (line.find("*BC") != string::npos) {
                break;
            }
            if (element_section) {
                istringstream iss(line);
                int element_id, n1, n2, n3, n4;
                char comma;
                if (iss >> element_id >> comma >> n1 >> comma >> n2 >> comma >> n3 >> comma >> n4) {
                    elements.emplace_back(element_id, vector<int>{n1, n2, n3, n4});
                }
            }
        }
        return elements;
    }

    vector<vector<double>> calculateHMatrix(double conductivity, const vector<Node>& nodes, int gauss_points_count) const {
        vector<double> gauss_points, gauss_weights;
        if (gauss_points_count == 2) {
            gauss_points = { -1.0 / sqrt(3), 1.0 / sqrt(3) };
            gauss_weights = { 1.0, 1.0 };
        }
        else if (gauss_points_count == 3) {
            gauss_points = { -sqrt(3.0 / 5.0), 0.0, sqrt(3.0 / 5.0) };
            gauss_weights = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
        }
        else {
            throw invalid_argument("Unsupported number of Gauss points.");
        }

        vector<vector<double>> H_local(4, vector<double>(4, 0.0));

        for (double xi : gauss_points) {
            for (double eta : gauss_points) {
                vector<double> dN_dxi = { -0.25 * (1 - eta), 0.25 * (1 - eta), 0.25 * (1 + eta), -0.25 * (1 + eta) };
                vector<double> dN_deta = { -0.25 * (1 - xi), -0.25 * (1 + xi), 0.25 * (1 + xi), 0.25 * (1 - xi) };

                double J11 = 0, J12 = 0, J21 = 0, J22 = 0;
                for (int i = 0; i < 4; ++i) {
                    J11 += dN_dxi[i] * nodes[node_ids[i] - 1].x;
                    J12 += dN_dxi[i] * nodes[node_ids[i] - 1].y;
                    J21 += dN_deta[i] * nodes[node_ids[i] - 1].x;
                    J22 += dN_deta[i] * nodes[node_ids[i] - 1].y;
                }
                double detJ = J11 * J22 - J12 * J21;

                double invJ11 = J22 / detJ;
                double invJ12 = -J12 / detJ;
                double invJ21 = -J21 / detJ;
                double invJ22 = J11 / detJ;

                vector<double> dN_dx(4), dN_dy(4);
                for (int i = 0; i < 4; ++i) {
                    dN_dx[i] = invJ11 * dN_dxi[i] + invJ12 * dN_deta[i];
                    dN_dy[i] = invJ21 * dN_dxi[i] + invJ22 * dN_deta[i];
                }

                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; j++) {
                        H_local[i][j] += conductivity * (dN_dx[i] * dN_dx[j] + dN_dy[i] * dN_dy[j]) * detJ;
                    }
                }
            }
        }

        return H_local;
    }

    vector<vector<double>> calculateHBCMatrix(double alpha, const vector<Node>& nodes, int gauss_points_count) const {
        vector<double> gauss_points, gauss_weights;
        if (gauss_points_count == 2) {
            gauss_points = { -1.0 / sqrt(3), 1.0 / sqrt(3) };
            gauss_weights = { 1.0, 1.0 };
        }
        else if (gauss_points_count == 3) {
            gauss_points = { -sqrt(3.0 / 5.0), 0.0, sqrt(3.0 / 5.0) };
            gauss_weights = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
        }
        else {
            throw invalid_argument("Unsupported number of Gauss points.");
        }

        vector<vector<double>> HBC_local(4, vector<double>(4, 0.0));
        vector<vector<int>> edges = { {0, 1}, {1, 2}, {2, 3}, {3, 0} };

        for (const auto& edge : edges) {
            int n1 = node_ids[edge[0]] - 1;
            int n2 = node_ids[edge[1]] - 1;

            if (nodes[n1].BC && nodes[n2].BC) {
                double edge_length = calculateEdgeLength(nodes[n1], nodes[n2]);
                for (size_t i = 0; i < gauss_points.size(); ++i) {
                    double ksi = gauss_points[i];
                    double weight = gauss_weights[i];

                    double N1 = 0.5 * (1 - ksi);
                    double N2 = 0.5 * (1 + ksi);

                    vector<double> N = { N1, N2 };

                    for (int a = 0; a < 2; ++a) {
                        for (int b = 0; b < 2; ++b) {
                            HBC_local[edge[a]][edge[b]] += alpha * N[a] * N[b] * edge_length * weight * 0.5;
                        }
                    }
                }
            }
        }
        return HBC_local;
    }



};

struct Grid {
    vector<Node> nodes;
    vector<Element> elements;

    Grid(const vector<Node>& nodes, const vector<Element>& elements)
        : nodes(nodes), elements(elements) {}

    void print() const {
        cout << endl << "\tNODES COORDINATES" << endl;
        for (int i = 0; i < nodes.size(); i++) {
            cout << i + 1 << ". ";
            if (i < 9) { cout << " "; }
            nodes[i].print();
        }

        cout << endl << "\tELEMENT NODES ID" << endl;
        for (int i = 0; i < elements.size(); i++) {
            cout << i + 1 << ". ";
            if (i < 9) { cout << " "; }
            elements[i].print();
        }
    }

    void printLocalHMatrices(double conductivity, int gauss_points_count) {
        cout << "\n\n\tLOCAL H MATRICES\n\n";
        for (const auto& element : elements) {
            auto H_local = element.calculateHMatrix(conductivity, nodes, gauss_points_count);
            cout << "\n\tLOCAL H MATRIX FOR ELEMENT: " << element.id << endl;
            for (const auto& row : H_local) {
                for (double value : row) {
                    cout << setw(10) << fixed << setprecision(4) << value << " ";
                }
                cout << endl;
            }
        }
    }

    void printLocalHBCMatrices(double conductivity, double alpha, int gauss_points_count) {
        cout << "\n\n\tLOCAL HBC MATRICES\n\n";
        for (const auto& element : elements) {
            auto H_local = element.calculateHMatrix(conductivity, nodes, gauss_points_count);
            auto HBC_local = element.calculateHBCMatrix(alpha, nodes, gauss_points_count);
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    H_local[i][j] += HBC_local[i][j];
                }
            }
            cout << "\n\tLOCAL HBC MATRIX FOR ELEMENT: " << element.id << endl;
            for (const auto& row : H_local) {
                for (double value : row) {
                    cout << setw(10) << fixed << setprecision(4) << value << " ";
                }
                cout << endl;
            }
        }
    }


};

struct Solve {
    vector<vector<double>> globalHMatrix;
    Solve(vector<vector<double>> calulateedGlobalHMatrix) : globalHMatrix(calulateedGlobalHMatrix) {};
};

struct CalculateGlobalHMatrix {

    vector<vector<double>> globalHBCMatrix;
    vector<vector<double>> globalHMatrix;


    void calculateBC(const Grid& grid, double conductivity, double alpha, int gauss_points_count) {
        int NodeCount = grid.nodes.size();
        globalHBCMatrix = vector<vector<double>>(NodeCount, vector<double>(NodeCount, 0.0));

        for (const auto& element : grid.elements) {
            auto H_local = element.calculateHMatrix(conductivity, grid.nodes, gauss_points_count);
            auto HBC_local = element.calculateHBCMatrix(alpha, grid.nodes, gauss_points_count);


            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    int global_i = element.node_ids[i] - 1;
                    int global_j = element.node_ids[j] - 1;
                    globalHBCMatrix[global_i][global_j] += H_local[i][j] + HBC_local[i][j];
                }
            }
        }
    }

    void calculate(const Grid& grid, double conductivity, int gauss_points_count) {
        int NodeCount = grid.nodes.size();
        globalHMatrix = vector<vector<double>>(NodeCount, vector<double>(NodeCount, 0.0));

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


    void printGlobalHBCMatrix() const {
        cout << "\n\tGLOBAL HBC MATRIX:" << endl;
        for (const auto& row : globalHBCMatrix) {
            for (double value : row) {
                cout << setw(10) << fixed << setprecision(4) << value << " ";
            }
            cout << endl;
        }
    }

    void printGlobalHMatrix() const {
        cout << "\n\tGLOBAL H MATRIX:" << endl;
        for (const auto& row : globalHMatrix) {
            for (double value : row) {
                cout << setw(10) << fixed << setprecision(4) << value << " ";
            }
            cout << endl;
        }
    }
};





int main() {
    //string grid_file = "../siatki/Test1_4_4.txt";
    string grid_file = "../siatki/Test2_4_4_MixGrid.txt";

    GlobalData global_data = GlobalData::readData(grid_file);
    global_data.print();

    vector<Node> nodes = Node::readNodes(grid_file);
    vector<Element> elements = Element::readElements(grid_file);

    Grid grid(nodes, elements);
    grid.print();

    int gauss_points_count = 2;
    grid.printLocalHMatrices(global_data.Conductivity, gauss_points_count);
    grid.printLocalHBCMatrices(global_data.Conductivity, global_data.Alfa, gauss_points_count);

    CalculateGlobalHMatrix calculationBC;
    CalculateGlobalHMatrix calculation;

    calculation.calculate(grid, global_data.Conductivity, gauss_points_count);
    calculation.printGlobalHMatrix();

    calculationBC.calculateBC(grid, global_data.Conductivity, global_data.Alfa, gauss_points_count);
    calculationBC.printGlobalHBCMatrix();

    //Solve solution(calculation.globalHBCMatrix);




    return 0;
}