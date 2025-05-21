#include "General.hpp"
#include "GameException.hpp"

namespace coup {

    General::General(Game& game, const std::string& name)
        : Player(game, name) {}

    void General::prevent_coup(Player& target) {
        if (!is_player_alive()) {
            throw GameException("Player is not alive");
        }
        if (is_player_blocked()) {
            throw GameException("Player is blocked");
        }
        if (game.turn() != get_name()) {
            throw GameException("Not player's turn");
        }
        if (get_coins() < 5) {
            throw GameException("Not enough coins to prevent coup");
        }
        if (!target.is_player_alive()) {
            throw GameException("Target player is not alive");
        }
        remove_coins(5);
        // Prevent coup is passive, doesn't count as a turn
    }

    void General::undo(Player& target) {
        if (!is_player_alive()) {
            throw GameException("Player is not alive");
        }
        if (!target.is_player_alive()) {
            throw GameException("Target player is not alive");
        }
        // General can't undo any actions
        throw GameException("General cannot undo actions");
    }

    bool General::can_block(const Player& target) const {
        (void)target;
        // General can block only coup actions
        if (game.get_last_action_type() == "coup") {
            return true;
        }
        return false;
    }

} 