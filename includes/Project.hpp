#ifndef PROJECT_HPP
# define PROJECT_HPP

# include"Game.hpp"
# include"Agent.hpp"
# include"Interpreter.hpp"

class Project
{
private:
	Game	_game;
	Agent	_agent;
public:
	Project(const size_t game_board_size_x, const size_t game_board_size_y, std::string load_model_filename);
	~Project();

	void	launchProject(const size_t sessions_ammount, std::string save_filename, bool learning, bool visual);
};


#endif