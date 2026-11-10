#ifndef BOARD_HPP
# define BOARD_HPP

#include"main.hpp"

class Board
{
	private:
		int								_board_size_x;
		int								_board_size_y;
		std::vector<std::vector<char>>	_board;

	public:
		Board(int board_size_x, int board_size_y);
		~Board(void);
	public:
		std::vector<std::vector<char>>	getBoardVec(void) const;
		int								getBoardSizeX(void) const;
		int								getBoardSizeY(void) const;
		void							generateApple(const int ammount, const char type);
		

};

std::ostream	&operator<<( std::ostream &o, Board const &fixed );

#endif