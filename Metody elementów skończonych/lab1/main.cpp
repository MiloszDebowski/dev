#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct GlobalData
{
    double SimulationTime, SimulationStepTime, Conductivity, Alfa, Tot, InitialTemp, Density, SpecificHeat;
    int nN, nE;

    GlobalData(double SimulationTime, double SimulationStepTime, double Conductivity, double Alfa, double Tot, double InitialTemp, double Density, double SpecificHeat, int nN, int nE) : SimulationTime(SimulationTime), SimulationStepTime(SimulationStepTime), Conductivity(Conductivity), Alfa(Alfa), Tot(Tot), InitialTemp(InitialTemp), Density(Density), SpecificHeat(SpecificHeat), nN(nN), nE(nE) {}

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

struct Element
{
    vector<int> nodeIDS;

    Element(const vector<int>& nodeIDS) : nodeIDS(nodeIDS) {}

    void print() const
    {
        cout << "{ ";
        for (int i = 0; i < nodeIDS.size(); ++i)
        {
            cout << nodeIDS[i];
            if (i != nodeIDS.size() - 1) cout << " ; ";
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
                    elements.push_back(Element({ n1, n2, n3, n4 }));
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

struct Gauss {
    double f1D(double x)
    {
        return 5 * x * x + 3 * x + 6;
    }

    double f2D(double x, double y)
    {
        return 5 * x * x * y * y + 3 * x * y + 6;
    }

    double gauss1D(int points)
    {
        double result = 0.0;
        if (points == 1)
        {
            double x[] = { 0.0 };
            double weights[] = { 2.0 };
            for (int i = 0; i < points; i++)
            {
                result += weights[i] * f1D(x[i]);
            }
        }
        else if (points == 2)
        {
            double x[] = { -1.0 / sqrt(3), 1.0 / sqrt(3) };
            double weights[] = { 1.0, 1.0 };
            for (int i = 0; i < points; i++)
            {
                result += weights[i] * f1D(x[i]);
            }
        }
        else if (points == 3)
        {
            double x[] = { -sqrt(3.0 / 5.0), 0.0, sqrt(3.0 / 5.0) };
            double weights[] = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
            for (int i = 0; i < points; i++)
            {
                result += weights[i] * f1D(x[i]);
            }
        }
        return result;
    }

    double gauss2D(int points)
    {
        double result = 0.0;
        if (points == 1)
        {
            double x[] = { 0.0 };
            double y[] = { 0.0 };
            double weights[] = { 4.0 };

            for (int i = 0; i < points; i++)
            {
                for (int j = 0; j < points; j++)
                {
                    result += weights[i] * f2D(x[i], y[j]);
                }
            }
        }
        else if (points == 2)
        {
            double x[] = { -1.0 / sqrt(3), 1.0 / sqrt(3) };
            double y[] = { -1.0 / sqrt(3), 1.0 / sqrt(3) };
            double weights[] = { 1.0, 1.0 };
            for (int i = 0; i < points; i++)
            {
                for (int j = 0; j < points; j++)
                {
                    result += weights[i] * weights[j] * f2D(x[i], y[j]);
                }
            }
        }
        else if (points == 3)
        {
            double x[] = { -sqrt(3.0 / 5.0), 0.0, sqrt(3.0 / 5.0) };
            double y[] = { -sqrt(3.0 / 5.0), 0.0, sqrt(3.0 / 5.0) };
            double weights[] = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };

            for (int i = 0; i < points; i++)
            {
                for (int j = 0; j < points; j++)
                {
                    result += weights[i] * weights[j] * f2D(x[i], y[j]);
                }
            }
        }

        return result;
    }


    void print()
    {
        cout << endl << "Gaussian integration in 1D - 1 point: " << gauss1D(1) << endl;
        cout << "Gaussian integration in 1D - 2 poins: " << gauss1D(2) << endl;
        cout << "Gaussian integration in 1D - 3 points: " << gauss1D(3) << endl;
        cout << "Gaussian integration in 2D - 1 point: " << gauss2D(1) << endl;
        cout << "Gaussian integration in 2D - 2 points: " << gauss2D(2) << endl;
        cout << "Gaussian integration in 2D - 3 points: " << gauss2D(3) << endl;

    }
};

struct pc {
    double ksi;
    double eta;

    pc(double ksi, double eta) : ksi(ksi), eta(eta) {}

    double N1ksi() { return (-0.25) * (1 - eta); }
    double N2ksi() { return (0.25) * (1 - eta); }
    double N3ksi() { return (0.25) * (1 + eta); }
    double N4ksi() { return (-0.25) * (1 + eta); }

    double N1eta() { return (-0.25) * (1 - ksi); }
    double N2eta() { return (-0.25) * (1 + ksi); }
    double N3eta() { return (0.25) * (1 + ksi); }
    double N4eta() { return (0.25) * (1 - ksi); }

    double calculateJacobian(const vector<double>& x, const vector<double>& y, double& detJ) {
        double dXdksi = N1ksi() * x[0] + N2ksi() * x[1] + N3ksi() * x[2] + N4ksi() * x[3];
        double dYdksi = N1ksi() * y[0] + N2ksi() * y[1] + N3ksi() * y[2] + N4ksi() * y[3];
        double dXdeta = N1eta() * x[0] + N2eta() * x[1] + N3eta() * x[2] + N4eta() * x[3];
        double dYdeta = N1eta() * y[0] + N2eta() * y[1] + N3eta() * y[2] + N4eta() * y[3];

        detJ = dXdksi * dYdeta - dYdksi * dXdeta;
        cout << endl << detJ << endl;
        return detJ;
    }

    vector<vector<double>> calculate_dNdx_dNdy(double detJ, const vector<double>& x, const vector<double>& y) {
        double dXdksi = N1ksi() * x[0] + N2ksi() * x[1] + N3ksi() * x[2] + N4ksi() * x[3];
        double dYdksi = N1ksi() * y[0] + N2ksi() * y[1] + N3ksi() * y[2] + N4ksi() * y[3];
        double dXdeta = N1eta() * x[0] + N2eta() * x[1] + N3eta() * x[2] + N4eta() * x[3];
        double dYdeta = N1eta() * y[0] + N2eta() * y[1] + N3eta() * y[2] + N4eta() * y[3];

        vector<vector<double>> dNdx_dNdy(4, vector<double>(2));
        dNdx_dNdy[0][0] = (1 / detJ) * (dYdeta * N1ksi() - dYdksi * N1eta());
        dNdx_dNdy[0][1] = (1 / detJ) * (-dXdeta * N1ksi() + dXdksi * N1eta());

        dNdx_dNdy[1][0] = (1 / detJ) * (dYdeta * N2ksi() - dYdksi * N2eta());
        dNdx_dNdy[1][1] = (1 / detJ) * (-dXdeta * N2ksi() + dXdksi * N2eta());

        dNdx_dNdy[2][0] = (1 / detJ) * (dYdeta * N3ksi() - dYdksi * N3eta());
        dNdx_dNdy[2][1] = (1 / detJ) * (-dXdeta * N3ksi() + dXdksi * N3eta());

        dNdx_dNdy[3][0] = (1 / detJ) * (dYdeta * N4ksi() - dYdksi * N4eta());
        dNdx_dNdy[3][1] = (1 / detJ) * (-dXdeta * N4ksi() + dXdksi * N4eta());

        return dNdx_dNdy;
    }

    void calculate_H_matrix(double k, double detJ, vector<vector<double>>& H) {
        vector<vector<double>> dNdx_dNdy = calculate_dNdx_dNdy(detJ, { 0, 0.025, 0.025, 0 }, { 0, 0, 0.025, 0.025 });

        H.assign(4, vector<double>(4, 0));
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                H[i][j] = k * detJ * (dNdx_dNdy[i][0] * dNdx_dNdy[j][0] + dNdx_dNdy[i][1] * dNdx_dNdy[j][1]);
            }
        }
    }

    void print_H_matrix(const vector<vector<double>>& H) {
        cout << fixed << setprecision(3);
        for (const auto& row : H) {
            for (const auto& value : row) {
                cout << setw(8) << value << " ";
            }
            cout << endl;
        }
    }
};


int main()
{
    string grid_file = "Test1_4_4.txt";

    GlobalData global_data = GlobalData::readData(grid_file);
    global_data.print();

    vector<Node> nodes = Node::readNodes(grid_file);
    vector<Element> elements = Element::readElements(grid_file);

    Grid grid(nodes, elements);
    grid.print();

    Gauss calka;
    calka.print();


    double k = 30;

    vector<pc> integration_points = {
        pc(-1.0 / sqrt(3), -1.0 / sqrt(3)),
        pc(1.0 / sqrt(3), -1.0 / sqrt(3)),
        pc(1.0 / sqrt(3), 1.0 / sqrt(3)),
        pc(-1.0 / sqrt(3), 1.0 / sqrt(3))
    };



    double detJ;
    vector<vector<double>> H(4, vector<double>(4, 0));
    vector<vector<double>> final_H(4, vector<double>(4, 0));

    for (int i = 0; i < integration_points.size(); ++i) {
        detJ = integration_points[i].calculateJacobian({ 0, 0.025, 0.025, 0 }, { 0, 0, 0.025, 0.025 }, detJ);

        integration_points[i].calculate_H_matrix(k, detJ, H);
        cout << "Macierz Hpc" << (i + 1) << ":" << endl;
        integration_points[i].print_H_matrix(H);
        cout << endl;

        double w1 = 1.0, w2 = 1.0;
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                final_H[j][k] += H[j][k] * w1 * w2;
            }
        }
    }

    cout << "Macierz H:" << endl;
    integration_points[0].print_H_matrix(final_H);

    return 0;



    return 0;
}