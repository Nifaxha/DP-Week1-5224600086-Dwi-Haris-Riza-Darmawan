#ifndef BONUS_REWARD_RULE_H
#define BONUS_REWARD_RULE_H

#include "IRewardRule.h"

// Modification 2: reward = baseScore + 2 on odd rounds,
//                 reward = baseScore * 2 on even rounds
class BonusRewardRule : public IRewardRule {
public:
    int ComputeReward(int baseScore, int round) override {
        if (round % 2 == 0) {
            return baseScore * 2;
        } else {
            return baseScore + 2;
        }
    }
};

#endif
