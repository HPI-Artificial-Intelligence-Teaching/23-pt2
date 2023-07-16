#include <stdio.h>
#include <stdexcept>
#include <string>
#include "Stack.h"
#include "Queue.h"

bool is_operator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool is_number(char c)
{
    return ((c >= '0' && c <= '9') || c == '.');
}

int precedence(char a, char b)
{
    if (a == '*' || a == '/')
    {
        return 1;
    }
    else if ((a == '+' || a == '-') && (b == '+' || b == '-'))
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

std::string infix_to_postfix(std::string inp)
{

    std::string tokens = inp;
    std::string out;
    Stack<char> S = Stack<char>();
    Queue<char> Q = Queue<char>();
    while (tokens.front())
    {
        char t = tokens.front();
        tokens.erase(0, 1); // remove token from sequence
        if (t == ' ')       // ignore spaces
        {
        }
        else if (t == '(')
        {
            S.push(t);
        }
        else if (t == ')')
        {
            try
            {
                while (S.top() != '(')
                {
                    Q.enqueue(S.pop());
                }
                S.pop();
            }
            catch (const std::logic_error &e)
            {
                throw std::invalid_argument("Mismatched parentheses (too many right parentheses)");
            }
        }
        else if (is_operator(t))
        {
            while (!S.is_empty() && is_operator(S.top()) && precedence(t, S.top()) < 1)
            {
                Q.enqueue(S.pop());
            }
            S.push(t);
        }
        else if (is_number(t)) // die Gleitkommazahl läuft bis zum nächsten nicht-zahl Zeichen
        {
            Q.enqueue(t);
            while (tokens.front() && is_number(tokens.front()))
            {
                t = tokens.front();
                Q.enqueue(t);
                tokens.erase(0, 1);
            }
            Q.enqueue(' ');
        }
        else
        {
            throw std::invalid_argument("Invalid character in input");
        }
    }
    while (!S.is_empty())
    {
        if (S.top() == '(')
        {
            throw std::invalid_argument("Mismatched parentheses (too many left parentheses)");
        }
        Q.enqueue(S.pop());
    }
    while (!Q.is_empty())
    {
        if (is_operator(Q.front()))
        {
            out = out + Q.dequeue() + " ";
        }
        else
        {
            out += Q.dequeue();
        }
    }
    if (out.back() == ' ')
    {
        out.pop_back();
    }
    return out;
}

float evaluate_infix(std::string inp)
{
    std::string tokens = infix_to_postfix(inp);
    Stack<float> S = Stack<float>();
    while (tokens.front())
    {
        char t = tokens.front();
        tokens.erase(0, 1); // remove token from sequence
        if (t == ' ')       // ignore spaces
        {
        }
        else if (is_operator(t))
        {
            try
            {
                float a = S.pop();
                float b = S.pop();
                switch (t)
                {
                case '*':
                    S.push(a * b);
                    break;
                case '/':
                    S.push(b / a);
                    break;
                case '+':
                    S.push(a + b);
                    break;
                case '-':
                    S.push(a - b);
                    break;
                }
            }
            catch (const std::logic_error &e)
            {
                throw std::invalid_argument("Invalid expression");
            }
        }
        else if (is_number(t))
        {
            std::string num = std::string(1, t);
            while (tokens.front() && is_number(tokens.front()))
            {
                num += tokens.front();
                tokens.erase(0, 1);
            }
            S.push(std::stof(num));
        }
        else
        {
            throw std::invalid_argument("Invalid character in input");
        }
    }
    return S.pop();
}