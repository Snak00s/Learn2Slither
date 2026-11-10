#ifndef BOARD_HPP
# define BOARD_HPP

#include"Snake.hpp"

class Board
{
	private:
		int								_board_size_x;
		int								_board_size_y;
		std::vector<std::vector<char>>	_board;
		Snake							_snake;

	public:
		Board(int board_size_x, int board_size_y);
		~Board(void);

		void							generateApple(const int ammount, const char type);
		void							move_snake(Snake_dir dir);

		std::vector<std::vector<char>>	getBoardVec(void) const;
		int								getBoardSizeX(void) const;
		int								getBoardSizeY(void) const;
		const Snake						&getSnake() const;
		Snake							&getNoConstSnake();
		

};

std::ostream	&operator<<( std::ostream &o, Board const &fixed );

#endif