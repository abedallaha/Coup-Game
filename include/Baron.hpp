#ifndef BARON_HPP
#define BARON_HPP

#include "Player.hpp"

namespace coup {
    class Baron : public Player {
    public:
        Baron(Game& game, const std::string& name);
        ~Baron() override = default;

        // Baron-specific actions
        void invest(); // Invest 3 coins to get 6 coins
        
        // Virtual method implementations
        void undo(Player& target) override;
        bool can_block(const Player& target) const override;
        std::string role() const override { return "Baron"; }
    };
}

#endif // BARON_HPP 