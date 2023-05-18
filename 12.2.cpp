#include <iostream>
#include <vector>

using namespace std;

void placeQueens(int k, vector<int>& columns, vector<vector<int>*>& solutions) {
    int n = columns.size();
    if (k == n) { // базовый случай: все ферзи размещены
        solutions.push_back(new vector<int>(columns));
    } else {
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

vector<vector<int>*>* solveQueens(int k) {
    vector<vector<int>*>* solutions = new vector<vector<int>*>();
    vector<int> columns(k);
    placeQueens(0, columns, *solutions);
    return solutions;
}

void deleteSolutions(vector<vector<int>*>& solutions) {
    for (vector<int>* solution : solutions) {
        delete solution;
    }
}

void deleteSolutionPointers(vector<vector<int>*>* solutions) {
    for (vector<int>* solution : *solutions) {
        delete solution;
    }
    delete solutions;
}

int main() {
    int k;
    cout << "Enter the number of queens: ";
    cin >> k;

    vector<vector<int>*>* solutions = solveQueens(k);
    int numSolutions = solutions->size();

    cout << "Number of solutions: " << numSolutions << endl;
    cout << "Solutions:" << endl;
    for (int i = 0; i < numSolutions; i++) {
        vector<int>* solution = (*solutions)[i];
        for (int j = 0; j < k; j++) {
            for (int l = 0; l < k; l++) {
                if ((*solution)[j] == l) {
                    cout << "Q ";
                } else {
                    cout << "- ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    deleteSolutionPointers(solutions);

    return 0;
}
