#include <iomanip>
#include <iostream>
#include <string>

#include "stack.h"

using namespace std;

// main entry point of the program
int main(void) {
    Stack<int> vals;
    Stack<string> ops;
    string token;

    while (getline(cin, token, ' ')) {
        if (token[0] == '(') {
        } else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')
            ops.push(token);
        else if (token[0] == ')') {
            string op = ops.pop();
            double v = vals.pop();
            if (op == "+")
                v = vals.pop() + v;
            else if (op == "-")
                v = vals.pop() - v;
            else if (op == "*")
                v = vals.pop() * v;
            else if (op == "/")
                v = vals.pop() / v;
            vals.push(v);
        } else 
            vals.push(stof(token));
    }

    cout << vals.pop() << endl;

    return (0);
}