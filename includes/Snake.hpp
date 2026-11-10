#ifndef SNAKE_HPP
# define SNAKE_HPP

#include"main.hpp"

class Snake
{
	private:
		int			_x;
		int			_y;
		int			_bodySize;
		SNAKE_VEC	_snake;
	
	public:
		Snake(void);
		Snake(BOARD_VEC &vec);
		~Snake();

		void	enlargeBody();
		void	decreaseBody();

		void	checkWinCond();
		void	checkLooseCond();

		void	move(Snake_dir dir);

		SNAKE_POS	getHeadPos() const;
		SNAKE_VEC	getSnakeBody() const;
		int			getBodySize() const;

};

#endif