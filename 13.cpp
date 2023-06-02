#include <iostream>
#include <fstream>

using namespace std;

// Вывод ступ. матрицы результата в файл
void MatrixPrint(float **matrix, int n, int m) {
    ofstream fout("output.txt");
    int i, j;
    fout << "step matrix: " << endl;
      for (i=0; i<n; i++)
       {
          for (j=0; j<m; j++)
            fout << matrix[i][j] << " ";
        fout << endl;
       }
    fout << endl;
    fout.close();
}

// Функция для приведения матрицы к ступенчатому виду методом Гаусса-Жордана
void stepMatrix(float **matrix, int n, int m) {
    int lead = 0;

    for (int r = 0; r < n; r++) {
        if (lead >= m)
            break;

        int i = r;
        while (matrix[i][lead] == 0) {
            i++;
            if (i == n) {
                i = r;
                lead++;
                if (lead == m)
                    return;
            }
        }

        swap(matrix[i], matrix[r]);

        float val = matrix[r][lead];
        if (val != 0) {
            for (int j = 0; j < m; j++)
                matrix[r][j] /= val;
        }

        for (int i = 0; i < n; i++) {
            if (i != r) {
                float factor = matrix[i][lead];
                for (int j = 0; j < m; j++)
                    matrix[i][j] -= factor * matrix[r][j];
            }
        }

        lead++;
    }


    // for (i=0; i<n; i++)
    //  {
    //    tmp=matrix[i][i];
    //      for (j=n;j>=i;j--)
    //          matrix[i][j]/=tmp;
    //        for (j=i+1;j<n;j++)
    //       {
    //          tmp=matrix[j][i];
    //            for (k=n;k>=i;k--)
    //          matrix[j][k]-=tmp*matrix[i][k];
    //       }
    //   };
}

int rang(float **matrix, int n, int m) {
    for (int i = n; i > 0; i--)
        for (int j = 0; j < m; j++)
            if (matrix[i-1][j] != 0) return i;
    return 0;
}

// Единственное решение
void OneVar(float **matrix, float *xx, int n) {
    xx[n-1] = matrix[n-1][n];
     for (int i=n-2; i>=0; i--)
       {
           xx[i] = matrix[i][n];
           for (int j=i+1;j<n;j++) xx[i]-=matrix[i][j]*xx[j];
       }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int i, j, n, m;
    //создаем массив
        fin >> n;
        fin >> m;
        m+=1;
    float **matrix = new float *[n];
        for (i=0; i<n; i++)
            matrix[i] = new float [m];
 
//инициализируем
 
    for(i = 0; i<n; i++)
        for (j = 0; j<m; j++)
            fin >> matrix[i][j];

 
 //выводим массив
    cout << "matrix: " << endl;
      for (i=0; i<n; i++)
       {
          for (j=0; j<m; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
       }
    cout << endl;

    // Вызов функции приведения матрицы к ступенчатому виду
    stepMatrix(matrix, n, m);

    // Вывод ступ. матрицы результата в файл
    fout << "step matrix: " << endl;
      for (i=0; i<n; i++)
       {
          for (j=0; j<m; j++)
            fout << matrix[i][j] << " ";
        fout << endl;
       }
    fout << endl;

    // Нет единственного решения
    if (rang(matrix, n, m-1) != m-1)
    {
        fout << "there is no single solution";
        fout.close();
        return 0;
    }
    

    //Единственное решение
    float xx[m];
    OneVar(matrix, xx, n);

    fout << "only decision:" << endl;
    for (i=0; i<n; i++)
        fout << xx[i] << " ";
    fout << endl;

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    fin.close();
    fout.close();

    return 0;
}
