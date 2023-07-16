#ifndef __LIST_SET_H__
#define __LIST_SET_H__

#include <stdexcept>
#include <stdio.h>

template <typename T>
class Set
{
    struct List
    {
        T data;
        List *next;
    } *head;
    int cardinality = 0;

    // copys an existing list
    void deep_copy_list(List *new_head)
    {
        if (new_head)
        {
            head = new List;
            head->data = new_head->data;
            List *tmp = new_head;
            List *tmp2 = head;
            while (tmp->next)
            {
                tmp2->next = new List;
                // tmp2->next->data;
                tmp = tmp->next;
                tmp2 = tmp2->next;
            }
            tmp2->next = nullptr;
        }
        else
            head = new_head;
        return;
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
    Set() : head(nullptr){};
    // destructor
    ~Set()
    {
        free_list();
    }
    // we need to define copy constructor and assignment as well see Wikipedia / C++ / Rule of Three
    // copy constructor
    Set(const Set &s)
    {
        deep_copy_list(s.head);
    }
    // copy assignment
    Set &operator=(const Set &s)
    {
        // free the existing Set
        free_list();
        // copy the Set passed in
        deep_copy_list(s.head);
        return (*this);
    }
    int size() const
    {
        return cardinality;
    }
    T operator[](int i) const
    {
        if (i >= cardinality)
        {
            throw std::out_of_range("Index out of range");
        }
        List *tmp = head;
        for (int j = 0; j < i; j++)
        {
            tmp = tmp->next;
        }
        return tmp->data;
    }
    bool operator==(const Set &s) const
    {
        if (cardinality != s.size())
        {
            return false;
        }
        for (int i = 0; i < cardinality; i++)
        {
            if (!s.contains((*this)[i]))
            {
                return false;
            }
        }
        return true;
    }
    Set<T> add(const T &x)
    {
        if (!contains(x))
        {
            List *new_head = new List;
            new_head->data = x;
            new_head->next = head;
            head = new_head;
            cardinality++;
        }
        return *this;
    }
    Set<T> remove(const T &x)
    {
        if (contains(x))
        {
            List *tmp = head;
            List *prev = nullptr;
            while (tmp)
            {
                if (tmp->data == x)
                {
                    if (prev)
                    {
                        prev->next = tmp->next;
                    }
                    else
                    {
                        head = tmp->next;
                    }
                    delete tmp;
                    break;
                }
                prev = tmp;
                tmp = tmp->next;
            }
            cardinality--;
        }
        return *this;
    }
    bool contains(const T &x) const
    {
        List *tmp = head;
        while (tmp)
        {
            if (tmp->data == x)
            {
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }
    void show()
    {
        List *tmp = head;
        printf("Set\n");
        printf("----------\n");
        while (tmp)
        {
            printf("%s ", tmp->data);
            tmp = tmp->next;
        }
        printf("\n----------\n");
    }
};
#endif