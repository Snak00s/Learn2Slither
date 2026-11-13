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

void	print_board_row(BOARD_ROW const &vec)
{
	for (auto &c : vec)
			std::cout << c;
	std::cout << std::endl;
}