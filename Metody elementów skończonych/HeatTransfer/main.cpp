#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<vector>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>

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

vector<double> assignGaussPoints(int n) {
    vector<double> gaussPoints;
    if (n == 2) {
        gaussPoints = { 
            -1.0 / sqrt(3),
            1.0 / sqrt(3)
        };
    }
    else if (n == 3) {
        gaussPoints = { 
            -sqrt(3.0 / 5.0), 0.0,
            sqrt(3.0 / 5.0)
        };
    }
    else if (n == 4) {
        gaussPoints = {
            -sqrt((3.0 + 2.0 * sqrt(6.0 / 5.0)) / 7.0),
            -sqrt((3.0 - 2.0 * sqrt(6.0 / 5.0)) / 7.0),
             sqrt((3.0 - 2.0 * sqrt(6.0 / 5.0)) / 7.0),
             sqrt((3.0 + 2.0 * sqrt(6.0 / 5.0)) / 7.0)
        };
    }
    else {
        throw invalid_argument("Unsupported number of Gauss points.");
    }
    return gaussPoints;
}

vector<double> assignGaussWeights(int n) {
    vector<double> gaussWeights;
    if (n == 2) {
        gaussWeights = {
            1.0,
            1.0
        };
    }
    else if (n == 3) {
        gaussWeights = {
            5.0 / 9.0,
            8.0 / 9.0,
            5.0 / 9.0
        };
    }
    else if (n == 4) {
        gaussWeights = {
            (18.0 - sqrt(30.0)) / 36.0,
            (18.0 + sqrt(30.0)) / 36.0,
            (18.0 + sqrt(30.0)) / 36.0,
            (18.0 - sqrt(30.0)) / 36.0
        };
    }
    else {
        throw invalid_argument("Unsupported number of Gauss points.");
    }
    return gaussWeights;
}


double calculateEdgeLength(const Node& n1, const Node& n2) {
    return sqrt(pow(n2.x - n1.x, 2) + pow(n2.y - n1.y, 2));
}

struct Element {
    int id;
    vector<int> node_ids;
    vector<vector<double>> H_local;
    vector<vector<double>> HBC_local;
    vector<double> P_local;
    vector<vector<double>> C_local;

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

