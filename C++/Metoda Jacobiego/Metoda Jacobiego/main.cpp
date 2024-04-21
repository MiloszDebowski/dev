#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<cmath>
#include<iomanip>


using namespace std;


	

vector<vector<double>> loadMatrix(const string& data) {
    ifstream file(data);
    vector<vector<double>> matrix;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<double> row;
            istringstream iss(line);
            double value;
            while (iss >> value) {
                row.push_back(value);
            }
            matrix.push_back(row);
        }
        file.close();
    }
    return matrix;
}
	
vector<double> loadVector(const string& data)
{
    ifstream file(data);
    vector<double> vec;
    if (file.is_open()) {
        double value;
        while (file >> value) {
            vec.push_back(value);
        }
        file.close();
    }
    return vec;
}

void printMatrix(vector<vector<double>>& matrix)
{
    size_t size = matrix.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j <size; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void printVector(vector<double>& vec)
{
    size_t size = vec.size();
    for (int i=0 ; i<size ; i++)
    {
        cout << fixed <<setprecision(5) <<"x["<<i<<"]: " << vec[i] << endl;
    }
}

bool isWeak(vector<vector<double>> matrix)
{
    bool weak = false;
    int biggerCount = 0;
    size_t n = matrix.size();
    for (int i = 0; i < n; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < n; j++)
        {
            if (j != i)
            {
                sum = sum + abs(matrix[i][j]);
            }
        }

        if (abs(matrix[i][i]) > sum)
        {
            biggerCount++;
        }

        if (abs(matrix[i][i]) >= sum)
        {
            weak = true;
        }
        else
        {
            weak = false;
            break;
        }
    }
    if (biggerCount == 0)
    {
        weak = false;
    }

    return weak;
}

void checkMatrix(vector<vector<double>>& matrix)
{
    if (isWeak(matrix) == true)
    {
        cout << "MACIERZ JEST DIAGONALNIE SLABO DOMINUJACA" << endl;
    }
    else
    {
        cout << "MACIERZ NIE JEST DIAGONALNIE SLABO DOMINUJACA" << endl;
    }
}

void printEquation(vector<vector<double>>& matrix, vector<double>& vec)
{
    cout << "             UKLAD ROWNAN" << endl;
    checkMatrix(matrix);
    size_t size = matrix.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << vec[i] << endl;
    }
}

void matrixDecomposition(vector<vector<double>>& matrixA, vector<vector<double>>& matrixL, vector<vector<double>>& matrixU, vector<vector<double>>& matrixD)
{
    size_t size = matrixA.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i > j)
            {
                matrixL[i][j] = matrixA[i][j];
            }
            else if (i==j)
            {
                matrixD[i][i] = matrixA[i][i];
            }
            else
            {
                matrixU[i][j] = matrixA[i][j];
            }
        }
    }
}

vector<vector<double>> addMatrix(vector<vector<double>>& matrixL, vector<vector<double>>& matrixU)
{
    size_t size = matrixL.size();
    vector<vector<double>> matrixLU(size,vector<double>(size,0.0));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if(j>i)
            {
                matrixLU[i][j] = matrixU[i][j];
            }
            else if(j<i)
            {
                matrixLU[i][j] = matrixL[i][j];
            }
        }
        
    }
    return matrixLU;
}

vector<vector<double>> inverseMatrix(vector<vector<double>>& matrix)
{
    size_t size = matrix.size();
    vector<vector<double>> invertedMatrix(size, vector<double>(size, 0.0));
    for (int i = 0; i < size; i++)
    {
                invertedMatrix[i][i] = 1.0/matrix[i][i];
    }
    return invertedMatrix;
}

