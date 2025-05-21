#ifndef GOVERNOR_HPP
#define GOVERNOR_HPP

#include "Player.hpp"

namespace coup {
    class Governor : public Player {
    public:
        Governor(Game& game, const std::string& name);
        ~Governor() override = default;

        // Governor-specific actions
        void tax(); // Override to get 3 coins instead of 2
        
        // Virtual method implementations
        void undo(Player& target) override;
        bool can_block(const Player& target) const override;
        std::string role() const override { return "Governor"; }
    };
}

#endif // GOVERNOR_HPP 