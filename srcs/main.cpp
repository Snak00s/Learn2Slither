#include"Game.hpp"
#include"Agent.hpp"
#include"Interpreter.hpp"
#include"Parser.hpp"


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

		Parser	parser;

		parser.addArgToParse("-visual", "string");
		parser.addArgToParse("-sessions", "int");
		parser.addArgToParse("-save", "string");
		parser.addArgToParse("-learn", "string");
		parser.addArgToParse("-load", "string");

		auto args = parser.parse(argv, argc);

		Game	game(10, 10);
		Snake &snake = game.getSnake();
		// Board &board = game.getBoard();

		Agent	agent(Interpreter::interpretView(snake.getNorthVision(),
												snake.getSouthVision(),
												snake.getEastVision(),
												snake.getWestVision()),
												0.1, 0.97, 1);

		if (args["-sessions"].size() != 1)
			return(1);
		const size_t sessions_ammount = std::atoi(args["-sessions"][0].c_str());

		while(game.getTotalGamePlayed() < sessions_ammount)
		{
			//agent action
			int	snake_size = snake.getBodySize();
			AgentAction const	action = agent.takeAction();

			//----------------------------------------------------------------------

			GameEvent event = game.playTurn(action);
			//----------------------------------------------------------------------

			//interpret tile and snake view
			const int			reward = Interpreter::interpretEventReward(event);		//main reward
			const uint32_t		state = Interpreter::interpretView(snake.getNorthVision(),
																snake.getSouthVision(),
																snake.getEastVision(),
																snake.getWestVision()); //next state
			// send state and reward to agent and update q-table
			agent.updateQTable(state, reward, event);
			//loop

			if (event == GameEvent::LOOSE)
			{
				clear();
				agent.setGreedFactor(agent.getGreedFactor() * 0.99);
				std::cout << "nbr game = " << game.getTotalGamePlayed() << std::endl;
				std::cout << "size = " << snake_size << std::endl;
				std::cout << "max size = " << game.getMaxSizeReached() << std::endl;
				std::cout << "avg size = " << game.getAvgSize() << std::endl;
				std::cout << "REACH 10 AMMOUNT : " << game.getTimeReach10() << std::endl;
				std::cout << "SIZE Q_TABLE = " << agent.getQTable().size() << std::endl;
				std::cout << "greed factor = " << agent.getGreedFactor() << std::endl;
			}
		}
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