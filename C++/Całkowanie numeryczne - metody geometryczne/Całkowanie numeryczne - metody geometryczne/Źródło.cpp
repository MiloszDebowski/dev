#include <iostream>
#include <cmath>

using namespace std;

double func1(double x) {
    return sin(x);
}

double func2(double x) {
    return x * x + 2 * x + 5;
}

double func3(double x) {
    return exp(x);
}

// Metoda prostok¹tów
double rectangle_method(double (*func)(double), double a, double b, int n) {
    double S = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        double h = a + i * S + S / 2;
        sum += func(h);
    }
    return sum * S;
}

// Metoda trapezów
double trapezoidal_method(double (*func)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = (func(a) + func(b)) / 2;
    for (int i = 1; i < n; ++i) {
        double x_i = a + i * h;//boki
        sum += func(x_i);
    }
    return sum * h;
}

// Metoda parabol
double simpson_method(double (*func)(double), double a, double b, int n) {
    double S = (b - a) / n;
    double sum = func(a) + func(b); 

    for (int i = 1; i < n; ++i) {
        double x_i = a + i * S;
        if (i % 2 == 0) { 
            sum += 2 * func(x_i);
        }
        else { 
            sum += 4 * func(x_i);
        }
    }

    return sum * S / 3;
}


int main() {
    double a = 0.5, b = 2.5; // Przedzia³ ca³kowania
    int n = 4; // Liczba prostok¹tów/trapezów

    // Ca³ka z sin(x)
    cout << "Calka z sin(x) w przedziale od " << a << " do " << b <<". Liczba przedzialow: "<<n<< endl;
    cout << "Metoda prostokatow: " << rectangle_method(func1, a, b, n) << endl;
    cout << "Metoda trapezow: " << trapezoidal_method(func1, a, b, n) << endl;
    cout << "Metoda parabol: " << simpson_method(func1, a, b, n) << endl;
    cout << endl;

    // Ca³ka z x^2 + 2x + 5
    b = 5.0;
    cout << "Calka z x^2 + 2x + 5 w przedziale od " << a << " do " << b << ". Liczba przedzialow: " << n << endl;
    cout << "Metoda prostokatow: " << rectangle_method(func2, a, b, n) << endl;
    cout << "Metoda trapezow: " << trapezoidal_method(func2, a, b, n) << endl;
    cout << "Metoda parabol: " << simpson_method(func2, a, b, n) << endl;
    cout << endl;

    // Ca³ka z exp(x)
    cout << "Calka z exp(x) w przedziale od " << a << " do " << b << ". Liczba przedzialow: " << n << endl;
    cout << "Metoda prostokatow: " << rectangle_method(func3, a, b, n) << endl;
    cout << "Metoda trapezow: " << trapezoidal_method(func3, a, b, n) << endl;
    cout << "Metoda parabol: " << simpson_method(func3, a, b, n) << endl;

    return 0;
}
