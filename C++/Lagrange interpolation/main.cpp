#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include<math.h>

using namespace std;

class Dane {
private:
    float x, y;
   

public:
    void setX(float x0) {
        x = x0;
    }
    void setY(float y0) {
        y = y0;
    }
    void print()
    {
        cout << x << ";" << y << endl;
    }
    float getX() { return x; }
    float getY() { return y; }
};

float returnX(string line) {
    size_t pos = line.find(' ');
    if (pos != string::npos) {
        string x_str = line.substr(0, pos);
        return stof(x_str);
    }
    return 0.0f; 
}

float returnY(string line) {
    size_t pos = line.find(' ');
    if (pos != string::npos) {
        string y_str = line.substr(pos + 1);
        return stof(y_str);
    }
    return 0.0f; 
}
float function(float x)
{
    float y;
    y = pow(x, (1 / 3.0));
    return y;
}



int main() {
    //1
    cout << "\t\t\tZADANIE 1\n\n";
    fstream plik;
    string sciezka = "C:/Users/milos/source/repos/Interpolacja Lagrange'a/Interpolacja Lagrange'a/wezly.txt";
    plik.open(sciezka, ios::in);
    string test;
    int count = 0;
    if (plik.good() == true) {

        while (!plik.eof()) {
            getline(plik, test);
            count++;
        }
        plik.close();

        vector<string> dane(count);
        plik.open(sciezka, ios::in);
        int i = 0;
        while (!plik.eof()) {
            getline(plik, dane[i]);
            i++;
        }
        plik.close();


        vector<Dane> XY(count);
        for (int j = 0; j < count; j++) {
            XY[j].setX(returnX(dane[j]));
            XY[j].setY(returnY(dane[j]));
        }
        //for (int j = 0; j < count; j++)//WYSWIETLANIE
        //{
        //    XY[j].print();
        //}
        cout << "Podaj x: ";
        float x;
        float y = 0;
        cin >> x;
        system("cls");
        
        for (i = 0; i < count; i++)
{
        float p = 1.0f;
        for (int j = 0; j < count; j++)
        {
            if (i != j)
            {
                p *= (x - XY[j].getX()) / (XY[i].getX() - XY[j].getX());
            }
        }
        y += p * XY[i].getY();
        }
        system("cls");
        cout << "\t\t\tZADANIE 1\n\n";
        cout << "Liczba wezlow: " << count << endl;
        cout << "Dane - wezly interpolacji oraz wartosci funkcji w wezlach: " << endl;
        for (int i=0;i<count;i++)
        {
            cout << "x" << i << " = " << XY[i].getX() << "   f(x" << i << ") = " << XY[i].getY()<<endl;
        }
        cout << "Punkt, w ktorym liczymy wartosc wielomianu: " << x << endl;
        cout << "Wartosc wielomianu Lagrange'aw danym punkcie: " << y << endl;
    }
    else {
        cout << "Nie udalo sie wczytac danych..." << endl;
    }
    
    //2
    cout << "\n\n\n\t\t\tZADANIE 2\n\n";
    
    fstream plik2;
    sciezka = "C:/Users/milos/source/repos/Interpolacja Lagrange'a/Interpolacja Lagrange'a/wezly2.txt";
    plik2.open(sciezka, ios::in);
    string test2;//nieuzywane
    count = 0;//zerowanie licznika wezlow
    if (plik2.good() == true)
    {
        while (!plik2.eof())
        {
            getline(plik2, test2);
            count++;
        }
        plik2.close();

        float* daneX = new float[count];
        float* daneY = new float[count];

        plik2.open(sciezka, ios::in);
        for (int i = 0; i < count; i++)
        {
            plik2 >> daneX[i];
            daneY[i] = function(daneX[i]);
        }
        plik2.close();

        Dane* XY2 = new Dane[count];
        for (int j = 0; j < count; j++) {
            XY2[j].setX(daneX[j]);
            XY2[j].setY(daneY[j]);
        }

        delete[] daneY;
        delete[] daneX;

        float x = pow(50, (1 / 3.0));
        cout << "x = " << x << endl;

        float y = 0;

        for (int i = 0; i < count; i++)
        {
            float p = 1.0f;
            for (int j = 0; j < count; j++)
            {
                if (i != j)
                {
                    p *= (x - XY2[j].getX()) / (XY2[i].getX() - XY2[j].getX());
                }
            }
            y += p * XY2[i].getY();
        }

        cout << "Liczba wezlow: " << count << endl;
        cout << "Dane - wezly interpolacji oraz wartosci funkcji w wezlach: " << endl;
        for (int i = 0; i < count; i++)
        {
            cout << "x" << i << " = " << XY2[i].getX() << "   f(x" << i << ") = " << XY2[i].getY() << endl;
        }
        cout << "Punkt, w ktorym liczymy wartosc wielomianu: " << x << endl;
        cout << "Wartosc wielomianu Lagrange'a w danym punkcie: " << y << endl;

        delete[] XY2;
    }
    else {
        cout << "Nie udalo sie wczytac danych..." << endl;
    }

}
