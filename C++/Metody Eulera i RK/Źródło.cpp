#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

// Function for the first differential equation
double f1(double x, double y) {
    return 2 * y * (x + 1);
}

// Function for the second differential equation
double f2(double x, double y) {
    return x + y;
}

// Euler method implementation
double euler_method(double (*f)(double, double), double x0, double y0, double x_end, int N) {
    double h = (x_end - x0) / N;
    double x = x0;
    double y = y0;
    for (int i = 0; i < N; ++i) {
        y += h * f(x, y);
        x += h;
    }
    return y;
}

// RK2 method implementation
double rk2_method(double (*f)(double, double), double x0, double y0, double x_end, int N) {
    double h = (x_end - x0) / N;
    double x = x0;
    double y = y0;
    for (int i = 0; i < N; ++i) {
        double k1 = f(x, y);
        double k2 = f(x + h, y + h * k1);
        y += h * (k1 + k2) / 2;
        x += h;
    }
    return y;
}

// RK4 method implementation
double rk4_method(double (*f)(double, double), double x0, double y0, double x_end, int N) {
    double h = (x_end - x0) / N;
    double x = x0;
    double y = y0;
    for (int i = 0; i < N; ++i) {
        double k1 = f(x, y);
        double k2 = f(x + h / 2, y + h * k1 / 2);
        double k3 = f(x + h / 2, y + h * k2 / 2);
        double k4 = f(x + h, y + h * k3);
        y += h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        x += h;
    }
    return y;
}

// Exact solutions for convergence study
double exact_solution1(double x) {
    return std::exp(x * x + 2 * x);
}

double exact_solution2(double x) {
    return 2 * std::exp(x) - x - 1;
}

// Main function
int main() {
    // Initial conditions and parameters
    double x0 = 0.0;
    double y0_1 = 1.0;
    double y0_2 = 0.1;
    double x_end = 1.0;
    int N = 10;

    // Solve for y'(x) = 2*y*(x + 1), y(0) = 1.0
    double euler_y1 = euler_method(f1, x0, y0_1, x_end, N);
    double rk2_y1 = rk2_method(f1, x0, y0_1, x_end, N);
    double rk4_y1 = rk4_method(f1, x0, y0_1, x_end, N);
    double exact_y1 = exact_solution1(x_end);

    cout << "Rownanie 1: y'(x) = 2*y*(x + 1), y(0) = 1.0\n";
    cout << "Warunek pocz¹tkowy: y(" << x0 << ") = " << y0_1 << "\n";
    cout << "Punkt koncowy: x = " << x_end << "\n";
    cout << "Krok obliczen: h = " << (x_end - x0) / N << "\n";
    cout << "Rozwiazanie metoda Eulera w punkcie koncowym: y(" << x_end << ") = " << euler_y1 << "\n";
    cout << "Rozwiazanie metoda RK2 w punkcie koncowym: y(" << x_end << ") = " << rk2_y1 << "\n";
    cout << "Rozwiazanie metoda RK4 w punkcie koncowym: y(" << x_end << ") = " << rk4_y1 << "\n";
    cout << "Dokladny wynik: y(" << x_end << ") = " << exact_y1 << "\n";

    // Solve for y'(x) = x + y, y(0) = 0.1
    double euler_y2 = euler_method(f2, x0, y0_2, x_end, N);
    double rk2_y2 = rk2_method(f2, x0, y0_2, x_end, N);
    double rk4_y2 = rk4_method(f2, x0, y0_2, x_end, N);
    double exact_y2 = exact_solution2(x_end);

    cout << "\nRownanie 2: y'(x) = x + y, y(0) = 0.1\n";
    cout << "Warunek poczatkowy: y(" << x0 << ") = " << y0_2 << "\n";
    cout << "Punkt koncowy: x = " << x_end << "\n";
    cout << "Krok obliczen: h = " << (x_end - x0) / N << "\n";
    cout << "Rozwiazanie metoda Eulera w punkcie koncowym: y(" << x_end << ") = " << euler_y2 << "\n";
    cout << "Rozwiazanie metoda RK2 w punkcie koncowym: y(" << x_end << ") = " << rk2_y2 << "\n";
    cout << "Rozwiazanie metoda Rk4 w punkcie koncowym: y(" << x_end << ") = " << rk4_y2 << "\n";
    cout << "Dokladny wynik: y(" << x_end << ") = " << exact_y2 << "\n";

    // Convergence study
    vector<int> N_values = { 10, 20, 40, 80, 160 };
    vector<double> errors_euler_1;
    vector<double> errors_rk2_1;
    vector<double> errors_rk4_1;
    vector<double> errors_euler_2;
    vector<double> errors_rk2_2;
    vector<double> errors_rk4_2;

    for (int N : N_values) {
        euler_y1 = euler_method(f1, x0, y0_1, x_end, N);
        rk2_y1 = rk2_method(f1, x0, y0_1, x_end, N);
        rk4_y1 = rk4_method(f1, x0, y0_1, x_end, N);
        exact_y1 = exact_solution1(x_end);
        errors_euler_1.push_back(abs(euler_y1 - exact_y1));
        errors_rk2_1.push_back(abs(rk2_y1 - exact_y1));
        errors_rk4_1.push_back(abs(rk4_y1 - exact_y1));

        euler_y2 = euler_method(f2, x0, y0_2, x_end, N);
        rk2_y2 = rk2_method(f2, x0, y0_2, x_end, N);
        rk4_y2 = rk4_method(f2, x0, y0_2, x_end, N);
        exact_y2 = exact_solution2(x_end);
        errors_euler_2.push_back(abs(euler_y2 - exact_y2));
        errors_rk2_2.push_back(abs(rk2_y2 - exact_y2));
        errors_rk4_2.push_back(abs(rk4_y2 - exact_y2));
    }

    cout << "\nWYNIKI:\n";
    for (size_t i = 0; i < N_values.size(); ++i) {
        cout <<"N: " << N_values[i] <<" BLAD EULERA: " << errors_euler_1[i]
            <<" BLAD RK2: " << errors_rk2_1[i]
            <<" BLAD RK4: " << errors_rk4_1[i]
            <<" BLAD Eulera: " << errors_euler_2[i]
            <<" BLAD RK2: " << errors_rk2_2[i]
            <<" BLAD RK4: " << errors_rk4_2[i] <<endl;
    }

    return 0;
}
