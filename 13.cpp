#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <array>
#include <algorithm>
#include <Windows.h>
using namespace std;

float* creating()
{
    float* test = new float[113];
    ifstream in("test.txt");
    if (in.is_open())
    {
        float N;
        int k = 0;
        while (in >> N)
        {
            test[k++] = N;
        }
    }
    in.close();
    return test;
}

vector<string> separator(string st, string separators)
{
    vector<string> res;
    int start = 0;
    while (start != string::npos)
    {
        int end = st.find_first_of(separators, start + 1);
        if (end == string::npos)
            end = st.length();
        res.push_back(st.substr(start, end - start));
        start = st.find_first_not_of(separators, end + 1);
    }
    return res;
}

float** filling(float* test, int n, int m)
{
    float** matrix = new float* [n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new float[m];
    }
    int z = 2;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] = test[z++];
        }
    }
    return matrix;
}

int calcRank(float** matrix, int coll, int row, int* L)
{
    int r, i;
    float eps = 0.000001;
    for (r = 0, i = 0; (i < coll) && (r < row); i++)
    {
        int v = r;
        for (int j = r + 1; j < row; j++)
            if (abs(matrix[j][i]) > abs(matrix[v][i])) v = j;

        if (abs(matrix[v][i]) >= eps)
        {
            if (v != r)
            {
                float* z = matrix[r];
                matrix[r] = matrix[v];
                matrix[v] = z;
            }
            for (int k = r + 1; k < row; k++)
            {
                float c = matrix[k][i] / matrix[i][i];
                for (int j = i; j < coll + 1; j++)
                {
                    matrix[k][j] -= c * matrix[i][j];
                }
            }
            r++;
        }
    }
    return r;
}

float* calcXs(float** matrix, int coll, int row, int rank, int* L)
{
    float* X = new float[coll + 1];
    float eps = 0.000001;

    int i = 0;

    while (i < rank)
    {
        int v = i;  int u = i;
        for (int j = i; j < row; j++)
            for (int k = i; k < coll; k++)
                if (abs(matrix[j][k]) > abs(matrix[v][u])) { v = j; u = k; }

        if (abs(matrix[v][u]) < eps) rank = i;
        else
        {
            if (v != i)
            {
                float* z = matrix[i];
                matrix[i] = matrix[v];
                matrix[v] = z;
            }

            if (u != i)
            {
                for (int k = 0; k < row; k++)
                {
                    float z = matrix[k][i];
                    matrix[k][i] = matrix[k][u];
                    matrix[k][u] = z;
                }

                int p = L[i];
                L[i] = L[u];
                L[u] = p;
            }

            float c = matrix[i][i];
            for (int j = i; j <= coll + 1; j++) matrix[i][j] /= c;

            for (int k = 0; k < row; k++)
                if (k != i)
                {
                    c = matrix[k][i];
                    for (int j = i; j <= coll; j++) matrix[k][j] -= c * matrix[i][j];
                }

            i++;
        }
    }

    i = rank;

    while (i < row && abs(matrix[i][coll]) < eps) i++;

    if (i < row) 
    {
        X[coll] = 0;
    }
    else if (rank == coll) 
    {
        for (int j = 0; j < coll; j++) X[L[j]] = matrix[j][coll];
        X[coll] = 1;
    }
    else
    {
        cout << "Input independant Xs:\n";
        for (int j = rank; j < coll; j++)
        {
            cout << "x" << L[j] + 1 << " = ";
            cin >> X[L[j]];
        }

        for (int j = 0; j < rank; j++)
        {
            X[L[j]] = matrix[j][coll];
            for (int k = rank; k < coll; k++)
                X[L[j]] -= matrix[j][k] * X[L[k]];
        }
        X[coll] = 2;
    }
    return X;
}

vector<vector<int>> readingEquations()
{
    ifstream f("test.txt");
    vector<string> equations;
    vector<vector<int>> coefs;

    if (f.is_open())
    {
        string st;
        while (getline(f, st))
        {
            equations.push_back(st);
        }

    }
    f.close();

    equations = separator(equations[0], ",\n");

    int i = 0;
    for (string eq : equations)
    {
        vector<int> a(4);
        coefs.push_back(a);
        vector<string> equation = separator(eq, " =");
        int coefMult = 1; int j = 0;
        for (string el : equation)
        {
            if (el[0] == 32)
            {
                el = el.substr(1, el.size() - 1);
            }
            if (find(el.begin(), el.end(), 'x') != el.end())
            {
                coefs[i][0] = ((el.size() == 1) ? 1 : (el.size() == 2 && el[0] == '-') ? -1 : stoi(el.substr(0, el.size() - 1))) * coefMult;
            }
            else if (find(el.begin(), el.end(), 'y') != el.end())
            {
                coefs[i][1] = ((el.size() == 1) ? 1 : (el.size() == 2 && el[0] == '-') ? -1 : stoi(el.substr(0, el.size() - 1))) * coefMult;
            }
            else if (find(el.begin(), el.end(), 'z') != el.end())
            {
                coefs[i][2] = ((el.size() == 1) ? 1 : (el.size() == 2 && el[0] == '-') ? -1 : stoi(el.substr(0, el.size() - 1))) * coefMult;
            }
            else if (el.size() == 1 && el[0] == '-')
            {
                coefMult = -1;
            }
            else if (el.size() == 1 && el[0] == '+')
            {
                coefMult = 1;
            }
            else
            {
                coefs[i][3] += stoi(el);
            }
        }
        i++;
    }

    return coefs;
}

