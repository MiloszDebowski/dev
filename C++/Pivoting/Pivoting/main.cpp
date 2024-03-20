#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> // Dla std::setprecision

using namespace std;

void partial_pivot_solve(const string& coefficients_file, const string& results_file) {
    // Wczytanie wspó³czynników z pliku
    ifstream coeff_file(coefficients_file);
    if (!coeff_file.is_open()) {
        cerr << "Nie mo¿na otworzyæ pliku " << coefficients_file << endl;
        return;
    }

    vector<vector<double>> A;
    double num;
    while (coeff_file >> num) {
        vector<double> row;
        for (int i = 0; i < 4; ++i) {
            row.push_back(num);
            coeff_file >> num;
        }
        A.push_back(row);
    }
    coeff_file.close();

    // Wczytanie wyników z pliku
    ifstream results(results_file);
    if (!results.is_open()) {
        cerr << "Nie mo¿na otworzyæ pliku " << results_file << endl;
        return;
    }

    vector<double> b;
    while (results >> num) {
        b.push_back(num);
    }
    results.close();

    // Sprawdzenie czy liczba wspó³czynników zgadza siê z liczb¹ wyników
    if (A.size() != b.size()) {
        cerr << "Liczba wspó³czynników i wyników nie zgadza siê." << endl;
        return;
    }

    // Macierz rozszerzona
    vector<vector<double>> augmented_matrix;
    for (size_t i = 0; i < A.size(); ++i) {
        vector<double> row = A[i];
        row.push_back(b[i]);
        augmented_matrix.push_back(row);
    }

    // Rozwi¹zanie uk³adu równañ
    int n = b.size();
    for (int i = 0; i < n; ++i) {
        // Wybór wiersza z maksymaln¹ wartoœci¹ bezwzglêdn¹ w kolumnie
        int max_row = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(augmented_matrix[k][i]) > abs(augmented_matrix[max_row][i])) {
                max_row = k;
            }
        }

        // Zamiana wierszy w macierzy rozszerzonej
        swap(augmented_matrix[i], augmented_matrix[max_row]);

        // Eliminacja Gaussa
        for (int k = i + 1; k < n; ++k) {
            double factor = augmented_matrix[k][i] / augmented_matrix[i][i];
            for (int j = i; j <= n; ++j) {
                augmented_matrix[k][j] -= factor * augmented_matrix[i][j];
            }
        }
    }

    // Wypisanie macierzy rozszerzonej po pierwszym etapie obliczeñ
    cout << "Macierz rozszerzona (po pierwszym etapie obliczeñ):" << endl;
    for (size_t i = 0; i < augmented_matrix.size(); ++i) {
        for (size_t j = 0; j < augmented_matrix[i].size(); ++j) {
            cout << setw(10) << setprecision(8) << augmented_matrix[i][j] << " "; // Ustawienie precyzji na 8 miejsc po przecinku
        }
        cout << endl;
    }

    // Rozwi¹zanie uk³adu równañ
    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = augmented_matrix[i][n];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= augmented_matrix[i][j] * x[j];
        }
        x[i] /= augmented_matrix[i][i];
    }

    // Wypisanie wyniku
    cout << "\nRozwi¹zanie uk³adu równañ (x0 - xn):" << endl;
    for (int i = 0; i < n; ++i) {
        cout << x[i] << " ";
    }
    cout << endl;
}

int main() {
    partial_pivot_solve("A3.txt", "B3.txt");
    return 0;
}
