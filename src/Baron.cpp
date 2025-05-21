#include "Baron.hpp"
#include "GameException.hpp"

namespace coup {

    Baron::Baron(Game& game, const std::string& name)
        : Player(game, name) {}

    void Baron::invest() {
        if (!is_player_alive()) {
            throw GameException("Player is not alive");
        }
        if (is_player_blocked()) {
            throw GameException("Player is blocked");
        }
        if (game.turn() != get_name()) {
            throw GameException("Not player's turn");
        }
        if (get_coins() != 3) {
            throw GameException("Baron must have exactly 3 coins to invest");
        }
        remove_coins(3);
        add_coins(6);
        game.set_last_action(get_name(), "invest");
        if (get_bribe_turns() > 0) {
            set_bribe_turns(get_bribe_turns() - 1);
        } else {
            game.next_turn();
        }
    }

    void Baron::undo(Player& target) {
        if (!is_player_alive()) {
            throw GameException("Player is not alive");
        }
        if (!target.is_player_alive()) {
            throw GameException("Target player is not alive");
        }
        // Baron can't undo any actions
        throw GameException("Baron cannot undo actions");
    }

    bool Baron::can_block(const Player& target) const {
        (void)target;
        // Baron can't block any actions
        return false;
    }

} 