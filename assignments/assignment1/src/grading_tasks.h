#ifndef GRADING_TASKS_H
#define GRADING_TASKS_H

#include <stdint.h>
#include <stdio.h>
#include <fstream>
#include "grading_table.h"

const int CONST_MAX_EXPECTED_RESULTS = 39;

class TaskAgent {
    protected:
        GradingTable* table;
    public:
        virtual void performTask() {};
        TaskAgent(GradingTable* table): table{table} {};
        ~TaskAgent() {};
};

class IteratingTaskAgent: public TaskAgent {  
    using TaskAgent::TaskAgent;
    public:
        void performTask() override;
        virtual int visit(GradingTableEntry *current) = 0;
        int* visitAll();
};

class ReducingTaskAgent: public TaskAgent {
    using TaskAgent::TaskAgent;
    public:
        void performTask() override;
        virtual int reduce(GradingTableEntry *current, int value) = 0;
        int reduceAll();
};

class TaskA: public IteratingTaskAgent {
    using IteratingTaskAgent::IteratingTaskAgent;
    public:
        int visit(GradingTableEntry *current) override;
};

class TaskB: public IteratingTaskAgent {
    using IteratingTaskAgent::IteratingTaskAgent;
    public:
        int visit(GradingTableEntry *current) override;
};

class TaskC: public ReducingTaskAgent {
    using ReducingTaskAgent::ReducingTaskAgent;
    public:
        int reduce(GradingTableEntry *current, int value) override;
};

class TaskD: public ReducingTaskAgent {
    using ReducingTaskAgent::ReducingTaskAgent;
    public:
        int reduce(GradingTableEntry *current, int value) override;
};

class TaskE: public ReducingTaskAgent {
    using ReducingTaskAgent::ReducingTaskAgent;
    public:
        int reduce(GradingTableEntry *current, int value) override;
};

#endif /* GRADING_TASKS */