#include "Player.hpp"
#include "GameException.hpp"

namespace coup {

    Player::Player(Game& game, const std::string& name)
        : game(game), name(name), coins(0), is_blocked(false), is_alive(true) {}

    void Player::gather() {
        if (!is_alive) {
            throw GameException("Player is not alive");
        }
        if (is_blocked) {
            throw GameException("Player is blocked");
        }
        if (game.turn() != name) {
            throw GameException("Not player's turn");
        }
        coins++;
        game.set_last_action(name, "gather");
        if (bribe_turns > 0) {
            bribe_turns--;
        } else {
            game.next_turn();
        }
    }

    void Player::tax() {
        if (!is_alive) {
            throw GameException("Player is not alive");
        }
        if (is_blocked) {
            throw GameException("Player is blocked");
        }
        if (game.turn() != name) {
            throw GameException("Not player's turn");
        }
        coins += 2;
        game.set_last_action(name, "tax");
        if (bribe_turns > 0) {
            bribe_turns--;
        } else {
            game.next_turn();
        }
    }

    void Player::bribe() {
        if (!is_alive) {
            throw GameException("Player is not alive");
        }
        if (is_blocked) {
            throw GameException("Player is blocked");
        }
        if (game.turn() != name) {
            throw GameException("Not player's turn");
        }
        if (coins < 4) {
            throw GameException("Not enough coins for bribe");
        }
        coins -= 4;
        bribe_turns = 1;
        game.set_last_action(name, "bribe");
        game.next_turn();
    }

    void Player::arrest(Player& target) {
        if (!is_alive) {
            throw GameException("Player is not alive");
        }
        if (is_blocked) {
            throw GameException("Player is blocked");
        }
        if (game.turn() != name) {
            throw GameException("Not player's turn");
        }
        if (!target.is_alive) {
            throw GameException("Target player is not alive");
        }
        if (target.coins < 1) {
            throw GameException("Target has no coins");
        }
        target.coins--;
        coins++;
        game.set_last_action(name, "arrest");
        if (bribe_turns > 0) {
            bribe_turns--;
        } else {
            game.next_turn();
        }
    }

    void Player::sanction(Player& target) {
        if (!is_alive) {
            throw GameException("Player is not alive");
        }
        if (is_blocked) {
            throw GameException("Player is blocked");
        }
        if (game.turn() != name) {
            throw GameException("Not player's turn");
        }
        if (coins < 3) {
            throw GameException("Not enough coins for sanction");
        }
        if (!target.is_alive) {
            throw GameException("Target player is not alive");
        }
        coins -= 3;
        target.is_blocked = true;
        game.set_last_action(name, "sanction");
        if (bribe_turns > 0) {
            bribe_turns--;
        } else {
            game.next_turn();
        }
    }

    void Player::coup(Player& target) {
        if (!is_alive) {
            throw GameException("Player is not alive");
        }
        if (is_blocked) {
            throw GameException("Player is blocked");
        }
        if (game.turn() != name) {
            throw GameException("Not player's turn");
        }
        if (coins < 7) {
            throw GameException("Not enough coins for coup");
        }
        if (!target.is_alive) {
            throw GameException("Target player is not alive");
        }
        coins -= 7;
        target.is_alive = false;
        game.set_last_action(name, "coup");
        if (bribe_turns > 0) {
            bribe_turns--;
        } else {
            game.next_turn();
        }
    }

} 