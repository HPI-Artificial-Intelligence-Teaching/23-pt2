#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

// C-like self-referential structure of a linked list
struct IntList {
    int value;
    IntList* next;
};

// adds an element to a linked list
IntList* add_element(IntList* head, int value) {
    IntList* new_element = new IntList;
    new_element->value = value;
    new_element->next = head;
    return (new_element);
}

// prints a linked list on the screen; using references avoids having to check for nullptr
void print_list(IntList& head) {
    while (true) {
        cout << head.value;
        if (head.next != nullptr) {
            cout << ", ";
            head = *head.next;
        } else
            break;
    }
    cout << endl;
    return;
}

// main entry point of the program
int main() {
    int x{5};                   // a 5 is allocated on the stack frame
    const int c{(int)sqrt(5)};  // the compiler knows that c cannot be changed after this
    int* p{&x};                 // a pointer to the location that stores x
    int& r{x};                  // initializes an lvalue-reference to the location that stores x
    // const int& r2{c};           // an lvalue-reference to the location that stores c (which is supposed to be const )

    cout << setw(10) << "x = " << x << endl;
    cout << setw(10) << "c = " << c << endl;
    x += c;
    cout << setw(10) << "x = " << x << " (after adding c)" << endl;
    *p += c;
    cout << setw(10) << "x = " << x << " (after adding c to the de-refence of p)" << endl;
    cout << setw(10) << "r = " << r << endl;
    r += c;
    cout << setw(10) << "x = " << x << " (after adding c to r)" << endl;
    // r = r2;
    // cout << setw(10) << "x = " << x << " (after assigning r2 to r)" << endl;

    // demonstrates a linked list and how to use a print function which uses a reference
    cout << endl
         << endl;
    IntList* head = nullptr;
    for (auto i = 0; i < 100; i++)
        head = add_element(head, i);
    print_list(*head);

    return (0);
}