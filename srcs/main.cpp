#include"Snake.hpp"

// W = wall
// H = snake head
// S = snake body segment
// G = green apple
// R = red apple
// 0 = empty space

int main(int argc, char **argv)
{
	std::srand(time(0));
	(void)argc, (void)argv;
	Board test(10, 10);
	test.generateApple(2, 'G');
	test.generateApple(1, 'R');
	Snake snak(test, 10);
	std::cout << test << std::endl;

	auto vec = snak.getSnake();
	for (auto i = vec.begin(); i != vec.end(); ++i)
	{
		std::cout << "x = " << (*i).first << " | y = " << (*i).second << std::endl;
	}
	return(0);
}