#include "Judge.hpp"
#include "GameException.hpp"

namespace coup {

    Judge::Judge(Game& game, const std::string& name)
        : Player(game, name) {}

    void Judge::cancel_bribe(Player& target) {
        if (!is_player_alive()) {
            throw GameException("Player is not alive");
        }
        if (!target.is_player_alive()) {
            throw GameException("Target player is not alive");
        }
        // Cancel bribe is passive, doesn't count as a turn
        // Target loses 4 coins
        if (target.get_coins() >= 4) {
            target.remove_coins(4);
        }
    }

    void Judge::undo(Player& target) {
        if (!is_player_alive()) {
            throw GameException("Player is not alive");
        }
        if (!target.is_player_alive()) {
            throw GameException("Target player is not alive");
        }
        // Only allow undo if:
        // 1. The last action was performed by this player
        // 2. The last action was a bribe action
        // 3. The target player is the one who was affected by the bribe
        if (game.get_last_action_player() != get_name()) {
            throw GameException("Can only undo your own actions");
        }
        if (game.get_last_action_type() != "bribe") {
            throw GameException("Can only undo bribe actions");
        }
        // Return the bribe amount to the target player
        target.add_coins(4);
        // Clear last action after undo
        game.set_last_action("", "");
    }

    bool Judge::can_block(const Player& target) const {
        (void)target;
        // Judge can block bribe actions
        return true; // This is a simplified version - in reality, we'd need to track the last action
    }

} 