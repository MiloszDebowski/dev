#include "GlobalData.h"

GlobalData::GlobalData(double simTime, double stepTime, double cond, double al, double to, double initTemp, double dens, double specHeat, int nodes, int elems)
    : SimulationTime(simTime), SimulationStepTime(stepTime), Conductivity(cond), Alfa(al), Tot(to), InitialTemp(initTemp), Density(dens), SpecificHeat(specHeat), nN(nodes), nE(elems) {}

void GlobalData::print() const {
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

GlobalData GlobalData::readData(const string& grid_file) {
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
