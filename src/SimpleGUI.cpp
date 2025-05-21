#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include "Game.hpp"
#include "Governor.hpp"
#include "Baron.hpp"
#include "Spy.hpp"
#include "General.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"

using namespace coup;

int main() {
    // Create a game and add some players
    Game game;
    auto p1 = std::make_shared<Governor>(game, "Alice");
    auto p2 = std::make_shared<Baron>(game, "Bob");
    auto p3 = std::make_shared<Spy>(game, "Charlie");
    game.add_player(p1);
    game.add_player(p2);
    game.add_player(p3);

    // Create the window (SFML 3.x: VideoMode takes Vector2u)
    sf::RenderWindow window(sf::VideoMode({500u, 300u}), "Coup Game - Simple GUI");
    sf::Font font;
    font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf"); // Change path if needed

    while (window.isOpen()) {
        // SFML 3.x: pollEvent returns std::optional<sf::Event>
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Advance turn on space (check key state)
        static bool space_was_pressed = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space)) {
            if (!space_was_pressed) {
                auto current = game.get_player(game.turn());
                current->gather();
                space_was_pressed = true;
            }
        } else {
            space_was_pressed = false;
        }

        window.clear(sf::Color(30, 30, 30));

        // Title
        sf::Text title(font, "Coup - Simple GUI Demo", 24);
        title.setFillColor(sf::Color::White);
        title.setPosition({20.f, 10.f});
        window.draw(title);

        // Show whose turn
        sf::Text turnText(font, "Current turn: " + game.turn(), 20);
        turnText.setFillColor(sf::Color::Yellow);
        turnText.setPosition({20.f, 50.f});
        window.draw(turnText);

        // Show players and coins
        auto players = game.players();
        float y = 90.f;
        for (const auto& name : players) {
            auto player = game.get_player(name);
            std::string info = name + " (" + player->role() + ") - Coins: " + std::to_string(player->get_coins());
            sf::Text t(font, info, 18);
            t.setFillColor(sf::Color::Cyan);
            t.setPosition({40.f, y});
            window.draw(t);
            y += 30.f;
        }

        // Instructions
        sf::Text instr(font, "Press SPACE to advance turn (gather)", 16);
        instr.setFillColor(sf::Color(200, 200, 200));
        instr.setPosition({20.f, 250.f});
        window.draw(instr);

        window.display();
    }
    return 0;
} 