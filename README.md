# Coup Game

## Table of Contents

- [Project Structure](#project-structure)
- [Game Rules](#game-rules)
- [Class Design](#class-design)
- [Role Abilities](#role-abilities)
- [Special Rules & Clarifications](#special-rules--clarifications)
- [Building & Running](#building--running)
- [Testing](#testing)
- [Memory Management](#memory-management)
- [GUI Demo](#gui-demo)
- [How the GUI Works](#how-the-gui-works)
---

## Project Structure

```
.
├── include/             # Header files
├── src/                # Source files
├── test/               # Unit tests
├── Makefile            # Build configuration
├── README.md           # This file
```

---

## Game Rules

- Each player has a name, a role, and a coin count.
- On their turn, a player may perform one of the following actions:
  - **gather**: Gain 1 coin.
  - **tax**: Gain 2 coins (can be blocked).
  - **bribe**: Pay 4 coins to gain an extra turn.
  - **arrest**: Take 1 coin from another player (cannot target the same player twice in a row).
  - **sanction**: Pay 3 coins to block another player's economic actions until their next turn.
  - **coup**: Pay 7 coins to eliminate another player (can be blocked by General).
- If a player starts their turn with 10 or more coins, they must perform a coup.
- Blockable actions can be countered by specific roles (see below).
- Eliminated players are removed from the game.
- The last active player wins.

---

## Class Design

- **Game**: Manages players, turn order, and game state.
- **Player (Base Class)**: Implements core actions and state.
- **Role Classes**: Inherit from Player and implement special abilities:
  - Governor, Spy, Baron, General, Judge, Merchant

---

## Role Abilities

- **Governor**: Gains 3 coins from tax; can cancel tax actions.
- **Spy**: Can view other players' coins and prevent arrests; abilities do not consume a turn.
- **Baron**: Can invest 3 coins to gain 6; receives compensation when sanctioned.
- **General**: Can pay 5 coins to block a coup; regains coins lost to arrest.
- **Judge**: Can cancel bribe actions; sanctions against Judge cost an extra coin.
- **Merchant**: Gains a bonus coin if starting turn with 3+ coins; pays 2 coins to the pool when arrested.

---

## Special Rules & Clarifications

- Multiple players can have the same role.
- There is no central coin pool limit.
- **Bribe** grants an extra turn (player can act twice in a row).
- **Governor** does not lose a turn when canceling tax.
- **Spy** actions do not count as a turn.
- **General** regains coins lost to arrest.
- **Judge** can only cancel bribe immediately after it is performed.
- **Coup** can only be blocked by General.
- **Arrest** does not cost coins.
- Players cannot perform two actions in one turn unless using bribe.
- If a block is successful, the blocked player loses their turn.
- If a player cannot pay for an action, an exception is thrown.
- If a player is sanctioned and has fewer than 3 coins, their turn is skipped (soft lock).
- All actions are validated for turn order, player status, and coin requirements.
- The GUI is for demonstration only and does not affect game logic.

---

## Building & Running

### Prerequisites

- C++17 compatible compiler
- Make
- SFML (for GUI demo)
- Valgrind (for memory checks)

### Build Commands

```sh
make Main      # Build main demo
make test      # Build and run unit tests
make valgrind  # Run memory leak check
make clean     # Remove build artifacts
```

### Running the GUI Demo

To build and run the GUI demo (requires SFML):

```sh
g++ -std=c++17 -I/opt/homebrew/include -L/opt/homebrew/lib -I./include -I./lib src/SimpleGUI.cpp src/Game.cpp src/Player.cpp src/Governor.cpp src/Baron.cpp src/Spy.cpp src/General.cpp src/Judge.cpp src/Merchant.cpp -o SimpleGUI -lsfml-graphics -lsfml-window -lsfml-system
./SimpleGUI
```

Make sure SFML is installed on your system. On macOS, you can install it with:

```sh
brew install sfml
```

If SFML is installed in a non-standard location, you may need to specify the include and library paths accordingly.

### How the GUI Works

- **Window and Font Setup**: A window is created with a title and dimensions. A font is loaded from the system (Arial) to display text.
- **Game Initialization**: A `Game` object is created, and players are added with specific roles (e.g., Spy, Baron, Governor).
- **Main Loop**: The program enters a loop that continues as long as the window is open. It checks for window events (like closing the window) and keyboard input.
- **Rendering**: The window is cleared to prepare for drawing. Text is drawn to display the current turn and player information. The window is displayed to show the updated graphics.
- **User Interaction**: The GUI responds to keyboard input (e.g., pressing 'G' to gather coins). It updates the game state based on user actions and redraws the window to reflect changes.

---

## Testing

- Comprehensive unit tests are provided in the `test/` directory.
- Tests cover all actions, roles, edge cases, and error conditions.
- Run `make test` to execute all tests.

---

## Memory Management

- All dynamic memory is managed with smart pointers.
- No raw pointer usage.
- The code is valgrind-clean (no memory leaks).

---

## GUI Demo

- The GUI is a simple SFML window that displays player names, roles, coins, and turn order.
- Press SPACE to advance the turn (gather action).
- The GUI is for demonstration only and is not required for the main build.

### How the GUI Works

- **Window and Font Setup**: A window is created with a title and dimensions. A font is loaded from the system (Arial) to display text.
- **Game Initialization**: A `Game` object is created, and players are added with specific roles (e.g., Spy, Baron, Governor).
- **Main Loop**: The program enters a loop that continues as long as the window is open. It checks for window events (like closing the window) and keyboard input.
- **Rendering**: The window is cleared to prepare for drawing. Text is drawn to display the current turn and player information. The window is displayed to show the updated graphics.
- **User Interaction**: The GUI responds to keyboard input (e.g., pressing 'G' to gather coins). It updates the game state based on user actions and redraws the window to reflect changes.

### Running the GUI Demo

To build and run the GUI demo (requires SFML):

```sh
g++ -std=c++17 -I/opt/homebrew/include -L/opt/homebrew/lib -I./include -I./lib src/SimpleGUI.cpp src/Game.cpp src/Player.cpp src/Governor.cpp src/Baron.cpp src/Spy.cpp src/General.cpp src/Judge.cpp src/Merchant.cpp -o SimpleGUI -lsfml-graphics -lsfml-window -lsfml-system
./SimpleGUI
```

Make sure SFML is installed on your system. On macOS, you can install it with:

```sh
brew install sfml
```

If SFML is installed in a non-standard location, you may need to specify the include and library paths accordingly.

---
 