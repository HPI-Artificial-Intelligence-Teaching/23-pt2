#include "grading_tasks.h"

/* main entry point for the program */
int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s (a|b|c|d|e) [filename]\n", argv[0]);
        return 1;
    }

    char task = argv[1][0];
    std::ifstream fp;
    fp.open(argv[2]);

    GradingTable *table = new GradingTable(fp);
    TaskAgent *agent;


    switch (task) {
        case 'a':
            agent = new TaskA(table);
            break;
        case 'b':
            agent = new TaskB(table);
            break;
        case 'c':
            agent = new TaskC(table);
            break;
        case 'd':
            agent = new TaskD(table);
            break;
        case 'e':
            agent = new TaskE(table);
            break;
        default:
            fprintf(stderr, "Unknown task: %c\n", task);
            return 2;
    }
    agent->performTask();
    delete table;
    delete agent;

    return 0;
}