#include <iostream>
#include "RunSession.h"

RunSession::RunSession(IInputGenerator* generator,
                       IScoringRule* scoring,
                       IRewardRule* reward,
                       ShopSystem* shop)
    : generator_(generator),
      scoring_(scoring),
      reward_(reward),
      shop_(shop),
      money_(0) {}

void RunSession::StartRun() {
    std::cout << "=== RUN START ===\n\n";

    for (int round = 1; round <= TOTAL_ROUNDS; round++) {
        RunRound(round);
    }

    std::cout << "=== RUN END ===\n";
    std::cout << "Final money: " << money_ << "\n";
}

void RunSession::RunRound(int round) {
    std::cout << "Round " << round << "\n";

    // Phase 1: Generate input
    TurnInput input = generator_->Generate();
    std::cout << "[PLAY] input generated: " << input.value << "\n";

    // Phase 2: Compute base score
    int baseScore = scoring_->ComputeScore(input);
    std::cout << "[SCORE] base score: " << baseScore << "\n";

    // Phase 3: Compute reward
    int gain = reward_->ComputeReward(baseScore, round);
    std::cout << "[REWARD] gain: " << gain;

    // Phase 4: Update money
    money_ += gain;
    std::cout << " | money: " << money_ << "\n";

    // Phase 5: Shop phase
    shop_->Offer(money_);

    // Phase 6: Advance round
    std::cout << "\n";
}
