/******************************************************************************
 *
 *  A generic stack using a resize-able array.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  % ./stack 
 *        Top of stack: 2
 *        Top of stack: 10
 *        Pop of stack: 10
 *        Pop of stack: 12
 *    is_empty (stack): 1
 *        Top of stack: example
 *        Top of stack: an
 *        Pop of stack: an
 *        Pop of stack: is
 *        Pop of stack: This
 *
 ******************************************************************************/

#include "stack.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// test a stack of integers
void test_int_stack(void) {
    Stack<int> s;

    s.push(12);
    s.push(10);
    s.push(2);

    cout << setw(20) << "Top of stack: " << s.top() << endl;
    s.pop();
    cout << setw(20) << "Top of stack: " << s.top() << endl;
    cout << setw(20) << "Pop of stack: " << s.pop() << endl;
    cout << setw(20) << "Pop of stack: " << s.pop() << endl;
    cout << setw(20) << "is_empty (stack): " << s.is_empty() << endl;

    return;
}

// test a stack of strings
void test_string_stack(void) {
    Stack<string> s;

    s.push("This");
    s.push("is");
    s.push("an");
    s.push("example");

    cout << setw(20) << "Top of stack: " << s.top() << endl;
    s.pop();
    cout << setw(20) << "Top of stack: " << s.top() << endl;
    cout << setw(20) << "Pop of stack: " << s.pop() << endl;
    cout << setw(20) << "Pop of stack: " << s.pop() << endl;
    cout << setw(20) << "Pop of stack: " << s.pop() << endl;

    return;
}

int main(void) {
    test_int_stack();
    test_string_stack();

    return (0);
}