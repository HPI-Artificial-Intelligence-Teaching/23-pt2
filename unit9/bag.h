/******************************************************************************
 *
 *  A generic bag or multiset, implemented using a singly linked list.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __BAG_H__
#define __BAG_H__

#include <cstddef>
#include <iterator>

using namespace std;

// Implements a generic bag or multiset, implemented using a singly linked list.
template <typename T>
class Bag {
    // stores the elements as a linked list
    struct List {
        T item;
        List* next;

        // constructor with values
        List(const T& _item, List* _next = nullptr) : item(_item), next(_next) {}
    }* head;
    int n;  // number of elements in the bag

    // copys an existing list
    const List* deep_copy_list(const List* new_head) {
        if (new_head) {
            auto tail = deep_copy_list(new_head->next);
            return (new List(new_head->data, tail));
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
        n = 0;
        return;
    }

   public:
    // constructor
    Bag() : head(nullptr), n(0) {}

    // copy constructor
    Bag(const Bag& b) {
        head = deep_copy_list(b.head);
        n = b.n;
    }

    // move constructor
    Bag(Bag&& b) : head(b.head), n(b.n) {
        b.head = nullptr;
        b.n = 0;
    }

    // copy assignment
    Bag& operator=(const Bag& b) {
        // free the existing bag
        free_list();

        // copy the bag passed in
        head = deep_copy_list(b.head);
        n = b.n;
        return (*this);
    }

    // move assignment
    Bag& operator=(Bag&& b) {
        // free the existing bag
        free_list();

        head = b.head;
        n = b.n;
        b.head = nullptr;
        b.n = 0;
        return (*this);
    }

    // destructor
    ~Bag() {
        free_list();
    }

    // is_empty method
    bool is_empty() const {
        return (head == nullptr);
    }

    // size method
    int size() const {
        return (n);
    }

    // adds the item to the bag
    void add(const T& item) {
        head = new List(item, head);
        n++;
        return;
    }

    // adding an iterator over the items of the bag
    struct Iterator {
        using iterator_category = forward_iterator_tag;
        using difference_time = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        reference operator*() const { return m_ptr->item; };
        pointer operator->() { return &m_ptr->item; };
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