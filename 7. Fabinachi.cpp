#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double x, func;
    double step = (3.99) / 9.0; 
    x = 0.01;
    int i = 0;
    while (i <= 9) {
        x += step;
        func = sin(x) / x;
        cout << "x = " << x << ", function = " << func << endl;
        i++;
    }

    cout << endl;

    int MAX, n = 3;
    int summ = 2, n1 = 1, n2 = 1, g;
    cout << "Enter a large number MAX: ";
    cin >> MAX;
    while (summ <= MAX) {
        g = n1;
        n1 += n2;
        n2 = g;
        summ += n1;
        n++;
    }

    cout << "The sum of the first " << n - 1 << " fibonacci numbers is " << summ - n1 << endl;
    cout << "The " << n - 1 << "th Fibonacci number is " << n2 << endl;
}