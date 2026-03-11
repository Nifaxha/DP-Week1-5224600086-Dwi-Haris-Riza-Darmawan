#ifndef IINPUT_GENERATOR_H
#define IINPUT_GENERATOR_H

#include "TurnInput.h"

class IInputGenerator {
public:
    virtual ~IInputGenerator() = default;
    virtual TurnInput Generate() = 0;
};

#endif
