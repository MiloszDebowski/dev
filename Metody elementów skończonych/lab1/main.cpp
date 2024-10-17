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
    int nN, nE;
    vector<Node> nodes;
    vector<Element> elements;

    Grid(const vector<Node>& nodes, const vector<Element>& elements)
        : nodes(nodes), elements(elements)
    {
        nN = nodes.size();
        nE = elements.size();
    }

    void print() const
    {
        int i = 1;
        cout << endl << "       NODES COORDINATES" << endl;
        for (const auto& nd : nodes)
        {
            cout << i << ". ";
            nd.print();
            i++;
        }
        i = 1;
        cout << endl << "       ELEMENT NODES ID" << endl;
        for (const auto& el : elements)
        {
            cout << i << ". ";
            el.print();
            i++;
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

    return 0;
}
