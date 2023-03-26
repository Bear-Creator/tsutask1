#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Функция нахождения корневых слов
void findRootWords(const vector<string>& words, vector<string>& rootWords) {
    for (int i = 0; i < words.size(); i++) {
        string word = words[i];
        for (int j = 1; j <= word.length(); j++) {
            string prefix = word.substr(0, j);
            bool isRoot = true;
            for (int k = 0; k < words.size(); k++) {
                if (i == k) continue;
                if (words[k].find(prefix) == 0) {
                    isRoot = false;
                    break;
                }
            }
            if (isRoot) {
                rootWords.push_back(prefix);
                break;
            }
        }
    }
}

int main() {
    ifstream input("input.txt"); // открытие файла для чтения
    ofstream output1("output1.txt"); // открытие файла для записи ответа 1
    ofstream output2("output2.txt"); // открытие файла для записи ответа 2

    vector<string> words;
    string word;
    while (input >> word) {
        words.push_back(word);
    }
    input.close(); // закрытие файла после чтения

    vector<string> rootWords;
    findRootWords(words, rootWords);

    // Поиск самого длинного корневого слова
    string longestRootWord = "NO";
    for (int i = 0; i < rootWords.size(); i++) {
        if (rootWords[i].length() > longestRootWord.length()) {
            longestRootWord = rootWords[i];
        }
    }
    output1 << longestRootWord << endl;

    // Поиск самого важного слова
    int maxCount = 0;
    string mostImportantWord = "NO";
    for (int i = 0; i < words.size(); i++) {
        int count = 0;
        for (int j = 0; j < rootWords.size(); j++) {
            if (words[i].find(rootWords[j]) == 0) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            mostImportantWord = words[i];
        }
    }
    output2 << mostImportantWord << endl;

    output1.close(); // закрытие файла после записи ответа 1
    output2.close(); // закрытие файла после записи ответа 2

    return 0;
}
