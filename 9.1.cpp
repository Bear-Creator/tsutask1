#include <iostream>
#include <string>

using namespace std; 

int main() {
    string str = "Hello, world!"; 
    cout << "String: " << str << endl; 
    cout << "Length: " << str.size() << endl; 

    string substr = str.substr(5, 8);
    cout << "Substring: " << substr << endl; 

    size_t pos = str.find("world"); 
    if (pos != string::npos) { 
        cout << "Substring found at position " << pos << endl;
    } else { 
        cout << "Substring not found" << endl; 
    }

    return 0;
}
