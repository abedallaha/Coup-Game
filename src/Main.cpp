#include "Game.hpp"
#include "Player.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include "GameException.hpp"

#include <iostream>
#include <memory>
#include <string>

using namespace coup;

// Helper function to advance the turn to the desired player
void advance_to_player(Game& game, const std::string& player_name) {
    while (game.turn() != player_name) {
        // Find the player whose turn it is and make them gather
        auto current = game.get_player(game.turn());
        current->gather();
    }
}

int main() {
    try {
        // Create a new game
        Game game;

        // Create players with different roles
        auto governor = std::make_shared<Governor>(game, "Moshe");
        auto spy = std::make_shared<Spy>(game, "Yossi");
        auto baron = std::make_shared<Baron>(game, "Meirav");
        auto general = std::make_shared<General>(game, "Reut");
        auto judge = std::make_shared<Judge>(game, "Gilad");

        // Add players to the game
        game.add_player(governor);
        game.add_player(spy);
        game.add_player(baron);
        game.add_player(general);
        game.add_player(judge);

        // Print initial game state
        std::cout << "Game started with players:" << std::endl;
        for (const auto& name : game.players()) {
            std::cout << "- " << name << std::endl;
        }
        std::cout << "\nFirst turn: " << game.turn() << std::endl;

        // Demonstrate basic actions
        std::cout << "\nDemonstrating basic actions:" << std::endl;
        advance_to_player(game, "Moshe");
        governor->gather();
        std::cout << "Moshe gathered a coin. Coins: " << governor->get_coins() << std::endl;

        advance_to_player(game, "Yossi");
        spy->tax();
        std::cout << "Yossi collected tax. Coins: " << spy->get_coins() << std::endl;

        // Demonstrate role-specific actions
        std::cout << "\nDemonstrating role-specific actions:" << std::endl;
        advance_to_player(game, "Meirav");
        baron->gather();
        advance_to_player(game, "Meirav");
        baron->gather();
        advance_to_player(game, "Meirav");
        baron->gather();
        advance_to_player(game, "Meirav");
        baron->invest();
        std::cout << "Meirav invested coins. Coins: " << baron->get_coins() << std::endl;

        // Demonstrate blocking
        std::cout << "\nDemonstrating blocking:" << std::endl;
        for (int i = 0; i < 5; ++i) {
            advance_to_player(game, "Reut");
            general->gather();
        }
        std::cout << "Reut gathered coins. Coins: " << general->get_coins() << std::endl;

        // Demonstrate coup
        std::cout << "\nDemonstrating coup:" << std::endl;
        for (int i = 0; i < 7; i++) {
            advance_to_player(game, "Gilad");
            judge->gather();
        }
        advance_to_player(game, "Gilad");
        judge->coup(*governor);
        std::cout << "Gilad performed a coup on Moshe" << std::endl;
        std::cout << "Active players:" << std::endl;
        for (const auto& name : game.players()) {
            std::cout << "- " << name << std::endl;
        }

    } catch (const GameException& e) {
        std::cerr << "Game error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
} 