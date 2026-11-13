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
		BOARD_VEC	_snake_vision;

		BOARD_ROW	_north;
		BOARD_ROW	_south;
		BOARD_ROW	_east;
		BOARD_ROW	_west;

		SNAKE_POS	_prev_pos;
	
	public:
		Snake(void);
		Snake(const BOARD_VEC &vec);
		~Snake(void);

		void	resetSnake(const BOARD_VEC &vec);

		void	enlargeBody(SNAKE_POS const &tail);
		void	decreaseBody(void);

		SNAKE_POS	move(Snake_dir dir);
		void		clearOldSnakeVision(const int board_max_x, const int board_max_y);
		void		updateSnakeVision(const BOARD_VEC &vec, const int board_max_x, const int board_max_y);
		
		SNAKE_POS	&getHeadPos(void);
		SNAKE_POS	getTailPos(void);
		SNAKE_VEC	&getSnakeBody(void);
		BOARD_VEC	&getSnakeVision(void);
		int			getBodySize(void) const;

		BOARD_ROW const	&getNorthVision(void) const;
		BOARD_ROW const	&getSouthVision(void) const;
		BOARD_ROW const	&getEastVision(void) const;
		BOARD_ROW const	&getWestVision(void) const;

};

std::ostream	&operator<<(std::ostream &o, Snake &snake);

#endif