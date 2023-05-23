#include "grading_table.h"

#include <stdlib.h>
#include <fstream>
#include <iostream>


GradingTable::GradingTable(std::ifstream &fp) {
    GradingTableEntry *head = NULL;
    if (fp.is_open() && !fp.eof()) {
        while (1) {
            GradingTableEntry *new_entry = new GradingTableEntry();

            fp.read(reinterpret_cast<char *>(&new_entry->mat_no), sizeof(new_entry->mat_no));
            if (fp.eof()) {
                delete new_entry;
                g_head = head;
                break;
            }
            fp.read(reinterpret_cast<char *>(&new_entry->series), sizeof(new_entry->series));
            fp.read(reinterpret_cast<char *>(&new_entry->points), sizeof(new_entry->points));

            new_entry->next = NULL;
            if (!head) {
                head = g_tail = new_entry;
            } else {
                g_tail->next = new_entry;
                g_tail = new_entry;
            }
        }
    }
}

GradingTable::~GradingTable() {
    GradingTableEntry *head = g_head;
    while (head) {
        GradingTableEntry *tmp = head->next;
        delete head;
        head = tmp;
    }
}