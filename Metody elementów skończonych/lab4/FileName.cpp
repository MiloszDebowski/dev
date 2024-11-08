#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<array>
#include <iomanip>
using namespace std;

struct GlobalData {
    double SimulationTime, SimulationStepTime, Conductivity, Alfa, Tot, InitialTemp, Density, SpecificHeat;
    int nN, nE;

    GlobalData(double simTime, double stepTime, double cond, double al, double to, double initTemp, double dens, double specHeat, int nodes, int elems)
        : SimulationTime(simTime), SimulationStepTime(stepTime), Conductivity(cond), Alfa(al), Tot(to), InitialTemp(initTemp), Density(dens), SpecificHeat(specHeat), nN(nodes), nE(elems) {}

    void print()
    {
        cout << "       GLOBAL DATA" << endl;
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

    static GlobalData readData(const string& grid_file)
    {
        ifstream file(grid_file);
        string line;
        double SimulationTime = 0, SimulationStepTime = 0, Conductivity = 0, Alfa = 0, Tot = 0, InitialTemp = 0, Density = 0, SpecificHeat = 0;
        int Nodes = 0, Elements = 0;

        while (getline(file, line))
        {
            istringstream iss(line);
            string key1, key2;
            double value;

            if (iss >> key1 >> value)
            {
                if (key1 == "SimulationTime") SimulationTime = value;
                else if (key1 == "SimulationStepTime") SimulationStepTime = value;
                else if (key1 == "Conductivity") Conductivity = value;
                else if (key1 == "Alfa") Alfa = value;
                else if (key1 == "Tot") Tot = value;
                else if (key1 == "InitialTemp") InitialTemp = value;
                else if (key1 == "Density") Density = value;
                else if (key1 == "SpecificHeat") SpecificHeat = value;
            }

            iss.clear();
            iss.str(line);

            if (iss >> key1 >> key2 >> value)
            {
                if (key1 == "Nodes" && key2 == "number")
                {
                    Nodes = static_cast<int>(value);
                }
                else if (key1 == "Elements" && key2 == "number")
                {
                    Elements = static_cast<int>(value);
                }
            }
        }

        return GlobalData(SimulationTime, SimulationStepTime, Conductivity, Alfa, Tot, InitialTemp, Density, SpecificHeat, Nodes, Elements);
    }

};

struct Node {
    
    double x, y;

    Node(double x, double y) : x(x), y(y) {}

    void print() const
    {
        cout << "( " << x << " ; " << y << " )\n";
    }

    static vector<Node> readNodes(const string& grid_file)
    {
        ifstream file(grid_file);
        string line;
        vector<Node> nodes;
        bool node_section = false;

        while (getline(file, line))
        {
            if (line.find("*Node") != string::npos)
            {
                node_section = true;
                continue;
            }

            if (line.find("*Element") != string::npos)
            {
                break;
            }

            if (node_section)
            {
                istringstream iss(line);
                int node_id;
                double x, y;
                char comma;

                if (iss >> node_id >> comma >> x >> comma >> y)
                {
                    nodes.push_back(Node(x, y));
                }
            }
        }
        return nodes;
    }
};

struct Element {
    int element_id;
    vector<int> node_ids;
    int npc;

    Element(int id, vector<int> nodes, int np) : element_id(id), node_ids(nodes), npc(np) {}

    void print() const
    {
        cout << "{ ";
        for (int i = 0; i < node_ids.size(); ++i)
        {
            cout << node_ids[i];
            if (i != node_ids.size() - 1) cout << " ; ";
        }
        cout << " }" << endl;
    }


    static vector<Element> readElements(const string& grid_file)
    {
        ifstream file(grid_file);
        string line;
        vector<Element> elements;
        bool element_section = false;

        while (getline(file, line))
        {
            if (line.find("*Element") != string::npos)
            {
                element_section = true;
                continue;
            }

            if (line.find("*BC") != string::npos)
            {
                break;
            }

            if (element_section)
            {
                istringstream iss(line);
                int element_id, n1, n2, n3, n4;
                char comma;
                if (iss >> element_id >> comma >> n1 >> comma >> n2 >> comma >> n3 >> comma >> n4)
                {
                    elements.push_back(Element(element_id,{ n1, n2, n3, n4 },4));
                }
            }
        }
        return elements;
    }
};


struct Grid
{
    vector<Node> nodes;
    vector<Element> elements;

    Grid(const vector<Node>& nodes, const vector<Element>& elements)
        : nodes(nodes), elements(elements) {}

