/******************************************************************************
 *
 *  A generic stack and queue using a singly linked list.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 *  % ./list_tests
 * STACK Tests
 * -----------
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
 * QUEUE Tests
 * -----------
 *      Front of queue: 12
 *      Front of queue: 10
 *      Dequeued value: 10
 *      Dequeued value: 2
 *    is_empty (queue): 1
 *      Front of queue: This
 *      Front of queue: is
 *      Dequeued value: is
 *      Dequeued value: an
 *      Dequeued value: example
 *
 ******************************************************************************/

#include <iomanip>
#include <iostream>
#include <string>

#include "list_queue.h"
#include "list_stack.h"

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

// test a queue of integers
void test_int_queue(void) {
    Queue<int> q;

    q.enqueue(12);
    q.enqueue(10);
    q.enqueue(2);

    cout << setw(20) << "Front of queue: " << q.front() << endl;
    q.dequeue();
    cout << setw(20) << "Front of queue: " << q.front() << endl;
    cout << setw(20) << "Dequeued value: " << q.dequeue() << endl;
    cout << setw(20) << "Dequeued value: " << q.dequeue() << endl;
    cout << setw(20) << "is_empty (queue): " << q.is_empty() << endl;

    return;
}

// test a queue of strings
void test_string_queue(void) {
    Queue<string> q;

    q.enqueue("This");
    q.enqueue("is");
    q.enqueue("an");
    q.enqueue("example");

    cout << setw(20) << "Front of queue: " << q.front() << endl;
    q.dequeue();
    cout << setw(20) << "Front of queue: " << q.front() << endl;
    cout << setw(20) << "Dequeued value: " << q.dequeue() << endl;
    cout << setw(20) << "Dequeued value: " << q.dequeue() << endl;
    cout << setw(20) << "Dequeued value: " << q.dequeue() << endl;

    return;
}

int main(void) {
    cout << "STACK Tests" << endl
         << "-----------" << endl;
    test_int_stack();
    test_string_stack();

    cout << endl
         << "QUEUE Tests" << endl
         << "-----------" << endl;
    test_int_queue();
    test_string_queue();

    return (0);
}