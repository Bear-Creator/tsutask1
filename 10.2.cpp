#include <iostream>
#include <vector>

using namespace std;

// Функция упаковки данных
vector<int> packData(int arr[], int N) {
    vector<int> packedData;
    int prev = -1;
    int count = 0;

    for (int i = 0; i < N; i++) {
        int curr = arr[i];
        if (curr == prev) {
            count++;
        } else {
            if (prev != -1) {
                packedData.push_back(prev);
                packedData.push_back(count);
            }
            prev = curr;
            count = 1;
        }
    }

    if (prev != -1) {
        packedData.push_back(prev);
        packedData.push_back(count);
    }

    return packedData;
}

// Функция распаковки данных
void unpackData(vector<int> packedData, int arr[], int N) {
    int index = 0;

    for (int i = 0; i < packedData.size(); i += 2) {
        int num = packedData[i];
        int count = packedData[i + 1];

        for (int j = 0; j < count; j++) {
            arr[index] = num;
            index++;

        }
    }
}

int main() {
    const int N = 10;  
    int arr[N];

    // Заполнение массива случайными числами
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 18;
    }

    // Упаковка данных
    vector<int> packedData = packData(arr, N);

    // Вывод упакованных данных
    for (int i = 0; i < packedData.size(); i += 2) {
        cout << packedData[i] << ":" << packedData[i + 1] << " ";
    }
    cout << endl;

    // Распаковка данных
    int unpackedArr[N];
    unpackData(packedData, unpackedArr, N);
    
    return 0;
}