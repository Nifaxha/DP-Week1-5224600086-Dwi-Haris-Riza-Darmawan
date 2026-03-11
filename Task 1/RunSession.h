#ifndef RUN_SESSION_H
#define RUN_SESSION_H

#include "IInputGenerator.h"
#include "IScoringRule.h"
#include "IRewardRule.h"
#include "ShopSystem.h"

class RunSession {
public:
    RunSession(IInputGenerator* generator,
               IScoringRule* scoring,
               IRewardRule* reward,
               ShopSystem* shop);

    void StartRun();

private:
    void RunRound(int round);

    IInputGenerator* generator_;
    IScoringRule*    scoring_;
    IRewardRule*     reward_;
    ShopSystem*      shop_;

    int money_;
    static const int TOTAL_ROUNDS = 3;
};

#endif
