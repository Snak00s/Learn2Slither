#include"Board.hpp"

Board::Board(int board_size_x, int board_size_y): _board_size_x(board_size_x + 2), _board_size_y(board_size_y + 2)
{
	this->_board.reserve(this->_board_size_y);
	for (int i = 0; i < this->_board_size_y; i++)
	{
		this->_board.emplace_back();
		this->_board[i].reserve(this->_board_size_x);
		if (i == 0 || i == this->_board_size_y - 1)
			this->_board[i].assign(this->_board_size_x, 'W');
		else
		{
			this->_board[i].assign(this->_board_size_x, '0');
			this->_board[i][0] = this->_board[i][this->_board_size_x - 1] = 'W';
		}
	}
	return;
}

Board::~Board(void)
{
	return;
}

void	Board::generateApple(const int ammount, const char type)
{
	int i = 0;
	while (i < ammount)
	{
		int x = rand() % this->_board_size_x;
		int y = rand() % this->_board_size_y;
		while (this->_board[x][y] != '0')
		{
			x = rand() % this->_board_size_x;
			y = rand() % this->_board_size_y;
		}
		this->_board[x][y] = type;
		i++;
	}
	return;
}

std::vector<std::vector<char>>	Board::getBoardVec(void) const {
	return this->_board;
}

int Board::getBoardSizeX(void) const {
	return this->_board_size_x;
}

int Board::getBoardSizeY(void) const {
	return this->_board_size_y;
}

std::ostream	&operator<<( std::ostream &o, Board const &board) {

	auto board_vec = board.getBoardVec();
	auto row_end = board_vec.end();
	for (auto row = board_vec.begin(); row != row_end; ++row)
	{
		auto col_end = (*row).end();
		for (auto col = (*row).begin(); col != col_end; ++col)
			o << *col;
		o << std::endl;
	}
	return (o);
}