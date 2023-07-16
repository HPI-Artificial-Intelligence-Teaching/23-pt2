#ifndef __LIST_QUEUE_H__
#define __LIST_QUEUE_H__

#include <stdexcept>

// Implements a queue with a linked list
template <typename T>
class Queue
{
    // stores the queue elements as a linked list
    struct List
    {
        T data;
        List *next;
    } *head, *last;

    // copys an existing list
    const List *deep_copy_list(const List *new_head, const List *new_last)
    {
        // set the last pointer
        if (new_head == new_last)
            last = head;

        // copy the list by first deep-copying the tail and then linking it
        if (new_head)
        {
            auto tail = deep_copy_list(new_head->next, new_last);
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
        last = nullptr;
        return;
    }

public:
    // constructor
    Queue() : head(nullptr), last(nullptr) {}

    // copy constructor
    Queue(const Queue &q) { head = deep_copy_list(q.head, q.last); }

    // move constructor
    Queue(Queue &&q) : head(q.head), last(q.last)
    {
        q.head = nullptr;
        q.last = nullptr;
    }

    // copy assignment
    Queue &operator=(const Queue &q)
    {
        // free the existing queue
        free_list();
        // copy the queue passed in
        head = deep_copy_list(q.head, q.last);
        return (*this);
    }

    // move assignment
    Queue &operator=(Queue &&q)
    {
        // free the existing stack
        free_list();

        head = q.head;
        last = q.last;
        q.head = nullptr;
        q.last = nullptr;
        return (*this);
    }

    // destructor
    ~Queue()
    {
        free_list();
    }

    // is_empty method
    const bool is_empty(void)
    {
        return (head == nullptr);
    }

    // enqueue method
    void enqueue(const T &x)
    {
        List *old_last = last;
        last = new List;
        last->data = x;
        last->next = nullptr;
        if (is_empty())
            head = last;
        else
            old_last->next = last;
    }

    // dequeue method
    T dequeue()
    {
        if (is_empty())
            throw std::logic_error("Calling dequeue on an empty queue");

        List *tmp = head->next;
        T ret_value = head->data;
        delete head;
        head = tmp;
        if (is_empty())
            last = nullptr;

        return (ret_value);
    }

    // front method
    const T &front()
    {
        if (is_empty())
            throw std::logic_error("Calling front on an empty queue");

        return (head->data);
    }
};

#endif
