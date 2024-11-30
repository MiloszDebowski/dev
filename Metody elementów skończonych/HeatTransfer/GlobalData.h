#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

struct GlobalData {
    double SimulationTime, SimulationStepTime, Conductivity, Alfa, Tot, InitialTemp, Density, SpecificHeat;
    int nN, nE;

    GlobalData(double simTime, double stepTime, double cond, double al, double to, double initTemp, double dens, double specHeat, int nodes, int elems);
    void print() const;

    static GlobalData readData(const string& grid_file);
};