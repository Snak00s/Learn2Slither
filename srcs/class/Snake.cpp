#include"Snake.hpp"

Snake::Snake(void)
{
	return;
}

Snake::Snake(BOARD_VEC &vec) : _bodySize(3)
{
	for (int i = 0; i < 3; i++)
		this->_snake.emplace_back();
	const int board_max_x = vec[0].size();
	const int board_max_y = vec.size();
	int x = rand() % board_max_x;
	int y = rand() % board_max_y;
	while (vec[y][x] != '0')
	{
		x = rand() % board_max_x;
		y = rand() % board_max_y;
	}
	this->_snake[0] = SNAKE_POS(x, y);
	this->_bodySize = 1;

	auto snake_beg = this->_snake.begin();
	auto snake_end = this->_snake.end();
	while (this->_bodySize != 3)
	{
		int next_x = x;
		int next_y = y;
		while (vec[next_y][next_x] != '0' || std::find(snake_beg, snake_end, SNAKE_POS(next_x, next_y)) != snake_end)
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
		this->_snake[this->_bodySize] = SNAKE_POS(next_x, next_y);
		x = next_x;
		y = next_y;
		this->_bodySize++;
	}
	return;
}

void	Snake::enlargeBody(void) {
	if (this->_bodySize >= 2)
	{
		auto pen_ulti = *(this->_snake.rbegin() + 1);
		auto ulti = *(this->_snake.rbegin());
		int delta_x = ulti.first - pen_ulti.first;
		int delta_y = ulti.second - pen_ulti.second;
		std::cout << "delta_x = " << delta_x << " | delta_y" << delta_y << std::endl;
	}
}

void	Snake::move(Snake_dir dir) {

	for (int i = this->_bodySize - 1; i > 0; i--)
		this->_snake[i] = this->_snake[i - 1];
	switch (dir)
	{
		case Snake_dir::MOVE_UP:
			this->_snake[0].second -= 1;
			break;
		case Snake_dir::MOVE_LEFT:
			this->_snake[0].first -= 1;
			break;
		case Snake_dir::MOVE_DOWN:
			this->_snake[0].second += 1;
			break;
		case Snake_dir::MOVE_RIGHT:
			this->_snake[0].first += 1;
			break;
		
		default:
			break;
	}
	return ;
}

SNAKE_VEC	Snake::getSnakeBody() const {
	return this->_snake;
}

SNAKE_POS	Snake::getHeadPos() const {
	return this->_snake[0];
}

int			Snake::getBodySize() const {
	return this->_bodySize;
}

Snake::~Snake(void)
{
	return ;
}