void solve(vector<vector<double>>& invertedMatrixD, vector<vector<double>>& matrixLU, vector<double>& vec)
{
    int iterations=0;
    cout <<endl<< "ILOSC ITERACJI: ";
    cin >> iterations;
    system("cls");
    size_t size = vec.size();
    vector<double> x(size, 0.0);
    vector<double> x_prev(size, 0.0);

    for (int iter = 0; iter < iterations; iter++) {
        vector<double> x_next(size, 0.0);

        for (size_t i = 0; i < size; i++) {
            double sum = 0.0;
            for (size_t j = 0; j < size; j++) {
                if (j != i) {
                    sum += (matrixLU[i][j] * x[j]);
                }
            }
            x_next[i] = (-invertedMatrixD[i][i] * (sum - vec[i]));
        }

        x_prev = x;
        x = x_next;
    }

    
    cout << "              ROZWIAZANIE PO " << iterations << " ITERACJACH:" << endl;
    printVector(x);

    if (iterations > 1) {
        cout <<endl<<"Blad bezwzgledny : "<<endl;
        for (size_t i = 0; i < size; i++) 
        {
            cout << fixed << setprecision(15) <<"Blad x[" << i << "]: " << abs(x[i] - x_prev[i]) << endl;
        }
    }
}

void solve2(vector<vector<double>>& invertedMatrixD, vector<vector<double>>& matrixLU, vector<double>& vec, double miss)
{
    size_t size = vec.size();
    vector<double> x(size, 0.0);
    vector<double> x_prev(size, 0.0);

    

    int iterations = 0;
    int maxIterations = 1000;
    for (;iterations<maxIterations;iterations++) {
        vector<double> x_next(size, 0.0);

        for (size_t i = 0; i < size; i++) {
            double sum = 0.0;
            for (size_t j = 0; j < size; j++) {
                if (j != i) {
                    sum += (matrixLU[i][j] * x[j]);
                }
            }
            x_next[i] = (-invertedMatrixD[i][i] * (sum - vec[i]));
        }

        x_prev = x;
        x = x_next;
        int isLess = 0;
        for (size_t i = 0; i < size; i++) 
        {
            if (abs(x[i] - x_prev[i]) < miss)
            {
                isLess++;
            }
        }
        if (isLess>=size)
        {
            iterations++;
            goto end;
        }
        
    }


    end:
    cout << "              ROZWIAZANIE PO " << iterations << " ITERACJACH:" << endl;
    printVector(x);
    cout << endl << "MAKSYMALNA PRZYJETA WARTOSC BLEDU BEZWZGLEDNEGO: " <<miss<< endl;
    cout << endl << "BLAD BEZWZGLEDNY : " << endl;
    for (size_t i = 0; i < size; i++)
    {
        cout<<fixed << setprecision(15) << "Blad x[" << i << "]: " << abs(x[i] - x_prev[i]) << endl;
    }
    


}


int main()
{

	//files
	const string fileMatrixA = "A.txt";
	const string fileVectorB = "B.txt";

    //creating matrix and vectors from file
    vector<vector<double>>matrixA = loadMatrix(fileMatrixA);
    vector<double>vectorB = loadVector(fileVectorB);

    printEquation(matrixA,vectorB);

    size_t size = matrixA.size();

    //creating matrix
    vector<vector<double>>matrixL(size, vector<double>(size,0.0));
    vector<vector<double>>matrixU(size, vector<double>(size,0.0));
    vector<vector<double>>matrixD(size, vector<double>(size,0.0));

    matrixDecomposition(matrixA, matrixL, matrixU, matrixD);

    //matrix L+U
    vector<vector<double>> matrixLU = addMatrix(matrixL, matrixU);
    cout << endl << "              MACIERZ L+U" << endl;
    printMatrix(matrixLU);

    //inverse diagonal matrix
    vector<vector<double>> invertedMatrixD = inverseMatrix(matrixD);
    cout << endl << "              MACIERZ DIAGONALNA ODWROTNA" << endl;
    printMatrix(invertedMatrixD);

    //result
    
    solve(invertedMatrixD, matrixLU, vectorB);
    double miss1 = 0.001;
    double miss2 = 0.000001;
    solve2(invertedMatrixD, matrixLU, vectorB,miss1);

	return 0;
}