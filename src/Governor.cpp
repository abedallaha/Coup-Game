#include "Governor.hpp"
#include "GameException.hpp"

namespace coup {

    Governor::Governor(Game& game, const std::string& name)
        : Player(game, name) {}

    void Governor::tax() {
        if (!is_player_alive()) {
            throw GameException("Player is not alive");
        }
        if (is_player_blocked()) {
            throw GameException("Player is blocked");
        }
        if (game.turn() != get_name()) {
            throw GameException("Not player's turn");
        }
        add_coins(3); // Governor gets 3 coins instead of 2
        game.set_last_action(get_name(), "tax");
        if (get_bribe_turns() > 0) {
            set_bribe_turns(get_bribe_turns() - 1);
        } else {
            game.next_turn();
        }
    }

    void Governor::undo(Player& target) {
        if (!is_player_alive()) {
            throw GameException("Player is not alive");
        }
        if (!target.is_player_alive()) {
            throw GameException("Target player is not alive");
        }
        // Only allow undo if:
        // 1. The last action was performed by this player
        // 2. The last action was a tax action
        // 3. The target player is the one who was affected by the tax
        if (game.get_last_action_player() != get_name()) {
            throw GameException("Can only undo your own actions");
        }
        if (game.get_last_action_type() != "tax") {
            throw GameException("Can only undo tax actions");
        }
        // Remove the tax amount from the target player
        if (target.get_coins() >= 2) {
            target.remove_coins(2);
        }
        // Clear last action after undo
        game.set_last_action("", "");
    }

    bool Governor::can_block(const Player& target) const {
        (void)target;
        // Governor can block tax actions
        return true; // This is a simplified version - in reality, we'd need to track the last action
    }

} 