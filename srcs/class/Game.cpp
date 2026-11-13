#include "Game.hpp"

Game::Game(const int board_size_x, const int board_size_y) : _board(board_size_x, board_size_y), _running(1) {
	this->_snake = Snake(this->_board.getBoardVec());
	return ;
}

Game::~Game(void) {
	return ;
}

Snake	&Game::getSnake(void) { return this->_snake; }

Board	&Game::getBoard(void) { return this->_board; }

bool	Game::getGameRunning(void) { return this->_running; }

void	Game::_win(void)
{
	return ;
}

void	Game::_lose(void)
{
	this->resetGame();
	return ;
}

void	Game::_applyGameRule(Board_tile const tile, SNAKE_POS const &head, SNAKE_POS const &tail)
{
	switch (tile)
	{
	case Board_tile::TILE_NOTHING:
		break;
	case Board_tile::TILE_WALL:
		this->_lose();
		break;
	case Board_tile::TILE_BODY:
		this->_lose();
		break;
	case Board_tile::TILE_GREEN:
		this->_snake.enlargeBody(tail);
		this->_board.destroyApple(head);
		this->_board.generateApple(this->_snake.getSnakeBody(), 1, 'G');
		break;
	case Board_tile::TILE_RED:
		this->_snake.decreaseBody();
		this->_board.destroyApple(head);
		this->_board.generateApple(this->_snake.getSnakeBody(), 1, 'R');
		break;
	
	default:
		break;
	}
	if (this->_snake.getBodySize() < 1)
		this->_lose();
}

void	Game::playTurn(Snake_dir dir)
{
	Snake &snake = this->_snake;
	Board &board = this->_board;
	SNAKE_POS const tail = snake.getTailPos();
	SNAKE_POS const head = snake.move(dir);

	snake.updateSnakeVision(board.getBoardVec(), board.getBoardSizeX(), board.getBoardSizeY());

	Board_tile tile = board.checkSnakePos(head);

	SNAKE_VEC const &body = snake.getSnakeBody();
	if (std::count(body.begin(), body.end(), head) > 1)
		tile = Board_tile::TILE_BODY;

	this->_applyGameRule(tile, head, tail);

	return ;
}

void	Game::resetGame(void)
{
	const int board_size_x = this->_board.getBoardSizeX();
	const int board_size_y = this->_board.getBoardSizeY();
	this->_board.resetBoard(board_size_x, board_size_y);
	this->_snake.resetSnake(this->_board.getBoardVec());
}

std::ostream	&operator<<(std::ostream &o, Game &game) {
	BOARD_VEC board_vec = game.getBoard().getBoardVec();
	Snake &snake = game.getSnake();
	SNAKE_VEC snake_vec = snake.getSnakeBody();

	auto snake_begin = snake_vec.begin();
	auto snake_end = snake_vec.end();
	for (auto body = snake_begin; body != snake_end; ++body)
	{
		int x = (*body).first;
		int y = (*body).second;
		if (body == snake_begin)
			board_vec[y][x] = 'H';
		else
			board_vec[y][x] = 'S';
	}
	auto row_end = board_vec.end();
	for (auto row = board_vec.begin(); row != row_end; ++row)
	{
		auto col_end = (*row).end();
		for (auto col = (*row).begin(); col != col_end; ++col)
			o << ((*col == '0') ? ' ' : *col);
		o << std::endl;
	}
	return (o);
}