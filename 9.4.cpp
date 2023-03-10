#include <iostream>
#include <string>

using namespace std;

int main() {
    const int max_words = 20;
    const int max_word_length = 10;

    // Запрос количества слов
    int num_words;
    cout << "Enter the number of words (<= " << max_words << "): ";
    cin >> num_words;
    cin.ignore(); // Очистка буфера ввода

    // Создание массива строк
    string words[max_words];

    // Заполнение массива строк
    for (int i = 0; i < num_words; ++i) {
        cout << "Enter word #" << i + 1 << " (max length " << max_word_length << "): ";
        getline(cin, words[i]);
    }

    // Вывод слов с четными номерами
    cout << "Words with even indices:" << endl;
    for (int i = 1; i < num_words; i += 2) {
        cout << words[i] << endl;
    }

    return 0;
}
