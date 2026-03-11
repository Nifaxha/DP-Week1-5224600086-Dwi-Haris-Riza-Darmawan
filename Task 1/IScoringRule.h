#ifndef ISCORING_RULE_H
#define ISCORING_RULE_H

#include "TurnInput.h"

class IScoringRule {
public:
    virtual ~IScoringRule() = default;
    virtual int ComputeScore(const TurnInput& input) = 0;
};

#endif
