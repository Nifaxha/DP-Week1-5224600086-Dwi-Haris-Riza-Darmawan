#include <cstdlib>
#include <ctime>

#include "RunSession.h"
#include "RandomInputGenerator.h"   // Modification 1: replaced FixedInputGenerator
#include "BasicScoringRule.h"
#include "BonusRewardRule.h"        // Modification 2: reward != baseScore
#include "ShopSystem.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    RandomInputGenerator generator;  // Modification 1
    BasicScoringRule     scoring;
    BonusRewardRule      reward;     // Modification 2
    ShopSystem           shop;

    RunSession session(&generator, &scoring, &reward, &shop);
    session.StartRun();

    return 0;
}