    void calculateHMatrix(double conductivity, const vector<Node>& nodes, int gauss_points_count) {
        vector<double> gauss_points, gauss_weights;
        gauss_points = assignGaussPoints(gauss_points_count);
        gauss_weights = assignGaussWeights(gauss_points_count);

        H_local.assign(4, vector<double>(4, 0.0));

        for (int i = 0; i < gauss_points_count; ++i) {
            for (int j = 0; j < gauss_points_count; ++j) {
                double xi = gauss_points[i];
                double eta = gauss_points[j];
                double weight = gauss_weights[i] * gauss_weights[j];

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
                        H_local[i][j] += conductivity * (dN_dx[i] * dN_dx[j] + dN_dy[i] * dN_dy[j]) * detJ * weight;
                    }
                }
            }
        }
    }

    void calculateCMatrix(double density, double specificHeat, const vector<Node>& nodes, int gauss_points_count) {
        vector<double> gauss_points, gauss_weights;
        gauss_points = assignGaussPoints(gauss_points_count);
        gauss_weights = assignGaussWeights(gauss_points_count);

        C_local.assign(4, vector<double>(4, 0.0));

        for (int i = 0; i < gauss_points_count; ++i) {
            for (int j = 0; j < gauss_points_count; ++j) {
                double xi = gauss_points[i];
                double eta = gauss_points[j];
                double weight = gauss_weights[i] * gauss_weights[j];

                vector<double> dN_dxi = { -0.25 * (1 - eta), 0.25 * (1 - eta), 0.25 * (1 + eta), -0.25 * (1 + eta) };
                vector<double> dN_deta = { -0.25 * (1 - xi), -0.25 * (1 + xi), 0.25 * (1 + xi), 0.25 * (1 - xi) };



                vector<double> N = {
                0.25 * (1 - xi) * (1 - eta),
                0.25 * (1 + xi) * (1 - eta),
                0.25 * (1 + xi) * (1 + eta),
                0.25 * (1 - xi) * (1 + eta)
                };

                double J11 = 0, J12 = 0, J21 = 0, J22 = 0;
                for (int i = 0; i < 4; ++i) {
                    J11 += dN_dxi[i] * nodes[node_ids[i] - 1].x;
                    J12 += dN_dxi[i] * nodes[node_ids[i] - 1].y;
                    J21 += dN_deta[i] * nodes[node_ids[i] - 1].x;
                    J22 += dN_deta[i] * nodes[node_ids[i] - 1].y;
                }
                double detJ = J11 * J22 - J12 * J21;

                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; j++) {
                        C_local[i][j] += density * specificHeat * N[i] * N[j] * detJ * weight;
                    }
                }
            }
        }
    }


    void calculateHBCMatrix(double tot, double alpha, const vector<Node>& nodes, int gauss_points_count) {
        vector<double> gauss_points, gauss_weights;
        gauss_points = assignGaussPoints(gauss_points_count);
        gauss_weights = assignGaussWeights(gauss_points_count);

        HBC_local.assign(4, vector<double>(4, 0.0));
        P_local.assign(4, 0.0);
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
                        P_local[edge[a]] += alpha * tot * N[a] * edge_length * weight * 0.5;
                        for (int b = 0; b < 2; ++b) {
                            HBC_local[edge[a]][edge[b]] += alpha * N[a] * N[b] * edge_length * weight * 0.5;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                HBC_local[i][j] += H_local[i][j];
            }
        }

    }

    void printHLocal() {
        for (const auto& row : H_local) {
            for (double value : row) {
                cout << setw(10) << fixed << setprecision(4) << value << " ";
            }
            cout << endl;
        }
    }

    void printHBCLocal() {
        for (const auto& row : HBC_local) {
            for (double value : row) {
                cout << setw(10) << fixed << setprecision(4) << value << " ";
            }
            cout << endl;
        }
        cout << "BC: ";
        for (const auto& value : P_local) {
            cout << value << " ";
        }
    }

    void printCLocal() {
        for (const auto& row : C_local) {
            for (double value : row) {
                cout << setw(10) << fixed << setprecision(4) << value << " ";
            }
            cout << endl;
        }
    }
};

struct Grid {
    vector<Node> nodes;
    vector<Element> elements;
    vector<vector<double>> HBC_global;
    vector<vector<double>> H_global;
    vector<double> P_global;
    vector<vector<double>> C_global;

    Grid(const vector<Node>& nodes, const vector<Element>& elements)
        : nodes(nodes), elements(elements) {}

    void calculateHMatrix() {
        int NodeCount = nodes.size();
        H_global.assign(NodeCount, vector<double>(NodeCount, 0.0));
        for (const auto& element : elements) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    int global_i = element.node_ids[i] - 1;
                    int global_j = element.node_ids[j] - 1;
                    H_global[global_i][global_j] += element.H_local[i][j];
                }
            }
        }
    }

    void calculateHBCMatrix() {
        int NodeCount = nodes.size();
        HBC_global.assign(NodeCount, vector<double>(NodeCount, 0.0));
        P_global.assign(NodeCount, 0.0);
        for (const auto& element : elements) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    int global_i = element.node_ids[i] - 1;
                    int global_j = element.node_ids[j] - 1;
                    HBC_global[global_i][global_j] += element.HBC_local[i][j];

                }
            }
            for (int i = 0; i < 4; i++) {
                int global_i = element.node_ids[i] - 1;
                P_global[global_i] += element.P_local[i];
            }
        }
    }

    void calculateCMatrix() {
        int NodeCount = nodes.size();
        C_global.assign(NodeCount, vector<double>(NodeCount, 0.0));
        for (const auto& element : elements) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    int global_i = element.node_ids[i] - 1;
                    int global_j = element.node_ids[j] - 1;
                    C_global[global_i][global_j] += element.C_local[i][j];
                }
            }
        }
    }

    void printGlobalHMatrix() const {
        cout << "\n\tGLOBAL H MATRIX:" << endl;
        for (const auto& row : H_global) {
            for (double value : row) {
                cout << setw(10) << fixed << setprecision(4) << value << " ";
            }
            cout << endl;
        }
    }

    void printGlobalCMatrix() const {
        cout << "\n\t GLOBAL C MATRIX:" << endl;
        for (const auto& row : C_global) {
            for (double value : row) {
                cout << setw(10) << fixed << setprecision(4) << value << " ";
            }
            cout << endl;
        }
    }

    void printGlobalHBCMatrix() const {
        cout << "\n\tGLOBAL HBC MATRIX:" << endl;
        for (const auto& row : HBC_global) {
            for (double value : row) {
                cout << setw(10) << fixed << setprecision(4) << value << " ";
            }
            cout << endl;
        }
        cout << "BC: ";

        for (const auto& value : P_global) {
            cout << value << " ";
        }
    }

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
        for (auto& element : elements) {
            cout << "\n\tLOCAL H MATRIX FOR ELEMENT: " << element.id << endl;
            element.calculateHMatrix(conductivity, nodes, gauss_points_count);
            element.printHLocal();
            cout << endl;
        }
    }

    void printLocalHBCMatrices(double tot, double alpha, int gauss_points_count) {
        cout << "\n\n\tLOCAL HBC MATRICES\n\n";
        for (auto& element : elements) {
            cout << "\n\tLOCAL HBC MATRIX FOR ELEMENT: " << element.id << endl;
            element.calculateHBCMatrix(tot, alpha, nodes, gauss_points_count);
            element.printHBCLocal();
            cout << endl;
        }
    }

    void printLocalCMatrices(double density, double specificHeat, int gauss_points_count) {
        cout << "\n\n\tLOCAL C MATRICES\n\n";
        for (auto& element : elements) {
            cout << "\n\tLOCAL C MATRIX FOR ELEMENT: " << element.id << endl;
            element.calculateCMatrix(density, specificHeat, nodes, gauss_points_count);
            element.printCLocal();
            cout << endl;
        }
    }
};

