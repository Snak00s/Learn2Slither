#include"Game.hpp"

Game::Game(int board_max_x, int board_max_y, int snake_max_size) : _board(board_max_x, board_max_y), _snake(_board, snake_max_size)
{
	return;
}