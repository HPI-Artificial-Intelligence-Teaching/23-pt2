#ifndef __LIST_STACK_H__
#define __LIST_STACK_H__

#include <stdexcept>

// Implements a stack with a linked list
template <typename T>
class Stack
{
    // stores the stack elements as a linked list
    struct List
    {
        T data;
        List *next;
    } *head;
    int capacity = 0;

    // copys an existing list
    const List *deep_copy_list(const List *new_head)
    {
        if (new_head)
        {
            auto tail = deep_copy_list(new_head->next);
            return (new List(new_head->data, tail));
        }

        return (nullptr);
    }

    // frees the list and sets the head to NULL
    void free_list()
    {
        while (head)
        {
            List *tmp = head->next;
            delete head;
            head = tmp;
        }
        return;
    }

public:
    // constructor
    Stack() : head(nullptr) {}

    // copy constructor
    Stack(const Stack &s) { head = deep_copy_list(s.head); }

    // move constructor
    Stack(Stack &&s) : head(s.head) { s.head = nullptr; }

    // copy assignment
    Stack &operator=(const Stack &s)
    {
        // free the existing stack
        free_list();
        // copy the stack passed in
        head = deep_copy_list(s.head);
        return (*this);
    }

    // move assignment
    Stack &operator=(Stack &&s)
    {
        // free the existing stack
        free_list();

        head = s.head;
        s.head = nullptr;
        return (*this);
    }

    // destructor
    ~Stack()
    {
        free_list();
    }

    // is_empty method
    const bool is_empty(void)
    {
        return (head == nullptr);
    }

    const int length(void)
    {
        return capacity;
    }

    // push method
    void push(const T &x)
    {
        List *new_head = new List;
        new_head->data = x;
        new_head->next = head;
        head = new_head;
        capacity++;
    }

    // pop method
    T pop()
    {
        if (is_empty())
            throw std::logic_error("Calling pop on an empty stack");

        List *tmp = head->next;
        T ret_value = head->data;
        delete head;
        head = tmp;
        capacity--;

        return (ret_value);
    }

    // top method
    const T &top()
    {
        if (is_empty())
            throw std::logic_error("Calling top on an empty stack");

        return (head->data);
    }
};

#endif