struct Solver {
    vector<double> TempVector;

    void solveT(Grid& grid) {
        int n = grid.HBC_global.size();

        if (n == 0 || grid.HBC_global[0].size() != n) {
            throw invalid_argument("HBC_global is not a square matrix.");
        }

        TempVector.assign(n, 0.0);

        vector<vector<double>> H = grid.HBC_global;

        //macierz jednostkowa
        vector<vector<double>> I(n, vector<double>(n, 0.0));
        for (int i = 0; i < n; ++i) {
            I[i][i] = 1.0;
        }

        //eliminacja gaussa
        for (int i = 0; i < n; ++i) {
            //jedynki na przekatnej
            double diag = H[i][i];
            if (diag == 0.0) {
                throw invalid_argument("Matrix cannot be inverted.");
            }
            for (int j = 0; j < n; ++j) {
                H[i][j] /= diag;
                I[i][j] /= diag;
            }

            //zero pod przekatna
            for (int k = 0; k < n; ++k) {
                if (k == i) continue;
                double factor = H[k][i];
                for (int j = 0; j < n; ++j) {
                    H[k][j] -= factor * H[i][j];
                    I[k][j] -= factor * I[i][j];
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                TempVector[i] += I[i][j] * grid.P_global[j];
            }
        }



    }

    void print() {
        cout << "\n\n[T] =  [";
        for (size_t i = 0; i < TempVector.size(); ++i) {
            cout << fixed << setprecision(4) << TempVector[i];
            if (i != TempVector.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }


};

struct Simulation {
    Grid& grid;
    GlobalData& globalData;

    Simulation(Grid& grid, GlobalData& globalData) : grid(grid), globalData(globalData) {}

    void run() {
        int numNodes = grid.nodes.size();
        vector<double> t_prev(numNodes, globalData.InitialTemp);
        vector<double> t_curr(numNodes);

        vector<double> maxTemperatures; // Wektor maksymalnych temperatur
        vector<double> minTemperatures; // Wektor minimalnych temperatur

        double simulationTime = globalData.SimulationTime;
        double timeStep = globalData.SimulationStepTime;

        cout << endl << "\tSIMULATION START" << endl << endl;
        cout << "SIMULATION DURATION: " << simulationTime << "s" << endl;
        cout << "SIMULATION TIME STEP : "<<timeStep<<"s"<<endl<<endl;

        for (double currentTime = 0.0; currentTime < simulationTime; currentTime += timeStep) {
            cout << "SIMULATION TIME: " << currentTime << " s" << endl;

            // Oblicz H + C/dt
            vector<vector<double>> H_total = grid.HBC_global;
            for (int i = 0; i < numNodes; ++i) {
                for (int j = 0; j < numNodes; ++j) {
                    H_total[i][j] += grid.C_global[i][j] / timeStep;
                }
            }

            // Oblicz P + (C/dt)*T_prev
            vector<double> P_total = grid.P_global;
            for (int i = 0; i < numNodes; ++i) {
                for (int j = 0; j < numNodes; ++j) {
                    P_total[i] += grid.C_global[i][j] / timeStep * t_prev[j];
                }
            }

            // Rozwiąż równanie H_total * t_curr = P_total
            t_curr = solveSystem(H_total, P_total);

            // Wypisz temperatury w każdym punkcie
            for (int i = 0; i < numNodes; ++i) {
                cout << setw(10) << "T[" << i << "] = " << t_curr[i];
                if ((i + 1) % 4 == 0) { cout << endl; }
            }
            cout << endl;

            // Dodaj maksymalną i minimalną temperaturę do odpowiednich wektorów
            double maxTemp = *max_element(t_curr.begin(), t_curr.end());
            double minTemp = *min_element(t_curr.begin(), t_curr.end());
            maxTemperatures.push_back(maxTemp);
            minTemperatures.push_back(minTemp);

            cout << "Max temperature this step: " << maxTemp << endl;
            cout << "Min temperature this step: " << minTemp << endl << endl;;

            // Przejdź do kolejnego kroku czasowego
            t_prev = t_curr;
        }

        cout << "\n\tEND OF SIMULATION\n" << endl;

        // Wypisz wektory maksymalnych i minimalnych temperatur
        cout << "\nMax Temperatures during simulation:" << endl;
        for (double temp : maxTemperatures) {
            cout << temp << " ";
        }
        cout << "\n\nMin Temperatures during simulation:" << endl;
        for (double temp : minTemperatures) {
            cout << temp << " ";
        }
        cout << endl;
    }

    vector<double> solveSystem(const vector<vector<double>>& A, const vector<double>& b) {
        // Prosty solver Gaussa – zakładamy, że A jest kwadratowa i pełnoranga
        int n = b.size();
        vector<vector<double>> augmentedMatrix(n, vector<double>(n + 1));

        // Tworzenie macierzy rozszerzonej
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                augmentedMatrix[i][j] = A[i][j];
            }
            augmentedMatrix[i][n] = b[i];
        }

        // Eliminacja Gaussa
        for (int i = 0; i < n; ++i) {
            // Normalizacja wiersza
            double pivot = augmentedMatrix[i][i];
            for (int j = 0; j <= n; ++j) {
                augmentedMatrix[i][j] /= pivot;
            }

            // Odejmowanie wierszy
            for (int k = 0; k < n; ++k) {
                if (k != i) {
                    double factor = augmentedMatrix[k][i];
                    for (int j = 0; j <= n; ++j) {
                        augmentedMatrix[k][j] -= factor * augmentedMatrix[i][j];
                    }
                }
            }
        }

        // Wyodrębnienie rozwiązań
        vector<double> solution(n);
        for (int i = 0; i < n; ++i) {
            solution[i] = augmentedMatrix[i][n];
        }
        return solution;
    }
};


int main(void) {

    string grid_file = "../siatki/Test1_4_4.txt";
    //string grid_file = "../siatki/Test2_4_4_MixGrid.txt";

    GlobalData global_data = GlobalData::readData(grid_file);
    global_data.print();

    vector<Node> nodes = Node::readNodes(grid_file);
    vector<Element> elements = Element::readElements(grid_file);

    Grid grid(nodes, elements);
    grid.print();

    int gauss_points_count = 2;
    grid.printLocalHMatrices(global_data.Conductivity, gauss_points_count);
    grid.printLocalHBCMatrices(global_data.Tot, global_data.Alfa, gauss_points_count);

    grid.calculateHMatrix();
    grid.calculateHBCMatrix();
    grid.printGlobalHMatrix();
    grid.printGlobalHBCMatrix();

    Solver solution;
    solution.solveT(grid);
    solution.print();

    grid.printLocalCMatrices(global_data.Density, global_data.SpecificHeat, gauss_points_count);
    grid.calculateCMatrix();
    grid.printGlobalCMatrix();




    Simulation simulation(grid, global_data);

    simulation.run();

    return 0;
}