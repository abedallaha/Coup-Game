#include "Spy.hpp"
#include "GameException.hpp"

namespace coup {

    Spy::Spy(Game& game, const std::string& name)
        : Player(game, name) {}

    void Spy::view_coins(Player& target) {
        if (!is_player_alive()) {
            throw GameException("Player is not alive");
        }
        if (!target.is_player_alive()) {
            throw GameException("Target player is not alive");
        }
        // View coins doesn't count as a turn
        // Just return the number of coins
        target.get_coins();
    }

    void Spy::prevent_arrest(Player& target) {
        if (!is_player_alive()) {
            throw GameException("Player is not alive");
        }
        if (!target.is_player_alive()) {
            throw GameException("Target player is not alive");
        }
        // Prevent arrest doesn't count as a turn
        target.set_blocked(true);
    }

    void Spy::undo(Player& target) {
        if (!is_player_alive()) {
            throw GameException("Player is not alive");
        }
        if (!target.is_player_alive()) {
            throw GameException("Target player is not alive");
        }
        // Spy can't undo any actions
        throw GameException("Spy cannot undo actions");
    }

    bool Spy::can_block(const Player& target) const {
        (void)target;
        // Spy can block arrest actions
        return true; // This is a simplified version - in reality, we'd need to track the last action
    }

} 