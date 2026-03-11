#ifndef FIXED_INPUT_GENERATOR_H
#define FIXED_INPUT_GENERATOR_H

#include "IInputGenerator.h"

class FixedInputGenerator : public IInputGenerator {
public:
    TurnInput Generate() override {
        return TurnInput{3};
    }
};

#endif
