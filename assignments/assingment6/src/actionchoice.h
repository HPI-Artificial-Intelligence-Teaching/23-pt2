#ifndef HEADER_H_ACTIONCHOICE
#define HEADER_H_ACTIONCHOICE

struct ActionChoice {
    int action;
    double maxReward;
    ActionChoice(int action, double maxReward) : action(action), maxReward(maxReward){};
};

#endif