#ifndef GAME_HPP
# define GAME_HPP

#include"Snake.hpp"

class Game
{
	private:
		Snake _snake;
		Board _board;
	
	public:
		Game(int board_max_x, int board_max_y, int snake_max_size);
		~Game(void);

};

#endif