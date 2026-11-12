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
	this->generateApple(2, 'G');
	this->generateApple(1, 'R');
	return;
}

Board::~Board(void)
{
	return;
}

void	Board::resetBoard(int board_size_x, int board_size_y)
{
	this->_board.clear();
	this->_board_size_x = board_size_x;
	this->_board_size_y = board_size_y;
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
	this->generateApple(2, 'G');
	this->generateApple(1, 'R');
	return;
}

void	Board::destroyApple(SNAKE_POS const &pos)
{
	this->_board[pos.second][pos.first] = '0';
	return ;
}

void	Board::generateApple(const int ammount, const char type)
{
	int i = 0;
	while (i < ammount)
	{
		int x = rand() % this->_board_size_x;
		int y = rand() % this->_board_size_y;
		while (this->_board[y][x] != '0')
		{
			x = rand() % this->_board_size_x;
			y = rand() % this->_board_size_y;
		}
		this->_board[y][x] = type;
		i++;
	}
	return;
}

void	Board::generateApple(SNAKE_VEC &snake, const int ammount, const char type)
{
	int i = 0;
	while (i < ammount)
	{
		int x = rand() % this->_board_size_x;
		int y = rand() % this->_board_size_y;
		while (this->_board[y][x] != '0' || std::find(snake.begin(), snake.end(), SNAKE_POS(x, y)) != snake.end())
		{
			x = rand() % this->_board_size_x;
			y = rand() % this->_board_size_y;
		}
		this->_board[y][x] = type;
		i++;
	}
	return;
}

Board_tile	Board::checkSnakePos(SNAKE_POS const &pos)
{
	const int x = pos.first;
	const int y = pos.second;

	const char tile = this->_board[y][x];

	switch (tile)
	{
	case '0':
		return (Board_tile::TILE_NOTHING);
	case 'W':
		return (Board_tile::TILE_WALL);
	case 'G':
		return (Board_tile::TILE_GREEN);
	case 'R':
		return (Board_tile::TILE_RED);

	default:
		return (Board_tile::TILE_ERROR);
	}
	return (Board_tile::TILE_ERROR);
}

// -------------------------------------------------------------

std::vector<std::vector<char>>	Board::getBoardVec(void) const {
	return this->_board;
}

int Board::getBoardSizeX(void) const {
	return this->_board_size_x;
}

int Board::getBoardSizeY(void) const {
	return this->_board_size_y;
}