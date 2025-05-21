#ifndef JUDGE_HPP
#define JUDGE_HPP

#include "Player.hpp"

namespace coup {
    class Judge : public Player {
    public:
        Judge(Game& game, const std::string& name);
        ~Judge() override = default;

        // Judge-specific actions
        void cancel_bribe(Player& target); // Cancel bribe action
        
        // Virtual method implementations
        void undo(Player& target) override;
        bool can_block(const Player& target) const override;
        std::string role() const override { return "Judge"; }
    };
}

#endif // JUDGE_HPP 