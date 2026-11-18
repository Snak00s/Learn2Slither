#ifndef INTERPRETER_HPP
# define INTERPRETER_HPP

#include"main.hpp"

class Interpreter
{
	private:
		static uint8_t	interpretRowState(BOARD_ROW const &row);
	public:
		static int		interpretEventReward(GameEvent const event);
		static uint32_t	interpretView(BOARD_ROW const &north, BOARD_ROW const &south, BOARD_ROW const &east, BOARD_ROW const &west);
	};


#endif