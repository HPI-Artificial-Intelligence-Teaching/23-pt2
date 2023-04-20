#include <iomanip>
#include <iostream>

using namespace std;

// This function double the references given to it
void double_number(int& x) {
    x *= 2;
    return;
}

// This function checks that the number passed by const-reference is even
bool is_even(const int& x) {
    // This is a compile time error as the function tries to change the value that x refers to
    // x += 2;
    return (x % 2 == 0);
}

// main entry point of the program
int main(void) {
    int x{10}, y{42};
    const int z{66};

    // This is not ok b/c of the const-ness of z
    // z = 13;

    int* const p{&x};
    cout << setw(20) << "*p = " << *p << endl;
    *p += 17;
    cout << setw(20) << "*p + 17 = " << *p << endl;

    // This does not compile b/c the pointer is const
    // p = &y;

    const int* const p2{&y};
    cout << setw(20) << "*p2 = " << *p2 << endl;
    // This is no longer possible b/c the pointer p2 is const pointing to a const int!
    // *p2 += 17;
    // cout << setw(20) << "*p + 17 = " << *p2 << endl;

    double_number(*p);
    cout << setw(20) << "*p (after double) = " << *p << endl;

    // This call is not possible because the function double_number MIGHT change the value (it's constness does not promise not to!)
    // double_number(*p2);
    // cout << setw(20) << "*p2 (after double) = " << *p2 << endl;

    cout << setw(20) << "*p is even = " << is_even(*p) << endl;
    // This call IS possible because the function is_even promises in its signature not to change the value it's given!
    cout << setw(20) << "*p2 is even = " << is_even(*p2) << endl;

    return (0);
}