#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest.h>
#include "../src/environments.h"
#include "../src/solver.h"
#include "../src/solver.cpp"

TEST_CASE("A1: Environment - Event probability Sale-Event")
{
    TicketEnvironment env = TicketEnvironment();

    double eventProb = env.getEventProbability(1, 200, 20, 30);
    
    CHECK(eventProb == .0775);
}

TEST_CASE("A1: Environment - Event probability No-Sale-Event")
{
    TicketEnvironment env = TicketEnvironment();

    double eventProb = env.getEventProbability(0, 200, 20, 30);
    
    CHECK(eventProb == .9225);
}

TEST_CASE("A1: Environment - Reward, Sale-Event")
{
    TicketEnvironment env = TicketEnvironment();

    double reward = env.getReward(1, 200, 5);
    
    CHECK(reward == 200);
}

TEST_CASE("A1: Environment - Reward, No-Sale-Event")
{
    TicketEnvironment env = TicketEnvironment();

    double reward = env.getReward(1, 200, 0);
    
    CHECK(reward == 0);
}


TEST_CASE("A1: Environment - Reward, No tickets left")
{
    TicketEnvironment env = TicketEnvironment();

    double reward = env.getReward(0, 200, 1);
    
    CHECK(reward == 0);
}

TEST_CASE("A1: Environment - Final reward")
{
    TicketEnvironment env = TicketEnvironment();

    double reward = env.getFinalReward(5);
    
    CHECK(reward == -50);
}

TEST_CASE("A2: Solver - Expected reward for a single action over all events")
{
    TicketEnvironment env = TicketEnvironment();
    Solver sol = Solver(env);
    double* futureValues = new double[51];
    for (int i=0;i<=50;++i) {
        futureValues[i] = i;
    }

    double reward = sol.computeExpectedRewardForAction(100, 10, 50, futureValues);
    
    CHECK(reward == doctest::Approx(28.9337));
    delete[] futureValues;
}

TEST_CASE("A2: Solver - Expected reward for a specific state at a specific time")
{
    TicketEnvironment env = TicketEnvironment();
    Solver sol = Solver(env);
    double* futureValues = new double[51];
    for (int i=0;i<=50;++i) {
        futureValues[i] = i;
    }

    ActionChoice choice = sol.computeExpectedRewardForTimeAndState(10, 50, futureValues);
    
    CHECK(choice.action == 200);
    CHECK(choice.maxReward == 35.3725);
    delete[] futureValues;
}

TEST_CASE("A2: Solver - Expected reward for all final states")
{
    TicketEnvironment env = TicketEnvironment();
    Solver sol = Solver(env);

    double* value = sol.computeFinalRewards();
    for (int i=0;i<=50;++i) {
        CHECK(value[i] == (-i*10));
    }
    delete value;
}


TEST_CASE("A2: Solver - Solve everything")
{
    TicketEnvironment env = TicketEnvironment();
    Solver sol = Solver(env);

    int* actions = sol.computePolicy();
    //Time step 0, state 1
    CHECK(actions[1] == 395);
    // Time step 11, state 11
    CHECK(actions[(11*51) + 11] == 350);
    // Time step 199, state 50
    CHECK(actions[(199*51) + 50] == 195);
    // Time step 200, state 50
    CHECK(actions[(200*51) + 50] == 195);

    delete[] actions;
}