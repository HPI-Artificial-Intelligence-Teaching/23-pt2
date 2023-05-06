#ifndef __STACK_H__
#define __STACK_H__

#include <stdexcept>

// Implements a stack with a fixed size array of values that will be resized if more capacity is needed
template <typename T>
class Stack {
    T* stack_data;
    int n;
    int capacity;

    // internal function that resizes the stack to a target size
    void resize(int new_capacity) {
        // allocate new array
        T* new_stack_data = new T[new_capacity];

        // copy all elements on the stack to the new stack
        for (auto i = 0; i < n; i++)
            new_stack_data[i] = stack_data[i];

        // remove old stack and move pointer
        delete[] stack_data;
        stack_data = new_stack_data;

        // set new capacity
        capacity = new_capacity;

        return;
    }

   public:
    // constructor
    Stack(int cap = 1) : n(0), capacity(cap) {
        stack_data = new T[capacity];
    }

    // copy constructor
    Stack(const Stack& s) : n(s.n), capacity(s.capacity) {
        stack_data = new T[capacity];
        for (auto i = 0; i < s.n; i++)
            stack_data[i] = s.stack_data[i];
    }

    // move constructor
    Stack(Stack&& s) : n(s.n), capacity(s.capacity) {
        stack_data = s.stack_data;
        s.stack_data = nullptr;
    }

    // copy assignment
    Stack& operator=(const Stack& s) {
        // free the existing stack
        delete[] stack_data;

        // copy the stack passed in
        n = s.n;
        capacity = s.capacity;
        stack_data = new T[capacity];
        for (auto i = 0; i < s.n; i++)
            stack_data[i] = s.stack_data[i];
        return (*this);
    }

    // move assignment
    Stack& operator=(Stack&& s) {
        // free the existing stack
        delete[] stack_data;

        n = s.n;
        capacity = s.capacity;
        stack_data = s.stack_data;
        s.stack_data = nullptr;
        return (*this);
    }

    // destructor
    ~Stack() {
        delete[] stack_data;
    }

    // is_empty method
    const bool is_empty(void) const {
        return (n == 0);
    }

    // push method
    void push(const T& x) {
        // check if the size is exceeded and then resize
        if (n == capacity)
            resize(2 * capacity);
        stack_data[n++] = x;
    }

    // pop method
    T& pop() {
        if (is_empty())
            throw std::logic_error("Calling pop on an empty stack");
        // check if we can shrink the stack
        if (n == capacity / 4)
            resize(capacity / 2);

        return (stack_data[--n]);
    }

    // top method
    const T& top() const {
        if (is_empty())
            throw std::logic_error("Calling top on an empty stack");

        return (stack_data[n - 1]);
    }
};

#endif