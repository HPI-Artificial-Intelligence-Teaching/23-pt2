/******************************************************************************
 *
 *  A generic queue using a fixed-size array.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdexcept>

// Implements a queue with a fixed size array of values 
template <typename T>
class Queue {
    T* queue_data;
    int l, u;
    int capacity;

   public:
    // constructor
    Queue(int cap = 100) : l(0), u(0), capacity(cap) {
        queue_data = new T[capacity];
    }
    // copy constructor
    Queue(const Queue& q) : l(q.l), u(q.u), capacity(q.capacity) {
        queue_data = new T[capacity];
        for (auto i = 0; i < q.capacity; i++)
            queue_data[i] = q.queue_data[i];
    }

    // move constructor
    Queue(Queue&& q) : l(q.l), u(q.u), capacity(q.capacity) {
        queue_data = q.queue_data;
        q.queue_data = nullptr;
    }

    // copy assignment
    Queue& operator=(const Queue& q) {
        // free the existing queue
        delete[] queue_data;

        // copy the queue passed in
        l = q.l;
        u = q.u;
        capacity = q.capacity;
        queue_data = new T[capacity];
        for (auto i = 0; i < q.capacity; i++)
            queue_data[i] = q.queue_data[i];
        return (*this);
    }

    // move assignment
    Queue& operator=(Queue&& q) {
        // free the existing queue
        delete[] queue_data;

        l = q.l;
        u = q.u;
        capacity = q.capacity;
        queue_data = q.queue_data;
        q.queue_data = nullptr;
        return (*this);
    }
    // destructor
    ~Queue() {
        delete[] queue_data;
    }

    // is_empty method
    const bool is_empty(void) const {
        return (l == u);
    }
    // enqueue method
    void enqueue(const T& x) {
        // check if the size is exceeded and then resize
        if (((u + capacity) - l) % capacity == capacity - 1) {
            throw std::length_error("Capacity of the queue is exceeded");
        }
        queue_data[u] = x;
        u = (u + 1) % capacity;
    }

    // dequeue method
    T& dequeue() {
        if (is_empty())
            throw std::logic_error("Dequeuing from an empty queue");

        auto old_l = l;
        l = (l + 1) % capacity;
        return (queue_data[old_l]);
    }

    // front method
    const T& front() const {
        if (is_empty())
            throw std::logic_error("Fronting an empty queue");

        return (queue_data[l]);
    }
};

#endif