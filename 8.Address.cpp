#include <iostream>

using namespace std;

int main() {
  // 1. Static array with index addressing
  cout << "Static array with index addressing" << endl;
  int array1[10];
  for (int i = 0; i < 10; i++) {
    array1[i] = i * i;
    cout << "array1[" << i << "] = " << array1[i] << endl;
  }

  // 2. Static array with pointer addressing
  cout << "Static array with pointer addressing" << endl;
  int array2[10];
  int* pointer2 = array2;
  for (int i = 0; i < 10; i++) {
    *(pointer2 + i) = i * i;
    cout << "*(pointer2 + " << i << ") = " << *(pointer2 + i) << endl;
  }

  // 3. Dynamic array with index addressing
  cout << "Dynamic array with index addressing" << endl;
  int* array3 = new int[10];
  for (int i = 0; i < 10; i++) {
    array3[i] = i * i;
    cout << "array3[" << i << "] = " << array3[i] << endl;
  }
  delete[] array3;

  // 4. Dynamic array with pointer addressing
  cout << "Dynamic array with pointer addressing" << endl;
  int* array4 = new int[10];
  int* pointer4 = array4;
  for (int i = 0; i < 10; i++) {
    *(pointer4 + i) = i * i;
    cout << "*(pointer4 + " << i << ") = " << *(pointer4 + i) << endl;
  }
  delete[] array4;

  return 0;
}