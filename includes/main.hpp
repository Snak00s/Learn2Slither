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

typedef std::pair<int, int>  				SNAKE_POS;
typedef std::vector<std::pair<int, int>>	SNAKE_VEC;

typedef std::vector<std::vector<char>>		BOARD_VEC;

enum class Snake_dir {
	MOVE_UP,
	MOVE_LEFT,
	MOVE_DOWN,
	MOVE_RIGHT
};

#endif