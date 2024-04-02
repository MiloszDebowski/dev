#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class Macierz;

class Dane {
    friend class Macierz;
private:
    static int iloscRownan;

public:
    static int getIloscRownan() {
        return iloscRownan;
    }

    static void znajdzIloscRownan(const string& sciezka) {
        ifstream plik(sciezka);
        if (!plik.is_open()) {
            cerr << "Blad podczas otwierania pliku" << endl;
            return;
        }
        iloscRownan = 0;
        string linia;
        while (getline(plik, linia)) {
            iloscRownan++;
        }
        plik.close();
    }
};

int Dane::iloscRownan = 0;

class Macierz {
private:
    vector<vector<double>> macierz;

public:
    Macierz(int rozmiar) {
        macierz.resize(rozmiar, vector<double>(rozmiar + 1, 0.0));
    }

    void wczytajDane(const string& sciezka1, const string& sciezka2) {
        ifstream plik1(sciezka1), plik2(sciezka2);
        if (plik1.is_open() && plik2.is_open()) {
            for (int wiersz = 0; wiersz < macierz.size(); ++wiersz) {
                for (int kolumna = 0; kolumna < macierz[wiersz].size(); ++kolumna) {
                    if (kolumna == macierz[wiersz].size() - 1) {
                        plik2 >> macierz[wiersz][kolumna];
                    }
                    else {
                        plik1 >> macierz[wiersz][kolumna];
                    }
                }
            }
            plik1.close();
            plik2.close();
        }
    }

    void wyswietl() {
        for (int wiersz = 0; wiersz < macierz.size(); ++wiersz) {
            for (int kolumna = 0; kolumna < macierz[wiersz].size(); ++kolumna) {
                cout << macierz[wiersz][kolumna] << " ";
            }
            cout << endl;
        }
    }

    void eliminacjaGaussa() {
        int n = macierz.size();

        for (int k = 0; k < n; ++k) {
            int maksIndeks = k;
            double maksWartosc = abs(macierz[k][k]);
            for (int i = k + 1; i < n; ++i) {
                if (abs(macierz[i][k]) > maksWartosc) {
                    maksWartosc = abs(macierz[i][k]);
                    maksIndeks = i;
                }
            }

            
            if (maksIndeks != k) {
                swap(macierz[k], macierz[maksIndeks]);
            }

            
           

            
            for (int i = k + 1; i < n; ++i) {
                double mnoznik = macierz[i][k] / macierz[k][k];
                for (int j = k; j <= n; ++j) {
                    macierz[i][j] -= mnoznik * macierz[k][j];
                }
            }
        }

        cout << "Postepowanie proste :" << endl;
        wyswietl();
        cout << endl;

        vector<double> rozwiazanie(n);
        for (int i = n - 1; i >= 0; --i) {
            rozwiazanie[i] = macierz[i][n];
            for (int j = i + 1; j < n; ++j) {
                rozwiazanie[i] -= macierz[i][j] * rozwiazanie[j];
            }
            rozwiazanie[i] /= macierz[i][i];
        }

        cout << "Rozwiazanie ukladu rownan:" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "x" << i << " = " << rozwiazanie[i] << endl;
        }
    }




    int znajdzWierszZRoznaPrzekatnej(int startWiersz, int kolumna) {
        for (int i = startWiersz + 1; i < macierz.size(); ++i) {
            if (macierz[i][kolumna] != 0.0) {
                return i;
            }
        }
        
    }



    void eliminacjaGaussaCrouta() {
        int n = macierz.size();

        for (int przekatna = 0; przekatna < n; ++przekatna) {
            if (macierz[przekatna][przekatna] == 0.0) {
                int nowyWiersz = znajdzWierszZRoznaPrzekatnej(przekatna, przekatna);
                
                swap(macierz[przekatna], macierz[nowyWiersz]);
            }

            for (int wiersz = przekatna + 1; wiersz < n; ++wiersz) {
                double mnoznik = macierz[wiersz][przekatna] / macierz[przekatna][przekatna];
                for (int kolumna = przekatna; kolumna <= n; ++kolumna) {
                    macierz[wiersz][kolumna] -= mnoznik * macierz[przekatna][kolumna];
                }
            }
        }

        cout << "Postepowanie proste  :" << endl;
        wyswietl();
        cout << endl;

        vector<double> rozwiazanie(n);
        for (int i = n - 1; i >= 0; --i) {
            rozwiazanie[i] = macierz[i][n];
            for (int kolumna = i + 1; kolumna < n; ++kolumna) {
                rozwiazanie[i] -= macierz[i][kolumna] * rozwiazanie[kolumna];
            }
            rozwiazanie[i] /= macierz[i][i];
        }

        cout << "Rozwiazanie ukladu rownan:" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "x" << i << " = " << rozwiazanie[i] << endl;
        }
    }
};

int main() {
    Dane::znajdzIloscRownan("B3.txt");
    int n = Dane::getIloscRownan();
    Macierz macierz(n);
    macierz.wczytajDane("A3.txt", "B3.txt");

    cout << "Macierz przed obliczeniami:" << endl;
    macierz.wyswietl();
    cout << endl;
    //A
    macierz.eliminacjaGaussa();
    //B
    //macierz.eliminacjaGaussaCrouta();
    return 0;
}
