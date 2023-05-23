#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "../src/grading_table.h"
#include "../src/grading_tasks.h"
#include "../src/grading_tasks.cpp"
#define DB_FILE "../src/grading_results.db"

TEST_CASE("A1: GradingTable - Loading")
{
    std::ifstream fp;
    fp.open(DB_FILE);

    GradingTable *table = new GradingTable(fp);
    
    GradingTableEntry* current = table->g_head;
    int i = 0;
    while (current != nullptr) {
        ++i;
        current = current->next;
    }

    CHECK(i == 40);
    fp.close();
}

TEST_CASE("A1: GradingTable - Iterator")
{
    std::ifstream fp;
    fp.open(DB_FILE);

    GradingTable *table = new GradingTable(fp);

    int i = 0;

    for (GradingTableEntry el : *table) {
        ++i;
    }

    CHECK(i == 40);
    fp.close();
}

TEST_CASE("A2: a)")
{
    std::ifstream fp;
    fp.open(DB_FILE);

    GradingTable *table = new GradingTable(fp);
    IteratingTaskAgent *agent;

    agent = new TaskA(table);
    int* result = agent->visitAll();
    int target[39] = {12, 11, 18, 12, 11, 15, 18, 13, 12, 11, 10, 11, 13, 11, 20, 19, 13, 17, 11, 10, 18, 20, 15, 21, 17, 14, 7, 20, 11, 17, 13, 12, 23, 10, 20, 15, 20, 16, 18};
    for (int i=0;i<39;i++) {
        CHECK(result[i] == target[i]);
    }
    fp.close();
}

TEST_CASE("A2: b)")
{
    std::ifstream fp;
    fp.open(DB_FILE);

    GradingTable *table = new GradingTable(fp);
    IteratingTaskAgent *agent;

    agent = new TaskB(table);
    int* result = agent->visitAll();
    int target[2] = {4211, 2342};
    for (int i=0;i<2;i++) {
        CHECK(result[i] == target[i]);
    }
    for (int i=2;i<CONST_MAX_EXPECTED_RESULTS;i++) {
        CHECK(result[i] == 0);
    }
    fp.close();
}

TEST_CASE("A2: c)")
{
    std::ifstream fp;
    fp.open(DB_FILE);

    GradingTable *table = new GradingTable(fp);
    ReducingTaskAgent *agent;

    agent = new TaskC(table);
    int result = agent->reduceAll();
    CHECK(result == 40);
    fp.close();
}

TEST_CASE("A2: d)")
{
    std::ifstream fp;
    fp.open(DB_FILE);

    GradingTable *table = new GradingTable(fp);
    ReducingTaskAgent *agent;

    agent = new TaskD(table);
    int result = agent->reduceAll();
    CHECK(result == 23);
    fp.close();
}

TEST_CASE("A2: e)")
{
    std::ifstream fp;
    fp.open(DB_FILE);

    GradingTable *table = new GradingTable(fp);
    ReducingTaskAgent *agent;

    agent = new TaskE(table);
    int result = agent->reduceAll();
    CHECK(result == 104);
    fp.close();
}