float** fillMatrix(vector<vector<int>> coefs, int row, int coll)
{
    float** matrix = new float* [row];
    for (int i = 0; i < row; i++)
    {
        matrix[i] = new float[coll + 1];
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < row; j++)
        {
            matrix[i][j] = (float)coefs[i][j];
        }
        matrix[i][coll] = (float)coefs[i][3];
    }

    return matrix;
}

void defaultMode()
{
    int matrixRank = 0;

    float* ArgsFromTest = creating();

    int equatioNumber = ArgsFromTest[0];
    int unknowNumber = ArgsFromTest[1];

    float* xx = new float[unknowNumber];
    float** matrix = filling(ArgsFromTest, equatioNumber, unknowNumber + 1);
    float** matrixCopy = filling(ArgsFromTest, equatioNumber, unknowNumber + 1);

    int* L = new int[unknowNumber];
    for (int i = 0; i < unknowNumber; i++) L[i] = i;

    matrixRank = calcRank(matrixCopy, unknowNumber, equatioNumber, L);
    delete[] matrixCopy;

    float* X = calcXs(matrix, unknowNumber, equatioNumber, matrixRank, L);

    if (X[unknowNumber] == 0)
    {
        ofstream out("answer.txt");
        if (out.is_open())
            out << "Inconsistent system";
        out.close();
    }
    else if (X[unknowNumber] == 1)
    {
        ofstream out("answer.txt");
        if (out.is_open())
            for (int i = 0; i < unknowNumber; i++) out << "x" << i + 1 << "=" << X[i] << "; ";
        out.close();
    }
    else
    {
        ofstream out("answer.txt");
        if (out.is_open())
        {
            for (int i = matrixRank; i < unknowNumber; i++) out << "x" << i + 1 << ", ";
            out << "is free\n";
            for (int i = 0; i < unknowNumber; i++) out << "x" << i + 1 << "=" << X[i] << "; ";
        }
        out.close();
    }
    /*for (int i = 0; i < equatioNumber; i++)
        delete[] matrix[i];*/
    delete[] matrix;
    delete[] X;
    delete[] L;
}

void intersectionPlanesMode()
{
    vector<vector<int>> coefs;
    coefs = readingEquations();

    int matrixRank;

    int equatioNumber = coefs.size();
    int unknowNumber = 3;

    float* xx = new float[unknowNumber];
    float** matrix = fillMatrix(coefs, equatioNumber, unknowNumber);
    float** matrixCopy = fillMatrix(coefs, equatioNumber, unknowNumber);

    int* L = new int[unknowNumber];
    for (int i = 0; i < unknowNumber; i++) L[i] = i;

    matrixRank = calcRank(matrixCopy, unknowNumber, equatioNumber, L);
    delete[] matrixCopy;

    float* X = calcXs(matrix, unknowNumber, equatioNumber, matrixRank, L);

    if (X[unknowNumber] == 0)
    {
        ofstream out("answer.txt");
        if (out.is_open())
            out << "Inconsistent system";
        out.close();
    }
    else if (X[unknowNumber] == 1)
    {
        ofstream out("answer.txt");
        if (out.is_open())
        {
            out << "x = " << X[0] << "; y = " << X[1] << "; z = " << X[2];
        }
        out.close();
    }
    else
    {
        ofstream out("answer.txt");
        if (out.is_open())
        {
            for (int i = matrixRank; i < unknowNumber; i++) out << ((i == 0) ? "x" : (i == 1) ? "y" : "z") << ", ";
            out << "are free\n";
            out << "x = " << X[0] << "; y = " << X[1] << "; z = " << X[2];
        }
        out.close();

        if (out.is_open())
            out << "Set of decisions";
        out.close();
    }
    delete[] matrix;
    delete[] X;
    delete[] L;
}



int main()
{
    cout << "Input mode(1 - default / 2 - INTERSECTION POINT OF THE PLANES): ";
    int i;
    cin >> i;

    switch (i)
    {
    case 1:
        defaultMode();
        break;
    case 2:
        intersectionPlanesMode();
        break;
    default:
        cout << "wrong input\n";
        break;
    }
}