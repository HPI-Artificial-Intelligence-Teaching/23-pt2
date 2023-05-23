#ifndef GRADING_TABLE_H
#define GRADING_TABLE_H

#include <stdint.h>
#include <stdio.h>
#include <fstream>

class TaskAgent;

class GradingTableEntry {
    public:
        uint32_t mat_no;              /* matriculation number */
        uint16_t series;              /* series */
        uint16_t points;              /* points scored */
        GradingTableEntry *next;
};

class GradingTable {
    public: 
        GradingTableEntry *g_head, *g_tail;
        struct Iterator {
            using iterator_category = std::forward_iterator_tag;
            using difference_time = std::ptrdiff_t;
            using value_type = GradingTableEntry;
            using pointer = GradingTableEntry*;
            using reference = GradingTableEntry&;

            reference operator*() const { return *m_ptr; };
            pointer operator->() { return m_ptr; };
            Iterator& operator++() { m_ptr = m_ptr->next; return *this; };
            Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; };

            friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }; 

            Iterator(pointer ptr) : m_ptr(ptr) {}

            private:
                pointer m_ptr;
        };
        Iterator begin() { return Iterator(g_head); };
        Iterator end() { return Iterator(NULL); };
        GradingTable(std::ifstream &fp);
        ~GradingTable();
};

#endif /* GRADING_TABLE */