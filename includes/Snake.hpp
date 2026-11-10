#ifndef SNAKE_HPP
# define SNAKE_HPP

# include"Board.hpp"

typedef std::pair<int, int>  				POS;
typedef std::vector<std::pair<int, int>>	VEC_POS;

class Snake
{
	private:
		int _x;
		int _y;
		int _bodySize;
		int	_maxSize;
		VEC_POS _snake;
	
	public:
		Snake(Board const &board, int snakeMaxSize);
		~Snake();

		void	enlargeBody();
		void	decreaseBody();

		void	checkWinCond();
		void	checkLooseCond();

		POS		getHeadPos() const;

		VEC_POS	getSnake() const;

};

#endif