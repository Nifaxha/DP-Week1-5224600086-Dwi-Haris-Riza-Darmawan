#ifndef BASIC_SCORING_RULE_H
#define BASIC_SCORING_RULE_H

#include "IScoringRule.h"

class BasicScoringRule : public IScoringRule {
public:
    int ComputeScore(const TurnInput& input) override {
        return input.value;
    }
};

#endif
