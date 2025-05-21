#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <string>
#include <memory>

namespace coup {
    class Player;  // Forward declaration

    class Game {
    private:
        // Renamed from players
        std::vector<std::shared_ptr<Player>> game_players;
        size_t current_player_index;
        bool game_started;
        bool game_ended;
        std::string last_action_player;
        std::string last_action_type;

    public:
        Game();
        ~Game() = default;

        // Game management
        void add_player(std::shared_ptr<Player> player);
        void remove_player(const std::string& name);
        void next_turn();
        
        // Game state queries
        std::string turn() const;
        std::vector<std::string> players() const;
        std::string winner() const;
        
        // Game state
        bool is_game_started() const { return game_started; }
        bool is_game_ended() const { return game_ended; }
        void set_game_started(bool started) { game_started = started; }
        void set_game_ended(bool ended) { game_ended = ended; }
        
        // Player management
        std::shared_ptr<Player> get_player(const std::string& name);
        size_t get_current_player_index() const { return current_player_index; }
        void set_current_player_index(size_t index) { current_player_index = index; }

        // Last action tracking
        void set_last_action(const std::string& player, const std::string& action) {
            last_action_player = player;
            last_action_type = action;
        }
        std::string get_last_action_player() const { return last_action_player; }
        std::string get_last_action_type() const { return last_action_type; }
    };

}
// GAME_HPP 
#endif