#include"Game.hpp"

void	print_board_vec(BOARD_VEC const &vec)
{
	for (auto &row : vec)
	{
		for (auto &c : row)
			std::cout << c;
		std::cout << std::endl;
	}
}