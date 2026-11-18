#include "Game.hpp"

Game::Game(const int board_size_x, const int board_size_y) : _board(board_size_x, board_size_y), _total_game_played(0), _total_losses(0), _time_reach_10(0), _max_size_reached(0) {
	this->_snake = Snake(this->_board.getBoardVec());
	this->_board.generateApple(this->_snake.getSnakeBody(), 2, 'G');
	this->_board.generateApple(this->_snake.getSnakeBody(), 1, 'R');
	return ;
}

Game::~Game(void) {
	return ;
}

void	Game::_win(void)
{
	return ;
}

void	Game::_lose(void)
{
	this->_computeResult();
	this->resetGame();
	return ;
}

GameEvent	Game::_applyGameRule(BoardTile const tile, SNAKE_POS const &head, SNAKE_POS const &tail)
{
	GameEvent event = GameEvent::NOTHING;
	switch (tile)
	{
		case BoardTile::TILE_NOTHING:
			break;
		case BoardTile::TILE_WALL:
			this->_lose();
			event = GameEvent::LOOSE;
			break;
		case BoardTile::TILE_BODY:
			this->_lose();
			event = GameEvent::LOOSE;
			break;
		case BoardTile::TILE_GREEN:
			this->_snake.enlargeBody(tail);
			this->_board.destroyApple(head);
			this->_board.generateApple(this->_snake.getSnakeBody(), 1, 'G');
			event = GameEvent::ENLARGE;
			break;
		case BoardTile::TILE_RED:
			this->_snake.decreaseBody();
			this->_board.destroyApple(head);
			this->_board.generateApple(this->_snake.getSnakeBody(), 1, 'R');
			event = GameEvent::DECREASE;
			break;
		
		default:
			break;
	}
	if (this->_snake.getBodySize() < 1)
	{
		this->_lose();
		event = GameEvent::LOOSE;
	}
	return (event);
}

GameEvent	Game::playTurn(AgentAction action)
{
	Snake &snake = this->_snake;
	Board &board = this->_board;
	SNAKE_POS const tail = snake.getTailPos();
	SNAKE_POS const head = snake.agentMove(action);

	SNAKE_VEC const &body = snake.getSnakeBody();

	BoardTile tile = board.checkSnakePos(head, body);

	GameEvent event = this->_applyGameRule(tile, head, tail);

	snake.updateSnakeVision(board.getBoardVec(), board.getBoardSizeX(), board.getBoardSizeY());

	return (event);
}

void	Game::resetGame(void)
{
	const int board_size_x = this->_board.getBoardSizeX();
	const int board_size_y = this->_board.getBoardSizeY();
	this->_board.resetBoard(board_size_x, board_size_y);
	this->_snake.resetSnake(this->_board.getBoardVec());
	this->_board.generateApple(this->_snake.getSnakeBody(), 2, 'G');
	this->_board.generateApple(this->_snake.getSnakeBody(), 1, 'R');
}

void	Game::_computeResult(void)
{
	size_t	size = this->_snake.getBodySize();
	if (size >= 10)
		this->_time_reach_10++;
	if (size > this->_max_size_reached)
		this->_max_size_reached = size;
	this->_total_game_played++;
	this->_total_losses++;
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

Snake	&Game::getSnake(void) { return this->_snake; }
Board	&Game::getBoard(void) { return this->_board; }
size_t	Game::getTotalGamePlayed(void) { return this->_total_game_played; }
size_t	Game::getTotalLosses(void) { return this->_total_losses; }
size_t	Game::getTimeReach10(void) { return this->_time_reach_10; }
size_t	Game::getMaxSizeReached(void) { return this->_max_size_reached; }