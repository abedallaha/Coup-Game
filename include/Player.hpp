#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include "Game.hpp"

namespace coup {
    class Game;

    class Player {
    protected:
        Game& game;
        std::string name;
        int coins;
        bool is_blocked;
        bool is_alive;
        int bribe_turns = 0;

    public:
        Player(Game& game, const std::string& name);
        virtual ~Player() = default;

        // Basic actions available to all players
        void gather();
        void tax();
        void bribe();
        void arrest(Player& target);
        void sanction(Player& target);
        void coup(Player& target);

        // Getters
        std::string get_name() const { return name; }
        int get_coins() const { return coins; }
        bool is_player_blocked() const { return is_blocked; }
        bool is_player_alive() const { return is_alive; }
        int get_bribe_turns() const { return bribe_turns; }

        // Setters
        void add_coins(int amount) { coins += amount; }
        void remove_coins(int amount) { coins -= amount; }
        void set_blocked(bool blocked) { is_blocked = blocked; }
        void set_alive(bool alive) { is_alive = alive; }
        void set_bribe_turns(int n) { bribe_turns = n; }

        // Virtual methods for role-specific abilities
        virtual void undo(Player& target) = 0;
        virtual bool can_block(const Player& target) const = 0;
        virtual std::string role() const = 0;
    };

}

#endif // PLAYER_HPP 