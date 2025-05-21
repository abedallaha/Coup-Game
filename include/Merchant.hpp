#ifndef MERCHANT_HPP
#define MERCHANT_HPP

#include "Player.hpp"

namespace coup {
    class Merchant : public Player {
    public:
        Merchant(Game& game, const std::string& name);
        ~Merchant() override = default;

        // Merchant-specific actions
        void collect_bonus(); // Collect bonus coin if has 3+ coins
        
        // Virtual method implementations
        void undo(Player& target) override;
        bool can_block(const Player& target) const override;
        std::string role() const override { return "Merchant"; }
    };
}

#endif // MERCHANT_HPP 