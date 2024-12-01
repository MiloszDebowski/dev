#include "GlobalData.h"
#include "Node.h"
#include "Element.h"
#include "Grid.h"
#include "CalculateGlobalHMatrix.h"
#include "Solve.h"

int main() {

    string grid_file = "Test1_4_4.txt";
    //string grid_file = "Test1_4_4.txt";
    

    GlobalData global_data = GlobalData::readData(grid_file);
    global_data.print();

    auto nodes = Node::readNodes(grid_file);
    auto elements = Element::readElements(grid_file);

    Grid grid(nodes, elements);
    grid.print();

    int gauss_points_count = 2;
    grid.printLocalHMatricesAndSum(global_data.Conductivity, gauss_points_count);

    CalculateGlobalHMatrix calculation;
    calculation.calculate(grid, global_data.Conductivity, gauss_points_count);
    calculation.printGlobalHMatrix();

    Solve solution(calculation.globalHMatrix);

    return 0;
}
