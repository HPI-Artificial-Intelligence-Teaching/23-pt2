#include <iomanip>
#include <iostream>

using namespace std;

// A simple struct to demonstrate operator overloading
struct Rational {
    int p;
    int q;

    // Operator overloading for a typecast operator
    operator double() const { return ((double)p / (double)q); }
};

// overloading of the addition operator
Rational operator+(Rational const& a, Rational const& b) {
    Rational c = {a.p * b.q + b.p * a.q, a.q * b.q};
    return (c);
}

// overloading of the multiplication operator
Rational operator*(Rational const& a, Rational const& b) {
    Rational c = {a.p * b.q, a.q * b.q};
    return (c);
}

// prints a rational number on the output stream
void print_rational(const Rational& r, int width = 10) {
    cout << setw(width) << (double)r.p / (double)r.q;
    return;
}

// integer version of the function f
int f(int x, int y) {
    return (x + y);
}

// double version of the function f
int f(double x, double y) {
    return ((int)(x * y));
}

// main entry point of the program
int main(void) {
    cout << setw(20) << "f(4,3) = " << f(4, 3) << endl;
    cout << setw(20) << "f(4.0,3.0) = " << f(4.0, 3.0) << endl;
    cout << setw(20) << "f(5,(int) 6.0) = " << f(5, (int)6.0) << endl;
    cout << setw(20) << "f(5.0,(double) 6) = " << f(5.0, (double)6) << endl;

    Rational a = {1, 2};
    Rational b = {1, 4};
    Rational c = a + b;
    Rational d = a * b;

    cout << setw(20) << "1/2 + 1/4 = " << (double)c.p / (double)c.q << endl;
    cout << setw(20) << "1/2 * 1/4 = " << a * b << endl;
    cout << setw(20) << "1/2 * 1/4 = ";
    print_rational(d);
    cout << endl;
    cout << setw(20) << "1/2 * 1/4 = ";
    print_rational(d, 5);
    cout << endl;

    return (0);
}