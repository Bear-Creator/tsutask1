#include <iostream>
#include <vector>

using namespace std;

// Функция упаковки данных
void packData(short arr[], int N, vector<short>& packedData) {
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
}

// Функция распаковки данных
void unpackData(const vector<short>& packedData, short arr[], int N) {
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
    const int N = 1000;  
    short arr[N];

    // Заполнение массива случайными числами
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 18;
    }

    // Упаковка данных
    vector<short> packedData;
    packData(arr, N, packedData);

    // Вывод упакованных данных
    cout << packedData.size() << endl;
    for (int i = 0; i < packedData.size(); i += 2) {
        cout << packedData[i] << ":" << packedData[i + 1] << endl;
    }
    cout << endl;

    // Распаковка данных
    short unpackedArr[N];
    unpackData(packedData, unpackedArr, N);
    
    return 0;
}
