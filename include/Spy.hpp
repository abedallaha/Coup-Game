#ifndef SPY_HPP
#define SPY_HPP

#include "Player.hpp"

namespace coup {
    class Spy : public Player {
    public:
        Spy(Game& game, const std::string& name);
        ~Spy() override = default;

        // Spy-specific actions
        void view_coins(Player& target); // View another player's coins
        void prevent_arrest(Player& target); // Prevent arrest on target
        
        // Virtual method implementations
        void undo(Player& target) override;
        bool can_block(const Player& target) const override;
        std::string role() const override { return "Spy"; }
    };
}

#endif // SPY_HPP 