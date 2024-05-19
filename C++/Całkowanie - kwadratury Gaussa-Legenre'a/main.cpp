#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

double legendre_integration(double (*func)(double), double a, double b, int n) {
    vector<double> nodes;
    vector<double> weights;

    if (n == 2) {
        double node1 = (-(pow(3.0, (1.0 / 2.0))) / 3.0);
        double node2 = ((pow(3.0, (1.0 / 2.0))) / 3.0);
        nodes = { node1,  node2 };
        weights = { 1, 1 };
    }
    else if (n == 3) {
        double node1 = -(pow((3.0 / 5.0), 1.0 / 2.0));
        double node2 = 0.0;
        double node3 = (pow((3.0 / 5.0), 1.0 / 2.0));
        nodes = { node1, node2, node3 };
        weights = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };
    }
    else if (n == 4) {
        double node1 = (-(1.0 / 35.0)) * pow(525.0 + 70.0 * (pow(30.0, (1.0 / 2.0))), (1.0 / 2.0));
        double node2 = (-(1.0 / 35.0)) * pow(525.0 - 70.0 * (pow(30.0, (1.0 / 2.0))), (1.0 / 2.0));
        double node3 = ((1.0 / 35.0)) * pow(525.0 - 70.0 * (pow(30.0, (1.0 / 2.0))), (1.0 / 2.0));
        double node4 = ((1.0 / 35.0)) * pow(525.0 + 70.0 * (pow(30.0, (1.0 / 2.0))), (1.0 / 2.0));
        nodes = { node1,node2,node3,node4 };
        double weight1 = (1.0 / 36.0) * (18.0 - pow(30.0, (1.0 / 2.0)));
        double weight2 = (1.0 / 36.0) * (18.0 + pow(30.0, (1.0 / 2.0)));
        double weight3 = (1.0 / 36.0) * (18.0 + pow(30.0, (1.0 / 2.0)));
        double weight4 = (1.0 / 36.0) * (18.0 - pow(30.0, (1.0 / 2.0)));
        weights = { 0.347855, 0.652145, 0.652145, 0.347855 };
    }
    else {
        cout << "Invalid number of nodes. Choose from 2, 3, or 4." << endl;;
    }





    vector<double> t;
    for (double x : nodes) {
        t.push_back(0.5 * (a + b) + 0.5 * (b - a) * x);
    }

    vector<double> ft;
    for (double x : t)
    {
        ft.push_back(func(x));
    }

    double integral = 0.0;
    for (size_t i = 0; i < weights.size(); ++i) {
        integral += 0.5 * (b - a) * weights[i] * ft[i];
    }

    return integral;
}


double legendre_integration_20(double (*func)(double), double a, double b, int n) {
    double integral = 0.0;
    double przedzial = (b - a) / 20.0;
    for (int i = 0; i < 20; i++)
    {
        double przaedzial_start = a + i * przedzial;
        double przedzial_koniec = przaedzial_start + przedzial;
        integral += legendre_integration(func, przaedzial_start, przedzial_koniec, n);
    }
    return integral;
}

// Funkcje podca³kowe
double func1(double x) {
    return sin(x);
}

double func2(double x) {
    return pow(x, 2.0) + 2.0 * x + 5.0;
}

double func3(double x) {
    return exp(x);
}

int main() {
    // Obliczanie ca³ek
    cout << "calki dla dwoch" << endl << endl;
    double integral1 = legendre_integration(func1, 0.5, 2.5, 3);
    double integral2 = legendre_integration(func2, 0.5, 5.0, 4);
    double integral3 = legendre_integration(func3, 0.5, 5.0, 2);
    cout << "Wartosc calki z sin(x) w przedziale [0.5, 2.5]: " << integral1 << endl;
    cout << "Wartosc calki z (x^2 + 2x + 5) w przedziale [0.5, 5]: " << integral2 << endl;
    cout << "Wartosc calki z exp(x) w przedziale [0.5, 5]: " << integral3 << endl;
    cout << endl << endl;



    //Obliczanie ca³ek dla 20 przedzialow
    cout << "calki dla dwudziestu" << endl << endl;
    integral1 = legendre_integration_20(func1, 0.5, 2.5, 3);
    integral2 = legendre_integration_20(func2, 0.5, 5.0, 4);
    integral3 = legendre_integration_20(func3, 0.5, 5.0, 2);

    cout << "Wartosc calki z sin(x) w przedziale [0.5, 2.5]: " << integral1 << endl;
    cout << "Wartosc calki z (x^2 + 2x + 5) w przedziale [0.5, 5]: " << integral2 << endl;
    cout << "Wartosc calki z exp(x) w przedziale [0.5, 5]: " << integral3 << endl;

    return 0;
}