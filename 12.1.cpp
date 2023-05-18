#include <iostream>
#include <vector>

using namespace std;

// Функция для обмена двух элементов
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Функция для генерации всех перестановок
void generatePermutations(vector<int>& arr, int start, int end) {
    if (start == end) {
        // Выводим текущую перестановку
        for (int i = 0; i <= end; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    } else {
        // Генерируем все перестановки
        for (int i = start; i <= end; i++) {
            // Меняем текущий элемент с элементом на позиции start
            swap(arr[start], arr[i]);
            
            // Генерируем перестановки для оставшейся части массива
            generatePermutations(arr, start + 1, end);
            
            // Возвращаем исходное состояние массива
            swap(arr[start], arr[i]);
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    
    vector<int> arr(n);
    
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << "Permutations: " << endl;
    generatePermutations(arr, 0, n - 1);
    
    return 0;
}
