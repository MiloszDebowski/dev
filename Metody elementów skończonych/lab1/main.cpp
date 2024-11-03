#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
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
};

struct Node {
    double x, y;

    Node(double x, double y) : x(x), y(y) {}

    void print() const
    {
        cout << "( " << x << " ; " << y << " )\n";
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

    void print_dN_dksi_deta() {
        cout << "dN/dksi: " << N1ksi() << " " << N2ksi() << " " << N3ksi() << " " << N4ksi() << endl;
        cout << "dN/deta: " << N1eta() << " " << N2eta() << " " << N3eta() << " " << N4eta() << endl;
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

int main() {
    double k = 30.0;
    vector<pc> integration_points = { pc(-1.0 / sqrt(3), -1.0 / sqrt(3)), pc(1.0 / sqrt(3), -1.0 / sqrt(3)), pc(1.0 / sqrt(3), 1.0 / sqrt(3)), pc(-1.0 / sqrt(3), 1.0 / sqrt(3)) };

    for (int i = 0; i < integration_points.size(); i++) {
        double current_detJ;
        current_detJ = integration_points[i].calculateJacobian({ 0, 0.025, 0.025, 0 }, { 0, 0, 0.025, 0.025 }, current_detJ);

        cout << "Integration point " << i + 1 << ":" << endl;
        cout << "detJ: " << current_detJ << endl;

        integration_points[i].print_dN_dksi_deta();

        vector<vector<double>> H;
        integration_points[i].calculate_H_matrix(k, current_detJ, H);

        cout << "H matrix:" << endl;
        integration_points[i].print_H_matrix(H);
        cout << endl;
    }

    return 0;
}
