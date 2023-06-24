/*****************************************************************************
 *
 *  A generic stack using a singly linked list.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __STACK_H__
#define __STACK_H__

#include <iterator>
#include <stdexcept>

using namespace std;

// Implements a stack with a linked list
template <typename T>
class Stack {
    // stores the stack elements as a linked list
    struct List {
        T data;
        List* next;
    }* head;

    // copys an existing list
    List* deep_copy_list(List* new_head) {
        if (new_head) {
            auto tail = deep_copy_list(new_head->next);
            List* head = new List();
            head->data = new_head->data;
            head->next = tail;
            return (head);
        }

        return (nullptr);
    }

    // frees the list and sets the head to NULL
    void free_list() {
        while (head) {
            List* tmp = head->next;
            delete head;
            head = tmp;
        }
        return;
    }

   public:
    // constructor
    Stack() : head(nullptr) {}

    // copy constructor
    Stack(const Stack& s) { head = deep_copy_list(s.head); }

    // move constructor
    Stack(Stack&& s) : head(s.head) { s.head = nullptr; }

    // copy assignment
    Stack& operator=(const Stack& s) {
        // free the existing stack
        free_list();
        // copy the stack passed in
        head = deep_copy_list(s.head);
        return (*this);
    }

    // move assignment
    Stack& operator=(Stack&& s) {
        // free the existing stack
        free_list();

        head = s.head;
        s.head = nullptr;
        return (*this);
    }

    // destructor
    ~Stack() {
        free_list();
    }

    // is_empty method
    const bool is_empty() const {
        return (head == nullptr);
    }

    // push method
    void push(const T& x) {
        List* new_head = new List();
        new_head->data = x;
        new_head->next = head;
        head = new_head;
    }

    // pop method
    T pop() {
        if (is_empty())
            throw logic_error("Calling pop on an empty stack");

        List* tmp = head->next;
        T ret_value = head->data;
        delete head;
        head = tmp;

        return (ret_value);
    }

    // top method
    const T& top() const {
        if (is_empty())
            throw logic_error("Calling top on an empty stack");

        return (head->data);
    }

    // adding an iterator over the items of the stack
    struct Iterator {
        using iterator_category = forward_iterator_tag;
        using difference_time = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        reference operator*() const { return m_ptr->data; };
        pointer operator->() { return &m_ptr->data; };
        Iterator& operator++() {
            m_ptr = m_ptr->next;
            return *this;
        };
        Iterator operator++(int) {
            Iterator tmp = *this;
            m_ptr = m_ptr->next;
            return tmp;
        };

        friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

        Iterator(List* ptr) : m_ptr(ptr) {}

       private:
        List* m_ptr;
    };
    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
};

#endif
