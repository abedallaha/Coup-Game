#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Game.hpp"
#include "Player.hpp"
#include "Governor.hpp"
#include "Spy.hpp"
#include "Baron.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"

using namespace coup;

// Helper function to advance the turn to the desired player
void advance_to_player(Game& game, const std::string& player_name) {
    while (game.turn() != player_name) {
        // Find the player whose turn it is and make them gather
        auto current = game.get_player(game.turn());
        current->gather();
    }
}

TEST_CASE("Game initialization") {
    Game game;
    CHECK_FALSE(game.is_game_started());
    CHECK_FALSE(game.is_game_ended());
    CHECK_THROWS(game.turn());
    CHECK_THROWS(game.winner());
}

TEST_CASE("Adding players") {
    Game game;
    auto governor = std::make_shared<Governor>(game, "Moshe");
    auto spy = std::make_shared<Spy>(game, "Yossi");
    
    game.add_player(governor);
    game.add_player(spy);
    
    auto players = game.players();
    CHECK_EQ(players.size(), 2);
    CHECK_EQ(players[0], "Moshe");
    CHECK_EQ(players[1], "Yossi");
}

TEST_CASE("Basic player actions") {
    Game game;
    auto governor = std::make_shared<Governor>(game, "Moshe");
    auto spy = std::make_shared<Spy>(game, "Yossi");
    
    game.add_player(governor);
    game.add_player(spy);
    
    // Test gather
    advance_to_player(game, "Moshe");
    governor->gather();
    CHECK_EQ(governor->get_coins(), 1);
    
    // Test tax
    advance_to_player(game, "Yossi");
    spy->tax();
    CHECK_EQ(spy->get_coins(), 2);
}

TEST_CASE("Role-specific actions") {
    Game game;
    auto governor = std::make_shared<Governor>(game, "Moshe");
    auto baron = std::make_shared<Baron>(game, "Yossi");
    
    game.add_player(governor);
    game.add_player(baron);
    
    // Test Governor's tax
    advance_to_player(game, "Moshe");
    governor->tax();
    CHECK_EQ(governor->get_coins(), 3); // Gets 3 instead of 2
    
    // Test Baron's invest
    advance_to_player(game, "Yossi");
    baron->gather();
    advance_to_player(game, "Yossi");
    baron->gather();
    advance_to_player(game, "Yossi");
    baron->gather();
    advance_to_player(game, "Yossi");
    baron->invest();
    CHECK_EQ(baron->get_coins(), 6);
}

TEST_CASE("Game rules") {
    Game game;
    auto governor = std::make_shared<Governor>(game, "Moshe");
    auto spy = std::make_shared<Spy>(game, "Yossi");
    
    game.add_player(governor);
    game.add_player(spy);
    
    // Test turn order
    CHECK_EQ(game.turn(), "Moshe");
    advance_to_player(game, "Moshe");
    governor->gather();
    CHECK_EQ(game.turn(), "Yossi");
    
    // Test player elimination
    for (int i = 0; i < 7; i++) {
        advance_to_player(game, "Yossi");
        spy->gather();
    }
    advance_to_player(game, "Yossi");
    spy->coup(*governor);
    CHECK_FALSE(governor->is_player_alive());
}

TEST_CASE("Error handling") {
    Game game;
    auto governor = std::make_shared<Governor>(game, "Moshe");
    auto spy = std::make_shared<Spy>(game, "Yossi");
    
    game.add_player(governor);
    game.add_player(spy);
    
    // Test invalid actions
    CHECK_THROWS(spy->gather()); // Not spy's turn
    advance_to_player(game, "Moshe");
    CHECK_THROWS(governor->coup(*spy)); // Not enough coins
    CHECK_THROWS(governor->bribe()); // Not enough coins
} 