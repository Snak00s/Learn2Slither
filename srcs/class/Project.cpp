#include"Project.hpp"

Project::Project(const size_t game_board_size_x, const size_t game_board_size_y, std::string load_model_filename) : _game(game_board_size_x, game_board_size_y),
	_agent(Interpreter::interpretView(_game.getSnake().getNorthVision(), _game.getSnake().getSouthVision(), _game.getSnake().getEastVision(), _game.getSnake().getWestVision()), 0.1, 0.97, 1)
{
	if (!load_model_filename.empty() && load_model_filename != "")
		this->_agent.loadModel(load_model_filename);
	return ;
}

Project::~Project()
{
	return ;
}

void	Project::launchProject(const size_t sessions_ammount, std::string save_model_filename, bool learning, bool visual)
{
	Game	&game = this->_game;
	Snake	&snake = game.getSnake();
	Agent	&agent = this->_agent;

	if (learning == false)
		agent.setGreedFactor(0);

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

		if (learning == true)
			agent.updateQTable(state, reward, event);
		agent.setActualState(state);
		//loop

		if (event == GameEvent::LOOSE)
		{
			clear();
			if (learning == true)
				agent.setGreedFactor(agent.getGreedFactor() * 0.99);
			if (visual == true)
			{
				std::cout << "nbr game = " << game.getTotalGamePlayed() << std::endl;
				std::cout << "size = " << snake_size << std::endl;
				std::cout << "max size = " << game.getMaxSizeReached() << std::endl;
				std::cout << "avg size = " << game.getAvgSize() << std::endl;
				std::cout << "REACH 10 AMMOUNT : " << game.getTimeReach10() << std::endl;
				std::cout << "SIZE Q_TABLE = " << agent.getQTable().size() << std::endl;
				std::cout << "greed factor = " << agent.getGreedFactor() << std::endl;
			}
		}
	}
	if (!save_model_filename.empty() && save_model_filename != "")
		agent.saveModel(save_model_filename);
}