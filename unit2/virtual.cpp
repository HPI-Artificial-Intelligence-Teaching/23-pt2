#include <iostream>
using namespace std;

// Base class which implements only two methods for showing content: print (virtual) and show (static)
class Base {
   public:
    // prints a fixed string on the standard output
    virtual void print() {
        cout << "print base class\n";
    }
    // prints a fixed string on the standard output
    void show() {
        cout << "show base class\n";
    }
};

// Derived class which overwrites the virtual print method of the parent class
class Derived : public Base {
   public:
    // prints a fixed string on the standard output
    void print() {
        cout << "print derived class\n";
    }
    // prints a fixed string on the standard output
    void show() {
        cout << "show derived class\n";
    }
};

// main entry point of the program
int main() {
    Base *p;
    Derived derived;
    p = &derived;

    // Virtual function which gets resolved with a function pointer at runtime
    p->print();

    // Non-virtual function which is already resolved at compile time (and pointing to the wrong method)
    p->show();

    return (0);
}