    void print() const
    {

        cout << endl << "       NODES COORDINATES" << endl;
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << i + 1 << ". ";
            nodes[i].print();
        }

        cout << endl << "       ELEMENT NODES ID" << endl;
        for (int i = 0; i < elements.size(); i++)
        {
            cout << i + 1 << ". ";
            elements[i].print();
        }
    }
};





struct ElemUniv {
    int npc;
    vector<pair<double, double>> pc_points;
    vector<vector<double>> shape_functions;

    ElemUniv(int np, const vector<pair<double, double>>& points) : npc(np), pc_points(points) {
        compute_shape_functions();
    }

    void compute_shape_functions() {
        shape_functions.clear();
        for (size_t i = 0; i < pc_points.size(); ++i) {
            double ksi = pc_points[i].first;
            double eta = pc_points[i].second;
            vector<double> N = {
                0.25 * (1 - ksi) * (1 - eta),
                0.25 * (1 + ksi) * (1 - eta),
                0.25 * (1 + ksi) * (1 + eta),
                0.25 * (1 - ksi) * (1 + eta)
            };
            shape_functions.push_back(N);
        }
    }

    void get_shape_function_derivatives(double ksi, double eta, vector<double>& dN_dksi, vector<double>& dN_deta) const {
        dN_dksi = { -0.25 * (1 - eta), 0.25 * (1 - eta), 0.25 * (1 + eta), -0.25 * (1 + eta) };
        dN_deta = { -0.25 * (1 - ksi), -0.25 * (1 + ksi), 0.25 * (1 + ksi), 0.25 * (1 - ksi) };
    }
};

struct Jakobian {
    double J[2][2];
    double detJ;

    Jakobian() : detJ(0.0) {
        J[0][0] = J[0][1] = J[1][0] = J[1][1] = 0.0;
    }

    void compute_jacobian(const Element& element, const vector<Node>& nodes, double ksi, double eta) {
        vector<double> x, y;
        for (int node_id : element.node_ids) {
            x.push_back(nodes[node_id - 1].x);
            y.push_back(nodes[node_id - 1].y);
        }

        ElemUniv elem_univ(4, {{ksi, eta}});
        vector<double> dN_dksi, dN_deta;
        elem_univ.get_shape_function_derivatives(ksi, eta, dN_dksi, dN_deta);

        J[0][0] = dN_dksi[0] * x[0] + dN_dksi[1] * x[1] + dN_dksi[2] * x[2] + dN_dksi[3] * x[3];
        J[0][1] = dN_dksi[0] * y[0] + dN_dksi[1] * y[1] + dN_dksi[2] * y[2] + dN_dksi[3] * y[3];
        J[1][0] = dN_deta[0] * x[0] + dN_deta[1] * x[1] + dN_deta[2] * x[2] + dN_deta[3] * x[3];
        J[1][1] = dN_deta[0] * y[0] + dN_deta[1] * y[1] + dN_deta[2] * y[2] + dN_deta[3] * y[3];

        detJ = J[0][0] * J[1][1] - J[0][1] * J[1][0];
        //cout << detJ;
    }
};

struct HMatrixCalculator {
    double k;

    HMatrixCalculator(double thermalConductivity) : k(thermalConductivity) {}

    void calculate_H_matrix(const Element& element, const vector<Node>& nodes, const vector<pair<double, double>>& pc_points, const vector<double>& weights) {
        vector<vector<double>> H(4, vector<double>(4, 0.0));

        if (pc_points.size() != weights.size()) {
            cerr << "zla ilosc wag lub pc" << endl;
            return;
        }

        for (size_t i = 0; i < pc_points.size(); ++i) {
            double ksi = pc_points[i].first;
            double eta = pc_points[i].second;

            Jakobian jakobian;
            jakobian.compute_jacobian(element, nodes, ksi, eta);

            vector<double> dN_dksi, dN_deta;
            ElemUniv elem_univ(4, { {ksi, eta} });
            elem_univ.get_shape_function_derivatives(ksi, eta, dN_dksi, dN_deta);

            vector<double> dN_dx(4), dN_dy(4);
            double inv_detJ = 1.0 / jakobian.detJ;

            for (int j = 0; j < 4; ++j) {
                dN_dx[j] = inv_detJ * (jakobian.J[1][1] * dN_dksi[j] - jakobian.J[0][1] * dN_deta[j]);
                dN_dy[j] = inv_detJ * (-jakobian.J[1][0] * dN_dksi[j] + jakobian.J[0][0] * dN_deta[j]);
            }

            double weight = weights[i] * jakobian.detJ;

            
            vector<vector<double>> H_local(4, vector<double>(4, 0.0));

            for (int m = 0; m < 4; ++m) {
                for (int n = 0; n < 4; ++n) {
                    H_local[m][n] = weight * k * (dN_dx[m] * dN_dx[n] + dN_dy[m] * dN_dy[n]);
                    H[m][n] += H_local[m][n];
                }
            }

            
            cout << "Macierz w punkcie (" << ksi << ", " << eta << "):" << endl;
            for (const auto& row : H_local) {
                for (double val : row) {
                    cout << setw(10) << val << " ";
                }
                cout << endl;
            }
            cout << endl;
        }

        cout << "Macierz H:" << endl;
        for (const auto& row : H) {
            for (double val : row) {
                cout << setw(10) << val << " ";
            }
            cout << endl;
        }
    }



};





