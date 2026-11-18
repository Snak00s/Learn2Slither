#ifndef GAME_HPP
# define GAME_HPP

# include"Board.hpp"

class Game
{
	private:
		Board	_board;
		Snake	_snake;
		bool	_running;

		GameEvent	_applyGameRule(BoardTile const tile, SNAKE_POS const &head, SNAKE_POS const &tail);
		void	_lose(void);
		void	_win(void);
	
	public:
		Game(const int board_size_x, const int board_size_y);
		~Game(void);

		Board		&getBoard(void);
		Snake		&getSnake(void);
		bool		getGameRunning(void);
		
		GameEvent	playTurn(AgentAction action);
		void		resetGame(void);

};

std::ostream	&operator<<(std::ostream &o, Game &game);

#endif