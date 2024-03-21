#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<algorithm>
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
            for (int i = 0; i < macierz.size(); ++i) {
                for (int j = 0; j < macierz[i].size(); ++j) {
                    if (j == macierz[i].size() - 1) {
                        plik2 >> macierz[i][j];
                    }
                    else {
                        plik1 >> macierz[i][j];
                    }
                }
            }
            //plik1,plik2.close();
            plik1.close();
            plik2.close();
        }
    }

    void wyswietl() {
        for (int i = 0; i < macierz.size(); ++i) {
            for (int j = 0; j < macierz[i].size(); ++j) {
                cout << macierz[i][j] << " ";
            }
            cout << endl;
        }
    }

    void eliminacjaGaussa() {
        int n = macierz.size();

        for (int k = 0; k < n; ++k) 
        {        
            int row = 0;
            double max = 0;
            if (macierz[k][k] == 0.0)
            {
                for (int u = 0; u < n; u++)
                {
                    if (macierz[u][k] > max) { max = macierz[u][k]; row++;
                    for(int y=0;y<n+1;y++)
                    {
                        swap(macierz[0][y], macierz[k][y]);
                    }
                    }
                }
            }
            
                
            
            for (int i = k + 1; i < n; ++i) 
            {
               
                float mnoznik = macierz[i][k] / macierz[k][k];
                for (int j = k; j <= n; ++j) 
                {
                    macierz[i][j] -= mnoznik * macierz[k][j];
                }
            }
        }

        cout << "Macierz rozszerzona - trojkatna  :" << endl;
        wyswietl();
        cout << endl;

        vector<double> rozwiazanie(n);
        for (int i = n - 1; i >= 0; --i) {
            rozwiazanie[i] = macierz[i][n];
            for (int k = i + 1; k < n; ++k) {
                rozwiazanie[i] -= macierz[i][k] * rozwiazanie[k];
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
    Dane::znajdzIloscRownan("B4.txt");
    int n = Dane::getIloscRownan();
    Macierz macierz(n);
    macierz.wczytajDane("A4.txt", "B4.txt");

    cout << "Macierz przed obliczeniami:" << endl;
    macierz.wyswietl();
    cout << endl;

    macierz.eliminacjaGaussa();

    return 0;
}