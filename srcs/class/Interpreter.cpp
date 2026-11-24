#include"Interpreter.hpp"

int Interpreter::interpretEventReward(GameEvent const event)
{
	switch (event)
	{
		case GameEvent::NOTHING:
			return (-1);
		case GameEvent::LOOSE:
			return (-100);
		case GameEvent::DECREASE:
			return (-50);
		case GameEvent::ENLARGE:
			return (50);
		
		default:
			return(0);
	}
}

// uint8_t	Interpreter::interpretRowState(BOARD_ROW const &row)
// {
// 	int o_order = -1;
// 	int death_order = -1;
// 	// int w_order = -1;
// 	// int s_order = -1;
// 	int g_order = -1;
// 	int r_order = -1;

// 	int placement = 0;
// 	for (auto c : row)
// 	{
// 		switch (c)
// 		{
// 			// case 'S':
// 			// 	if (s_order == -1)
// 			// 		s_order = placement++;
// 			// 	break;
// 			// case 'W':
// 			// 	if (w_order == -1)
// 			// 		w_order = placement++;
// 			// 	break;
// 			case '0':
// 				if (o_order == -1)
// 					o_order = placement++;
// 				break;
// 			case 'S': case 'W':
// 				if (death_order == -1)
// 					death_order = placement++;
// 				break;
// 			case 'G':
// 				if (g_order == -1)
// 					g_order = placement++;
// 				break;
// 			case 'R':
// 				if (r_order == -1)
// 					r_order = placement++;
// 				break;
			
// 			default:
// 				break;
// 		}
// 	}
// 	// if (w_order == 0 && row[0] != 'W')
// 	// 	w_order = 1;

// 	// if (s_order == 0 && row[0] != 'S')
// 	// 	s_order = 1;

// 	// if (s_order == -1)
// 	// 	s_order = w_order;

// 	// if (w_order == -1)
// 	// 	w_order = w_order;

// 	if (g_order == -1)
// 		g_order = death_order;

// 	if (r_order == -1)
// 		r_order = death_order;
	
// 	if (o_order == -1)
// 		o_order = death_order;

// 	unsigned char c = (o_order << 6 | death_order << 4 | r_order << 2 | g_order);
// 	return (c);
// }


// 00 = none
// 01 = next to
// 10 = not far
// 11 = far
int		range_value(int idx)
{
	if (idx == 0)
		return (0b01);
	else if (idx < 3)
		return (0b10);
	else
		return (0b11);
}

uint8_t	Interpreter::interpretRowState(BOARD_ROW const &row)
{
	uint8_t s_range = 0;
	uint8_t w_range = 0;
	uint8_t g_range = 0;
	uint8_t r_range = 0;

	size_t idx = 0;
	for (auto c : row)
	{
		switch (c)
		{
			case 'S':
				if (s_range == 0)
					s_range = range_value(idx);
				break;
			case 'W':
				if (w_range == 0)
					w_range = range_value(idx);
				break;
			case 'G':
				if (g_range == 0)
					g_range = range_value(idx);
				break;
			case 'R':
				if (r_range == 0)
					r_range = range_value(idx);
				break;
			
			default:
				break;
		}
		idx++;
		if (s_range || w_range)
			break;
	}

	uint8_t c = (s_range << 6 | w_range << 4 | g_range << 2 | r_range);
	return (c);
}

uint32_t	Interpreter::interpretView(BOARD_ROW const &north, BOARD_ROW const &south, BOARD_ROW const &east, BOARD_ROW const &west)
{
	return (static_cast<uint32_t>(interpretRowState(north) << 24
									| interpretRowState(south) << 16
									| interpretRowState(east) << 8
									| interpretRowState(west)));
}