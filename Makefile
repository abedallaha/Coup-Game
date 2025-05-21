CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include -I./lib
LDFLAGS = -L./lib

SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

# Source files excluding Main.cpp and SimpleGUI.cpp
SRCS = $(filter-out $(SRC_DIR)/Main.cpp $(SRC_DIR)/SimpleGUI.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Main program files
MAIN_SRCS = $(SRCS) $(SRC_DIR)/Main.cpp
MAIN_OBJS = $(MAIN_SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Test files
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o)

.PHONY: all clean test valgrind Main

all: Main test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

Main: $(MAIN_OBJS)
	$(CXX) $(MAIN_OBJS) -o Main

test: $(OBJS) $(TEST_OBJS)
	$(CXX) $(OBJS) $(TEST_OBJS) -o test_runner

valgrind: Main
ifeq ($(shell uname), Darwin)
	leaks --atExit -- ./Main
else
	valgrind --leak-check=full --show-leak-kinds=all ./Main
endif

clean:
	rm -rf $(BUILD_DIR) Main test_runner SimpleGUI 