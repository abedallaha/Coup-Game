#include "Game.hpp"
#include "Player.hpp"
#include "GameException.hpp"

namespace coup {

    Game::Game() : current_player_index(0), game_started(false), game_ended(false), last_action_player(""), last_action_type("") {}

    void Game::add_player(std::shared_ptr<Player> player) {
        if (game_started) {
            throw GameException("Cannot add players after game has started");
        }
        if (game_players.size() >= 6) {
            throw GameException("Maximum number of players reached");
        }
        game_players.push_back(player);
    }

    void Game::remove_player(const std::string& name) {
        auto it = std::find_if(game_players.begin(), game_players.end(),
            [&name](const std::shared_ptr<Player>& p) { return p->get_name() == name; });
        
        if (it != game_players.end()) {
            game_players.erase(it);
        }
    }

    void Game::next_turn() {
        if (game_players.empty()) {
            throw GameException("No players in game");
        }
        size_t attempts = 0;
        do {
            current_player_index = (current_player_index + 1) % game_players.size();
            attempts++;
            auto& p = game_players[current_player_index];
            // Soft lock: skip blocked players with less than 3 coins
            if (p->is_player_alive() && (!p->is_player_blocked() || p->get_coins() >= 3)) {
                break;
            }
        } while (attempts < game_players.size());
    }

    std::string Game::turn() const {
        if (game_players.empty()) {
            throw GameException("No players in game");
        }
        return game_players[current_player_index]->get_name();
    }

    std::vector<std::string> Game::players() const {
        std::vector<std::string> active_players;
        for (const auto& player : game_players) {
            if (player->is_player_alive()) {
                active_players.push_back(player->get_name());
            }
        }
        return active_players;
    }

    std::string Game::winner() const {
        if (!game_ended) {
            throw GameException("Game is not over");
        }
        
        std::vector<std::string> active = players();
        if (active.size() != 1) {
            throw GameException("Game is not over - multiple players still active");
        }
        
        return active[0];
    }

    std::shared_ptr<Player> Game::get_player(const std::string& name) {
        auto it = std::find_if(game_players.begin(), game_players.end(),
            [&name](const std::shared_ptr<Player>& p) { return p->get_name() == name; });
        
        if (it == game_players.end()) {
            throw GameException("Player not found");
        }
        
        return *it;
    }

} 