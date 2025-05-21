#ifndef GAME_EXCEPTION_HPP
#define GAME_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace coup {
    class GameException : public std::runtime_error {
    public:
        explicit GameException(const std::string& message) 
            : std::runtime_error(message) {}
    };
}

#endif // GAME_EXCEPTION_HPP 