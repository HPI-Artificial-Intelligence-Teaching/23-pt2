#ifndef HEADER_H_SOLVER
#define HEADER_H_SOLVER

#include <tuple>

#include "actionchoice.h"
#include "environments.h"

class Solver {
   private:
    TicketEnvironment env;

   public:
    // constructor
    Solver(const TicketEnvironment& ticketEnv) : env(ticketEnv){};

    // returns the expected reward for taking action "action" in a state "state" at time "time"
    double computeExpectedRewardForAction(const int action, const int state, const int time, const double* const futureValues);

    // returns the action (and reward) that maximizes the expected reward in a state "state" at time "time"
    ActionChoice computeExpectedRewardForTimeAndState(const int state, const int time, const double* const futureValues);

    // returns the final rewards for all states
    double* computeFinalRewards(void);

    // computes the optimal policy by dynamic programming
    int* computePolicy(void);
};

#endif