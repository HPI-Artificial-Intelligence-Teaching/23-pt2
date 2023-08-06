#include "solver.h"
#include "actionchoice.h"

// returns the expected reward for taking action "action" in a state "state" at time "time"
double Solver::computeExpectedRewardForAction(const int action, const int state, const int time, const double* const futureValues) {
    double expectedReward = 0;
    for (int event = 0; event <= 1; ++event) {
        double eventProbability = env.getEventProbability(event, action, state, time);
        double reward = env.getReward(event, action, state);
        int nextState = env.getNextState(event, state);
        double futureValue = futureValues[nextState];
        expectedReward += eventProbability * (reward + futureValue);
    }
    return expectedReward;
}

// returns the action (and reward) that maximizes the expected reward in a state "state" at time "time"
ActionChoice Solver::computeExpectedRewardForTimeAndState(const int state, const int time, const double* const futureValues) {
    double maxReward = -1000000;
    int bestAction = -1;
    for (int action = env.getMinAction(); action <= env.getMaxAction(); action += env.getActionStep()) {
        double expectedReward = computeExpectedRewardForAction(action, state, time, futureValues);
        if (expectedReward > maxReward) {
            maxReward = expectedReward;
            bestAction = action;
        }
    }
    return ActionChoice(bestAction, maxReward);
}

// returns the final rewards for all states
double* Solver::computeFinalRewards(void) {
    double* finalRewards = new double[env.getMaxState() + 1];
    for (int state = 0; state <= env.getMaxState(); ++state) {
        finalRewards[state] = env.getFinalReward(state);
    }
    return finalRewards;
}

// computes the optimal policy by dynamic programming
int* Solver::computePolicy(void) {
    double* futureValues = computeFinalRewards();
    double* currentValues = new double[env.getMaxState() + 1];
    int* policy = new int[(env.getMaxTime() + 1) * (env.getMaxState() + 1)];
    for (int time = env.getMaxTime(); time >= 0; --time) {
        for (int state = 0; state <= env.getMaxState(); ++state) {
            ActionChoice choice = computeExpectedRewardForTimeAndState(state, time, futureValues);
            policy[time * (env.getMaxState() + 1) + state] = choice.action;
            currentValues[state] = choice.maxReward;
        }
        auto* tmp = futureValues;
        futureValues = currentValues;
        currentValues = tmp;
    }
    delete[] futureValues;
    delete[] currentValues;
    return policy;
}