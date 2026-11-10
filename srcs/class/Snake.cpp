#include"Snake.hpp"

Snake::Snake(Board const &board, int snakeMaxSize) : _bodySize(3), _maxSize(snakeMaxSize)
{
	this->_snake.reserve(this->_maxSize);
	for (int i = 0; i < this->_maxSize; i++)
		this->_snake.emplace_back();
	auto vec = board.getBoardVec();
	const int board_max_x = board.getBoardSizeX();
	const int board_max_y = board.getBoardSizeY();
	int x = rand() % board_max_x;
	int y = rand() % board_max_y;
	while (vec[x][y] != '0')
	{
		x = rand() % board_max_x;
		y = rand() % board_max_y;
	}
	this->_snake[0] = POS(x, y);
	this->_bodySize = 1;

	auto snake_beg = this->_snake.begin();
	auto snake_end = this->_snake.end();
	while (this->_bodySize != 3)
	{
		int next_x = x;
		int next_y = y;
		while (vec[next_x][next_y] != '0' || std::find(snake_beg, snake_end, POS(next_x, next_y)) != snake_end)
		{
			next_x = x;
			next_y = y;

			int cas = rand() % 4;
			switch (cas)
			{
			case 0:
				next_x = x + 1;
				break;

			case 1:
				next_x = x - 1;
				break;

			case 2:
				next_y = y + 1;
				break;
			
			case 3:
				next_y = y - 1;
				break;

			default:
				break;
			}
		}
		std::cout << next_x << " " << next_y << std::endl;
		this->_snake[this->_bodySize] = POS(next_x, next_y);
		x = next_x;
		y = next_y;
		this->_bodySize++;
	}
	return;
}

VEC_POS Snake::getSnake() const
{
	return this->_snake;
}

POS	Snake::getHeadPos() const
{
	return this->_snake[0];
}

Snake::~Snake(void)
{
	return ;
}