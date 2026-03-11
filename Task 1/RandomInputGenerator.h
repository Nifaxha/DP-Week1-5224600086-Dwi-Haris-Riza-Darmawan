#ifndef RANDOM_INPUT_GENERATOR_H
#define RANDOM_INPUT_GENERATOR_H

#include "IInputGenerator.h"
#include <cstdlib>

class RandomInputGenerator : public IInputGenerator {
public:
    TurnInput Generate() override {
        int value = (std::rand() % 10) + 1; // 1 to 10
        return TurnInput{value};
    }
};

#endif
