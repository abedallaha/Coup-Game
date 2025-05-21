#ifndef GENERAL_HPP
#define GENERAL_HPP

#include "Player.hpp"

namespace coup {
    class General : public Player {
    public:
        General(Game& game, const std::string& name);
        ~General() override = default;

        // General-specific actions
        void prevent_coup(Player& target); // Prevent coup against target
        
        // Virtual method implementations
        void undo(Player& target) override;
        bool can_block(const Player& target) const override;
        std::string role() const override { return "General"; }
    };
}

#endif // GENERAL_HPP 