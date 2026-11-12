#ifndef SNAKE_HPP
# define SNAKE_HPP

#include"main.hpp"

class Snake
{
	private:
		int			_x;
		int			_y;
		int			_bodySize;
		SNAKE_VEC	_snake_vec;
	
	public:
		Snake(void);
		Snake(const BOARD_VEC &vec);
		~Snake();

		void	resetSnake(const BOARD_VEC &vec);

		void	enlargeBody(SNAKE_POS const &tail);
		void	decreaseBody();

		SNAKE_POS	move(Snake_dir dir);
		void		snakeVision(const BOARD_VEC &vec);

		SNAKE_POS	&getHeadPos();
		SNAKE_POS	getTailPos();
		SNAKE_VEC	&getSnakeBody();
		int			getBodySize() const;

};

std::ostream	&operator<<(std::ostream &o, Snake &snake);

#endif