#ifndef GAME_HPP
# define GAME_HPP

# include"Board.hpp"

class Game
{
	private:
		Board	_board;
		Snake	_snake;
		size_t	_total_game_played;
		size_t	_total_losses;
		size_t	_time_reach_10;
		size_t	_max_size_reached;

		GameEvent	_applyGameRule(BoardTile const tile, SNAKE_POS const &head, SNAKE_POS const &tail);
		void		_computeResult(void);
		void		_lose(void);
		void		_win(void);
	
	public:
		Game(const int board_size_x, const int board_size_y);
		~Game(void);
		
		GameEvent	playTurn(AgentAction action);
		void		resetGame(void);


		Board		&getBoard(void);
		Snake		&getSnake(void);
		size_t		getTotalGamePlayed(void);
		size_t		getTotalLosses(void);
		size_t		getTimeReach10(void);
		size_t		getMaxSizeReached(void);

};

std::ostream	&operator<<(std::ostream &o, Game &game);

#endif