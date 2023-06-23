#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "stdio.h"
using namespace std;

int main()
{ 
    FILE* F1, * F2, * F3, * F4;
    int i, j, n, m, k;;
    int** M, * L, * S, * U, * D, * v1, * v2;
    F1 = fopen("number.txt", "r");
    fscanf(F1, "%d", &n);
    M = new int* [n];
    for (i = 0; i < n; i++)
    {
        M[i] = new int[n];
        for (j = 0; j < n; j++) M[i][j] = 0;
    }
    fscanf(F1, "%d", &m);
    for (k = 0; k < m; k++)
    {
        fscanf(F1, "%d%d", &i, &j);
        M[i][j] = 1;
        M[j][i] = 1;
    }
    fclose(F1);
    F2 = fopen("matr.txt", "w+");
    fprintf(F2, " %d %d", n, m);
    fprintf(F2, "\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            fprintf(F2, " ");
            fprintf(F2, "%d", M[i][j]);
        }
        fprintf(F2, "\n");
    }
    fclose(F2);

    for (i = 0; i < n; i++)
        for (j = 0; j < i; j++)
            M[i][j] = 0;

    k = 0;
    v1 = new int[m]; v2 = new int[m];
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (M[i][j])
            {
                v1[k] = i;
                v2[k] = j;
                k++;
            }
    D = new int[m + m]; 
    S = new int[n];
    L = new int[n];
    for (j = 0; j < n; j++) L[j] = 0;
    for (i = 0; i < m; i++)
    {
        L[v1[i]]++;
        L[v2[i]]++;
    }
    S[0] = 0;
    for (j = 1; j < n; j++) S[j] = S[j - 1] + L[j - 1];
    for (i = 0; i < m; i++)
    {
        k = v1[i]; D[S[k]] = v2[i]; S[k]++;
        k = v2[i]; D[S[k]] = v1[i]; S[k]++;
    }

    F3 = fopen("massiv.txt", "w+");
    fprintf(F2, "%d %d", n, m);
    fprintf(F2, "\n");
    for (j = 0; j < n; j++)
        fprintf(F3, "%d ", S[j]);
    fprintf(F3, "\n");
    for (j = 0; j < n; j++)
        fprintf(F3, "%d ", L[j]);
    fprintf(F3, "\n");
    for (j = 0; j < m + m; j++)
        fprintf(F3, "%d ", D[j]);
    if (m == 0) fprintf(F3, "%s", "No vertices");
    fclose(F3);

    F4 = fopen("out.txt", "w+");
    k = 0;
    fprintf(F2, "%d %d", n, m);
    fprintf(F2, "");
    for (i = 0; i < m + m; i++)
    {
        for (j = 0; j < L[i]; j++)
        {
            fprintf(F4, "%d ", i);
            fprintf(F4, "%d ", D[k]);
            k++;
            fprintf(F4, "\n");
        }
    }
    if (m == 0) fprintf(F4, "%s", "No vertices");
    fclose(F4);
}