#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

void rozkladLU(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& L, std::vector<std::vector<double>>& U) {
    int n = A.size();

    for (int i = 0; i < n; ++i) {
        for (int k = i; k < n; ++k) {
            double suma = 0.0;
            for (int j = 0; j < i; ++j) {
                suma += L[i][j] * U[j][k];
            }
            U[i][k] = A[i][k] - suma; //wzor 12 dla u 
        }

        for (int k = i; k < n; ++k) {
            if (i == k) {
                L[i][i] = 1.0;
            }
            else {
                double suma = 0.0;
                for (int j = 0; j < i; ++j) {
                    suma += L[k][j] * U[j][i];
                }
                L[k][i] = (A[k][i] - suma) / U[i][i]; //wzor 12 dla l
            }
        }
    }
}

std::vector<double> substytucja_w_przod(std::vector<std::vector<double>>& L, std::vector<double>& B) {
    int n = B.size();
    std::vector<double> Y(n, 0.0);

    for (int i = 0; i < n; ++i) {
        double suma = 0.0;
        for (int j = 0; j < i; ++j) {
            suma += L[i][j] * Y[j];
        }
        Y[i] = B[i] - suma;  //wzor 7 
    }

    return Y;
}

std::vector<double> substytucja_wstecz(std::vector<std::vector<double>>& U, std::vector<double>& Y) {
    int n = Y.size();
    std::vector<double> X(n, 0.0);

    for (int i = n - 1; i >= 0; --i) {
        double suma = 0.0;
        for (int j = i + 1; j < n; ++j) {
            suma += U[i][j] * X[j];
        }
        X[i] = (Y[i] - suma) / U[i][i];
    }

    return X; //wzor 9 - obliczanie wyniku
}

std::vector<std::vector<double>> wczytaj_macierz_z_pliku(const std::string& nazwa_pliku) {
    std::ifstream plik(nazwa_pliku);
    std::vector<std::vector<double>> macierz;
    if (plik.is_open()) {
        std::string linia;
        while (std::getline(plik, linia)) {
            std::vector<double> wiersz;
            std::istringstream iss(linia);
            double wartosc;
            while (iss >> wartosc) {
                wiersz.push_back(wartosc);
            }
            macierz.push_back(wiersz);
        }
        plik.close();
    }
    return macierz;
}

std::vector<double> wczytaj_wektor_z_pliku(const std::string& nazwa_pliku) {
    std::ifstream plik(nazwa_pliku);
    std::vector<double> wektor;
    if (plik.is_open()) {
        double wartosc;
        while (plik >> wartosc) {
            wektor.push_back(wartosc);
        }
        plik.close();
    }
    return wektor;
}

int main() {
    // Wczytanie macierzy A i wektora B z plików
    std::vector<std::vector<double>> A = wczytaj_macierz_z_pliku("A3.txt");
    std::vector<double> B = wczytaj_wektor_z_pliku("B3.txt");

    int n = A.size();
    std::vector<std::vector<double>> L(n, std::vector<double>(n, 0.0));
    std::vector<std::vector<double>> U(n, std::vector<double>(n, 0.0));

    // Wyœwietlenie macierzy rozszerzonej 
    std::cout << "Macierz rozszerzona A:" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << A[i][j] << " ";
        }
        std::cout << B[i] << std::endl;
    }

    //dekompozycja LU
    rozkladLU(A, L, U);

    // Wyœwietlenie macierzy L
    std::cout << std::endl << "Macierz L:" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i > j) {
                std::cout << L[i][j] << " ";
            }
            else if (i == j) {
                std::cout << "1 ";
            }
            else {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }



    // Wyœwietlenie macierzy U
    std::cout << std::endl << "Macierz U:" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i <= j) {
                std::cout << U[i][j] << " ";
            }
            else {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }

    // Obliczenie wektora Y
    std::vector<double> Y = substytucja_w_przod(L, B);

    // Wyœwietlenie wektora Y
    std::cout << std::endl << "Wektor Y:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << Y[i] << std::endl;
    }

    // Obliczenie wektora X
    std::vector<double> X = substytucja_wstecz(U, Y);

    // Wyœwietlenie wyniku
    std::cout << std::endl << "Rozwiazanie ukladu rownan (x0 - xn):" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << "x" << i << ": " << X[i] << std::endl;
    }

    return 0;
}