int main() {

    /*string grid_file = "Test1_4_4.txt";

    GlobalData global_data = GlobalData::readData(grid_file);
    global_data.print();

    vector<Node> nodes = Node::readNodes(grid_file);
    vector<Element> elements = Element::readElements(grid_file);

    Grid grid(nodes, elements);
    grid.print();*/



    vector<Node> nodes1 = {
        Node(0.01, -0.01),
        Node(0.025, 0.0),
        Node(0.025, 0.025),
        Node(0.0, 0.025)
    };
    vector<Element> elements1 = {
        Element(1, {1, 2, 3, 4}, 4)
    };
    vector<pair<double, double>> pc_points1 = {
    {-sqrt(1.0 / 3.0), -sqrt(1.0 / 3.0)},
    {sqrt(1.0 / 3.0), -sqrt(1.0 / 3.0)},
    {-sqrt(1.0 / 3.0), sqrt(1.0 / 3.0)},
    {sqrt(1.0 / 3.0), sqrt(1.0 / 3.0)}
    };

    vector<double> weights1 = { 1.0,1.0,1.0,1.0 };
    HMatrixCalculator h_calculator1(30.0);
    for (const auto& element : elements1) {
        h_calculator1.calculate_H_matrix(element, nodes1, pc_points1, weights1);
    }




    vector<Node> nodes2 = {
        Node(0.0, 0.0),
        Node(0.025, 0.0),
        Node(0.025, 0.025),
        Node(0.0, 0.025)
    };
    vector<Element> elements2 = {
        Element(1, {1, 2, 3, 4}, 4)
    };
    vector<pair<double, double>> pc_points2 = {
    {-sqrt(1.0 / 3.0), -sqrt(1.0 / 3.0)},
    {sqrt(1.0 / 3.0), -sqrt(1.0 / 3.0)},
    {-sqrt(1.0 / 3.0), sqrt(1.0 / 3.0)},
    {sqrt(1.0 / 3.0), sqrt(1.0 / 3.0)}
    };

    vector<double> weights2 = {1.0,1.0,1.0,1.0};
    HMatrixCalculator h_calculator2(30.0);
    for (const auto& element : elements2) {
        h_calculator2.calculate_H_matrix(element, nodes2, pc_points2, weights2);
    }


    vector<Node> nodes3 = {
    Node(0.0, 0.0),
    Node(0.025, 0.0),
    Node(0.025, 0.025),
    Node(0.0, 0.025)
    };
    vector<Element> elements3 = {
        Element(1, {1, 2, 3, 4}, 9)
    };
    vector<pair<double, double>> pc_points3 = {
     {-sqrt(3.0 / 5.0), -sqrt(3.0 / 5.0)},  
     {0, -sqrt(3.0 / 5.0)},                  
     {sqrt(3.0 / 5.0), -sqrt(3.0 / 5.0)},   
     {-sqrt(3.0 / 5.0), 0},                  
     {0, 0},                                  
     {sqrt(3.0 / 5.0), 0},                   
     {-sqrt(3.0 / 5.0), sqrt(3.0 / 5.0)},    
     {0, sqrt(3.0 / 5.0)},                   
     {sqrt(3.0 / 5.0), sqrt(3.0 / 5.0)}     
    };

    vector<double> weights3 = {
    25.0 / 81.0, 40.0 / 81.0, 25.0 / 81.0,
    40.0 / 81.0, 64.0 / 81.0, 40.0 / 81.0,
    25.0 / 81.0, 40.0 / 81.0, 25.0 / 81.0
    };




    HMatrixCalculator h_calculator3(30.0);
    for (const auto& element : elements3) {
        h_calculator3.calculate_H_matrix(element, nodes3, pc_points3, weights3);
    }

    return 0;
}