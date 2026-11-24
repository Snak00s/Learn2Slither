#ifndef MAIN_HPP
# define MAIN_HPP

# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <iostream>
# include <array>
# include <string>
# include <cstdlib>
# include <ctime>
# include <cmath>
# include <memory>
# include <vector>
# include <map>
# include <sys/types.h>
# include <dirent.h>
# include <exception>
# include <fstream>
# include <queue>
# include <unordered_map>
# include <algorithm>
# include <chrono>
# include <unistd.h>
# include <bit>
# include <format>
# include <filesystem>
#include <variant>

using SNAKE_POS=std::pair<int, int>;
using SNAKE_VEC=std::vector<std::pair<int, int>>;

using BOARD_VEC=std::vector<std::vector<char>>;
using BOARD_ROW=std::vector<char>;

// enum class Snake_dir {
// 	MOVE_UP,
// 	MOVE_LEFT,
// 	MOVE_DOWN,
// 	MOVE_RIGHT,
// 	MOVE_NONE
// };

enum class Compass {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

enum class BoardTile {
	TILE_NOTHING,
	TILE_WALL,
	TILE_BODY,
	TILE_GREEN,
	TILE_RED
};

enum class GameEvent {
	NOTHING,
	LOOSE,
	DECREASE,
	ENLARGE
};

enum class AgentAction {
	IDLE,
	TURN_RIGHT,
	TURN_LEFT
};

void	clear();
void	print_board_vec(BOARD_VEC const &vec);
void	print_board_row(BOARD_ROW const &vec);
void	print_vector(std::vector<double> const &vec);

#endif