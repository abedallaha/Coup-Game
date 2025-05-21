#include "Merchant.hpp"
#include "GameException.hpp"

namespace coup {

    Merchant::Merchant(Game& game, const std::string& name)
        : Player(game, name) {}

    void Merchant::collect_bonus() {
        if (!is_player_alive()) {
            throw GameException("Player is not alive");
        }
        if (is_player_blocked()) {
            throw GameException("Player is blocked");
        }
        if (game.turn() != get_name()) {
            throw GameException("Not player's turn");
        }
        if (get_coins() >= 3) {
            add_coins(1); // Get free coin if has 3+ coins
        }
        game.set_last_action(get_name(), "collect_bonus");
        if (get_bribe_turns() > 0) {
            set_bribe_turns(get_bribe_turns() - 1);
        } else {
            game.next_turn();
        }
    }

    void Merchant::undo(Player& target) {
        if (!is_player_alive()) {
            throw GameException("Player is not alive");
        }
        if (!target.is_player_alive()) {
            throw GameException("Target player is not alive");
        }
        // Merchant can't undo any actions
        throw GameException("Merchant cannot undo actions");
    }

    bool Merchant::can_block(const Player& target) const {
        (void)target;
        // Merchant can't block any actions
        return false;
    }

} 