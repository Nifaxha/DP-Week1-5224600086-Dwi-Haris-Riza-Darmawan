#ifndef SHOP_SYSTEM_H
#define SHOP_SYSTEM_H

#include <iostream>

class ShopSystem {
public:
    void Offer(int& money) {
        int cost = 2;
        std::cout << "[SHOP] offered: Bonus(+2) cost " << cost << "\n";
        if (money >= cost) {
            // Auto-skip for simplicity (no user input)
            std::cout << "[SHOP] skipped\n";
        } else {
            std::cout << "[SHOP] not enough money, skipped\n";
        }
    }
};

#endif
