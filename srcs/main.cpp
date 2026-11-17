#include"Game.hpp"
#include"Agent.hpp"
#include"Interpreter.hpp"

// Snake_dir	key_down(SDL_Event &event);

void	clear()
{
	std::cout << "[H[2J[3J" << std::endl;
	return ;
}

int main(int argc, char **argv)
{
	try
	{
		std::srand(time(0));
		(void)argc, (void)argv;

		// Game	game(10, 10);
		Board	board(10, 10);
		Snake	snake(board.getBoardVec());

		Agent	agent(Interpreter::interpretView(snake.getNorthVision(),
												snake.getSouthVision(),
												snake.getEastVision(),
												snake.getWestVision()), 0.5, 0.9);

		int step = 0;
		while(step < 100)
		{
			// clear();
			//agent action
			AgentAction const	action = agent.takeAction();

			//apply on snake
			SNAKE_POS const		pos = snake.agentMove(action);
			std::cout << "x = " << pos.first << " | " << "y = " << pos.second << std::endl;
			snake.updateSnakeVision(board.getBoardVec(), board.getBoardSizeX(), board.getBoardSizeY());

			SNAKE_VEC &snake_body = snake.getSnakeBody();
			//check snake board tile
			Board_tile			tile = board.checkSnakePos(pos, snake_body);

			//interpret tile and snake view
			const int			reward = Interpreter::interpretTileReward(tile);		//main reward
			const uint32_t		state = Interpreter::interpretView(snake.getNorthVision(),
																snake.getSouthVision(),
																snake.getEastVision(),
																snake.getWestVision()); //next state
			//send state and reward to agent and update q-table
			agent.updateQTable(state, reward);
			//loop

			step++;
		}
		for (auto &item : agent.getQTable())
		{
			std::cout << item.first << std::endl;
			print_vector(item.second);
		}
		std::cout << "SIZE = " << agent.getQTable().size() << std::endl;
		return(0);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

//state actuel : state debut de loop
//state next : state fin de loop

//donc pour update la q-table il faut garder en memoir le state actuel et futur


// 01010100	00000000 00010101 00000000
// 00000000 00010101 00000000 00000000

// 			S	W	R	G

// north	0	0	0	0

// south	1	1	1	0

// east		0	1	1	1

// west		0	0	0	0

// valeur = ordre apparition (0=premier, 1, 2, 3=dernier);
// si valeur (S ou R ou G) == valeur W -> y'a pas

// 000S00G0W

//	North			South		East			West
// 00 00 00 00 - 01 01 01 00 - 00 01 01 01 - 00 00 00 00
// S  W  R  G  - S  W  R  G  - S  W  R  G  - S  W  R  G