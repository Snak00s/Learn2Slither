#include"Snake.hpp"

Snake::Snake(void)
{
	return;
}

Snake::Snake(const BOARD_VEC &vec) : _bodySize(1)
{
	const int board_max_x = vec[0].size();
	const int board_max_y = vec.size();

	BOARD_ROW const row(board_max_x, ' ');
	
	for (int i = 0; i < board_max_y; i++)
	{
		this->_snake_vision.emplace_back(row);
		if (i < 3)
			this->_snake_vec.emplace_back();
	}
	int x = rand() % board_max_x;
	int y = rand() % board_max_y;
	while (vec[y][x] != '0')
	{
		x = rand() % board_max_x;
		y = rand() % board_max_y;
	}
	this->_snake_vec[0] = SNAKE_POS(x, y);

	auto snake_beg = this->_snake_vec.begin();
	auto snake_end = this->_snake_vec.end();
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
		this->_snake_vec[this->_bodySize] = SNAKE_POS(next_x, next_y);
		x = next_x;
		y = next_y;
		this->_bodySize++;
	}
	this->_prev_pos = this->_snake_vec[0];
	this->updateSnakeVision(vec, board_max_x, board_max_y);
	return;
}

Snake::~Snake(void)
{
	return ;
}

void	Snake::resetSnake(const BOARD_VEC &vec)
{
	this->_snake_vec.clear();
	this->_bodySize = 1;
	const int board_max_x = vec[0].size();
	const int board_max_y = vec.size();
	BOARD_ROW const row(board_max_x, ' ');
	
	for (int i = 0; i < board_max_y; i++)
	{
		this->_snake_vision[i] = row;
		if (i < 3)
			this->_snake_vec.emplace_back();
	}
	int x = rand() % board_max_x;
	int y = rand() % board_max_y;
	while (vec[y][x] != '0')
	{
		x = rand() % board_max_x;
		y = rand() % board_max_y;
	}
	this->_snake_vec[0] = SNAKE_POS(x, y);

	auto snake_beg = this->_snake_vec.begin();
	auto snake_end = this->_snake_vec.end();
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
		this->_snake_vec[this->_bodySize] = SNAKE_POS(next_x, next_y);
		x = next_x;
		y = next_y;
		this->_bodySize++;
	}

	this->_prev_pos = this->_snake_vec[0];
	this->updateSnakeVision(vec, board_max_x, board_max_y);
	return;
}

void	Snake::enlargeBody(SNAKE_POS const &tail) {
	this->_snake_vec.emplace_back(SNAKE_POS(tail.first, tail.second));
	this->_bodySize++;
	return;
}

void	Snake::decreaseBody(void) {
	this->_snake_vec.pop_back();
	this->_bodySize--;
	return ;
}

SNAKE_POS	Snake::move(Snake_dir dir) {

	this->_prev_pos = this->_snake_vec[0];

	for (int i = this->_bodySize - 1; i > 0; i--)
		this->_snake_vec[i] = this->_snake_vec[i - 1];
	switch (dir)
	{
		case Snake_dir::MOVE_UP:
			this->_snake_vec[0].second -= 1;
			break;
		case Snake_dir::MOVE_LEFT:
			this->_snake_vec[0].first -= 1;
			break;
		case Snake_dir::MOVE_DOWN:
			this->_snake_vec[0].second += 1;
			break;
		case Snake_dir::MOVE_RIGHT:
			this->_snake_vec[0].first += 1;
			break;
		
		default:
			break;
	}
	return (this->getHeadPos());
}

void	Snake::clearOldSnakeVision(const int board_max_x, const int board_max_y)
{
	SNAKE_POS const &head = this->_prev_pos;

	const int board_origin_x = head.first;
	const int board_origin_y = head.second;

	BOARD_VEC &vision = this->_snake_vision;

	int y = board_origin_y;
	while (y >= 0)
		vision[y--][board_origin_x] = ' ';
	//South
	y = board_origin_y;
	while (y < board_max_y)
		vision[y++][board_origin_x] = ' ';
	//East
	int x = board_origin_x;
	while (x >= 0)
		vision[board_origin_y][x--] = ' ';
	//West
	x = board_origin_x;
	while (x < board_max_x)
		vision[board_origin_y][x++] = ' ';
	return ;
}

void	Snake::updateSnakeVision(const BOARD_VEC &vec, const int board_max_x, const int board_max_y)
{
	this->clearOldSnakeVision(board_max_x, board_max_y);
	SNAKE_POS const &head = this->getHeadPos();

	const int board_origin_x = head.first;
	const int board_origin_y = head.second;

	BOARD_VEC &vision = this->_snake_vision;

	vision[board_origin_y][board_origin_x] = 'H';
	//Manage Body Part
	auto body_end = this->_snake_vec.end();
	for (auto body = this->_snake_vec.begin() + 1; body != body_end; ++body)
	{
		if ((*body).first == board_origin_x || (*body).second == board_origin_y)
			vision[(*body).second][(*body).first] = 'S';
	}

	//North
	int y = board_origin_y;
	while (y >= 0)
	{
		if (vision[y][board_origin_x] == ' ')
			vision[y][board_origin_x] = vec[y][board_origin_x];
		y--;
	}
	//South
	y = board_origin_y;
	while (y < board_max_y)
	{
		if (vision[y][board_origin_x] == ' ')
			vision[y][board_origin_x] = vec[y][board_origin_x];
		y++;
	}
	//East
	int x = board_origin_x;
	while (x >= 0)
	{
		if (vision[board_origin_y][x] == ' ')
			vision[board_origin_y][x] = vec[board_origin_y][x];
		x--;
	}
	//West
	x = board_origin_x;
	while (x < board_max_x)
	{
		if (vision[board_origin_y][x] == ' ')
			vision[board_origin_y][x] = vec[board_origin_y][x];
		x++;
	}
	return ;
}

SNAKE_VEC	&Snake::getSnakeBody(void) {
	return this->_snake_vec;
}

SNAKE_POS	&Snake::getHeadPos(void) {
	return this->_snake_vec[0];
}

SNAKE_POS	Snake::getTailPos(void) {
	return SNAKE_POS(this->_snake_vec.back());
}

BOARD_VEC	&Snake::getSnakeVision(void) {
	return this->_snake_vision;
}

int			Snake::getBodySize(void) const {
	return this->_bodySize;
}

std::ostream	&operator<<(std::ostream &o, Snake &snake)
{
	SNAKE_VEC const &body = snake.getSnakeBody();

	auto snake_end = body.end();
	for (auto i = body.begin(); i != snake_end; ++i)
		o << "pos_x = " << (*i).first << " | pos_y = " << (*i).second << std::endl;
	return (o);
}