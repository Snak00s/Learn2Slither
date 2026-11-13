#ifndef BOARD_HPP
# define BOARD_HPP

#include"Snake.hpp"

class Board
{
	private:
		int									_board_size_x;
		int									_board_size_y;
		std::vector<std::vector<char>>		_board;

	public:
		Board(int board_size_x, int board_size_y);
		~Board(void);

		void							resetBoard(int board_size_x, int board_size_y);

		void							generateApple(SNAKE_VEC &snake, const int ammount, const char type);
		void							generateApple(const int ammount, const char type);
		void							destroyApple(SNAKE_POS const &pos);
		Board_tile						checkSnakePos(SNAKE_POS const &pos);

		std::vector<std::vector<char>>	getBoardVec(void) const;
		int								getBoardSizeX(void) const;
		int								getBoardSizeY(void) const;
		

};

#endif