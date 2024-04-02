#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include<iostream>
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
        cout << endl;
    }
    void copy(Macierz matka)
    {
        for (int wiersz = 0; wiersz < macierz.size(); wiersz++)
        {
            for (int kolumna = 0; kolumna < macierz[wiersz].size(); kolumna++)
            {
                macierz[wiersz][kolumna] = matka.macierz[wiersz][kolumna];
            }
        }

    }
    void setL()
    {
        for (int i = 0; i < macierz.size(); i++)
        {
            macierz[i][i] = 1;
        }
    }
    void setU()
    {

    }
};

int main() {
    Dane::znajdzIloscRownan("B3.txt");
    int n = Dane::getIloscRownan();
    Macierz macierz(n);
    macierz.wczytajDane("A3.txt", "B3.txt");

    cout << "Macierz przed obliczeniami:" << endl;
    macierz.wyswietl();

    Macierz L(n-1);
    Macierz U(n-1);
    L.copy(macierz);
    U.copy(macierz);
    L.setL();
    L.wyswietl();
    
    return 0;
}