#include <iomanip>
#include <iostream>

using namespace std;

// main entry point of the program
int main(void) {
    // output the size of basic types using formatted IO streams
    cout << "Type size example" << endl;
    cout << setw(30) << "sizeof(bool): " << sizeof(bool) << endl;
    cout << setw(30) << "sizeof(char): " << sizeof(char) << endl;
    cout << setw(30) << "sizeof(int): " << sizeof(int) << endl;
    cout << setw(30) << "sizeof(short int): " << sizeof(short int) << endl;
    cout << setw(30) << "sizeof(long int): " << sizeof(long int) << endl;
    cout << setw(30) << "sizeof(long long int): " << sizeof(long long int) << endl;
    cout << setw(30) << "sizeof(float): " << sizeof(float) << endl;
    cout << setw(30) << "sizeof(double): " << sizeof(double) << endl;
    cout << setw(30) << "sizeof(long double): " << sizeof(long double) << endl;

    // type inference
    cout << endl
         << endl
         << "Type inference example" << endl;
    auto x = 3 + 4;
    for (auto i = 0; i < 10; i++) {
        cout << setw(20) << "i = " << i << ", i+x = " << i + x << endl;
    }

    return (0);
}