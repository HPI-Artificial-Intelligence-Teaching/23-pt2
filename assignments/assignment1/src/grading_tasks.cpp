#include <stdio.h>
#include <fstream>

#include "grading_table.h"
#include "grading_tasks.h"
#include "grading_table.cpp"

void IteratingTaskAgent::performTask() {
    int* result = visitAll();
    for (auto i = 0;i < CONST_MAX_EXPECTED_RESULTS;++i) {
        if (result[i] == 0) {
            break;
        }
        printf("Result %d is %d \n", i, result[i]);
    }
};

int* IteratingTaskAgent::visitAll() {
    int* output = new int[CONST_MAX_EXPECTED_RESULTS] ;
    int i = 0;
    for (GradingTableEntry el : *table) {
        int current = visit(&el);
        if (current > 0) {
            output[i] = current;
            ++i;
        }
    }
    return output;
};

void ReducingTaskAgent::performTask() {
    int result = reduceAll();
    printf("Result %d\n", result);
};

int ReducingTaskAgent::reduceAll() {
    int value = 0;
    for (GradingTableEntry el : *table) {
        value = reduce(&el, value);
    }
    return value;
};

int TaskA::visit(GradingTableEntry *current) {
    return current->points;
};

int TaskB::visit(GradingTableEntry *current) {
    if (current->points < 10) {
        return current->mat_no;
    }
    return 0;
}

int TaskC::reduce(GradingTableEntry *current, int value) {
    return ++value;
}

int TaskD::reduce(GradingTableEntry *current, int value) {
    return (current->points > value) ? current->points : value;
}

int TaskE::reduce(GradingTableEntry *current, int value) {
    return (current->series == 3) ? value + current->points : value;
};