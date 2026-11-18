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

		Game	game(10, 10);
		Snake &snake = game.getSnake();
		// Board &board = game.getBoard();

		Agent	agent(Interpreter::interpretView(snake.getNorthVision(),
												snake.getSouthVision(),
												snake.getEastVision(),
												snake.getWestVision()),
												0.1, 0.9, 0.99);

		while(game.getTotalGamePlayed() + 1)
		{
			// clear();
			//agent action
			AgentAction const	action = agent.takeAction();

			//---------------------------------------------------------------------

			GameEvent event = game.playTurn(action);
			//----------------------------------------------------------------------

			//interpret tile and snake view
			const int			reward = Interpreter::interpretEventReward(event);		//main reward
			const uint32_t		state = Interpreter::interpretView(snake.getNorthVision(),
																snake.getSouthVision(),
																snake.getEastVision(),
																snake.getWestVision()); //next state
			//send state and reward to agent and update q-table
			agent.updateQTable(state, reward, event);
			//loop

			if (event == GameEvent::LOOSE)
			{
				agent.setGreedFactor(agent.getGreedFactor() * 0.99999);
			}

			if (agent.getGreedFactor() <= 0.0001)
			{
				std::cout << game << std::endl;
				usleep(200000);
			}

			// std::cout << game << std::endl;
			// std::cout << static_cast<int>(event) << std::endl;

			// sleep(1);
		}
		for (auto &item : agent.getQTable())
		{
			std::cout << item.first << std::endl;
			print_vector(item.second);
		}
		std::cout << "SIZE = " << agent.getQTable().size() << std::endl;
		std::cout << "NBR LOOSE : " << game.getTotalLosses() << std::endl;
		std::cout << "REACH 10 AMMOUNT : " << game.getTimeReach10() << std::endl;
		std::cout << "MAX SNAKE SIZE : " << game.getMaxSizeReached() << std::endl;
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