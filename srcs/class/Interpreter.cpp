#include"Interpreter.hpp"

int Interpreter::interpretEventReward(GameEvent const event)
{
	switch (event)
	{
		case GameEvent::NOTHING:
			return (-1);
		case GameEvent::LOOSE:
			return (-3);
		case GameEvent::DECREASE:
			return (-2);
		case GameEvent::ENLARGE:
			return (3);
		
		default:
			return(0);
	}
}
uint8_t	Interpreter::interpretRowState(BOARD_ROW const &row)
{
	int w_order = -1;
	int s_order = -1;
	int g_order = -1;
	int r_order = -1;

	int placement = 0;
	for (auto c : row)
	{
		switch (c)
		{
			case 'S':
				if (s_order == -1)
					s_order = placement++;
				break;
			case 'W':
				if (w_order == -1)
					w_order = placement++;
				break;
			case 'G':
				if (g_order == -1)
					g_order = placement++;
				break;
			case 'R':
				if (r_order == -1)
					r_order = placement++;
				break;
			
			default:
				break;
		}
	}
	if (w_order == 0 && row[0] != 'W')
		w_order = 1;

	if (s_order == -1)
		s_order = w_order;

	if (w_order == -1)
		w_order = w_order;

	if (g_order == -1)
		g_order = w_order;

	if (r_order == -1)
		r_order = w_order;

	unsigned char c = (s_order << 6 | w_order << 4 | r_order << 2 | g_order);
	return (c);
}

uint32_t	Interpreter::interpretView(BOARD_ROW const &north, BOARD_ROW const &south, BOARD_ROW const &east, BOARD_ROW const &west)
{
	return (static_cast<unsigned int>(interpretRowState(north) << 24
									| interpretRowState(south) << 16
									| interpretRowState(east) << 8
									| interpretRowState(west)));
}