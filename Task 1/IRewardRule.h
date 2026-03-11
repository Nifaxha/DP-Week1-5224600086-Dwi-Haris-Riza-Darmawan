#ifndef IREWARD_RULE_H
#define IREWARD_RULE_H

class IRewardRule {
public:
    virtual ~IRewardRule() = default;
    virtual int ComputeReward(int baseScore, int round) = 0;
};

#endif
