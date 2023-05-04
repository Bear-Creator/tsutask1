#include <iostream>
#include <vector>

using namespace std;

void placeQueens(int k, vector<int>& columns, vector<vector<int>>& solutions) {
    int n = columns.size();
    if (k == n) { // base case: all queens are placed
        solutions.push_back(columns);
    } 
    else {
        for (int i = 0; i < n; i++) {
            bool canPlace = true;
            for (int j = 0; j < k; j++) {
                if (columns[j] == i || abs(columns[j] - i) == abs(k - j)) {
                    canPlace = false;
                    break;
                }
            }
            if (canPlace) {
                columns[k] = i;
                placeQueens(k+1, columns, solutions);
            }
        }
    }
}

vector<vector<int>> solveQueens(int k) {
    vector<vector<int>> solutions;
    vector<int> columns(k);
    placeQueens(0, columns, solutions);
    return solutions;
}

int main() {
    int k;
    cout << "Enter the number of queens: ";
    cin >> k;

    vector<vector<int>> solutions = solveQueens(k);
    int numSolutions = solutions.size();

    cout << "Number of solutions: " << numSolutions << endl;
    cout << "Solutions:" << endl;
    for (int i = 0; i < numSolutions; i++) {
        for (int j = 0; j < k; j++) {
            for (int l = 0; l < k; l++) {
                if (solutions[i][j] == l) {
                    cout << "Q ";
                } else {
                    cout << "- ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
