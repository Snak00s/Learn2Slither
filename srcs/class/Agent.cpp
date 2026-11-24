#include "Agent.hpp"

Agent::Agent(uint32_t starting_state, double learning_rate, double discount_factor, double greed_factor) : _learning_rate(learning_rate), _discount_factor(discount_factor), _greed_factor(greed_factor),  _actual_state(starting_state)
{
	this->_q_table.emplace(starting_state, std::vector<double>(3, 0));
	return ;
}

Agent::~Agent(void)
{
	return ;
}

void	Agent::_pickBestAction(void)
{
	std::vector<double> const &actions = this->_q_table[this->_actual_state];

	size_t best_action_idx = 0;
	for (int i = 1; i < 3; i++)
	{
		if (actions[i] > actions[best_action_idx])
			best_action_idx = i;
	}

	switch (best_action_idx)
	{
		case 0:
			this->_action_taken = AgentAction::IDLE;
			break;
		case 1:
			this->_action_taken = AgentAction::TURN_RIGHT;
			break;
		case 2:
			this->_action_taken = AgentAction::TURN_LEFT;
			break;
	}
	return ;
}

void	Agent::_pickRandomAction(void)
{
	int rng = rand() % 3;

	switch (rng)
	{
		case 0:
			this->_action_taken = AgentAction::IDLE;
			break;
		case 1:
			this->_action_taken = AgentAction::TURN_RIGHT;
			break;
		case 2:
			this->_action_taken = AgentAction::TURN_LEFT;
			break;
	}
	return ;
}

AgentAction	Agent::takeAction(void)
{
	double r = static_cast<double>(rand()) / RAND_MAX;

	if ((r <= 1 - this->_greed_factor) && (this->_q_table.find(this->_actual_state) != this->_q_table.end()))
		this->_pickBestAction();
	else
		this->_pickRandomAction();
	return (this->_action_taken);
}

void	Agent::_bellmanEquation(const uint32_t state, const int reward, GameEvent event)
{
	double &state_action_qval = this->_q_table[this->_actual_state][static_cast<int>(this->_action_taken)];

	auto &next_state = this->_q_table[state];
	double next_state_best_q_value = 0;
	if (event != GameEvent::LOOSE)
		next_state_best_q_value = *std::max_element(next_state.begin(), next_state.end());

	state_action_qval += this->_learning_rate * (reward + this->_discount_factor * next_state_best_q_value - state_action_qval);

	return;
}

void Agent::updateQTable(const uint32_t state, const int reward, GameEvent event)
{
	auto known_state = this->_q_table.find(state);
	if (known_state == this->_q_table.end())
	{
		this->_q_table.emplace(state, std::vector<double>(3, 0));
	}

	this->_bellmanEquation(state, reward, event);
	this->_actual_state = state;
}

void	Agent::saveModel(std::string filename)
{
	std::ofstream	model(filename);
	for (auto &row : this->_q_table)
	{
		// model.write(reinterpret_cast<const char *>(&row.first), sizeof(row.first));
		model << row.first << '|';
		auto action_val_end = row.second.end();
		for (auto action_value = row.second.begin(); action_value != action_val_end; ++action_value)
		{
			// model.write(reinterpret_cast<const char *>(&action_value), sizeof(action_value));
			model << *action_value;
			if (action_value + 1 != action_val_end)
				model << ',';
		}
		model << std::endl;
	}
	return ;
}

bool	isnumber(std::string str, bool isfloat)
{
	size_t len = str.size();

	if (std::count(str.begin(), str.end(), '.') > static_cast<int>(isfloat))
		return (false);
	for (size_t i = 0; i < len; i++)
	{
		if (!isdigit(str[i]))
		{
			if (i == 0 && str[i] != '-' && str[i] != '+')
				return (false);
			else if (i != 0 && str[i] != '.')
				return (false);
		}
	}
	return (true);
}

void	Agent::loadModel(std::string model_filename)
{
	std::ifstream model_file(model_filename);
	if (!model_file) {
		throw InvalidFileException(model_filename);
	}

	std::string line;
	size_t line_idx = 0;
	while (std::getline(model_file, line))
	{
		const size_t state_end = line.find('|');
		if (state_end == line.npos || std::count(line.begin(), line.end(),  ',') != 2)
			throw LineErrorException(line_idx);

		const size_t action_1_end = line.find(',', state_end + 1);
		const size_t action_2_end = line.find(',', action_1_end + 1);

		if (action_1_end == line.npos || action_2_end == line.npos)
			throw LineErrorException(line_idx);

		const size_t action_1_size = action_1_end - (state_end + 1);
		const size_t action_2_size = action_2_end - (action_1_end + 1);
		const size_t action_3_size = line.size() - (action_2_end + 1);
		
		std::string const state(line, 0, state_end);
		std::string const action_1(line, state_end + 1, action_1_size);
		std::string const action_2(line, action_1_end + 1, action_2_size);
		std::string const action_3(line, action_2_end + 1, action_3_size);

		if (!isnumber(state, false) || !isnumber(action_1, true) || !isnumber(action_2, true) || !isnumber(action_3, true))
			throw LineErrorException(line_idx);

		const uint32_t state_val = std::atoi(state.c_str());

		double actions_lst[] = {std::atof(action_1.c_str()), std::atof(action_2.c_str()), std::atof(action_3.c_str())};
		std::vector<double> actions;
		actions.assign(actions_lst, actions_lst + 3);
		this->_q_table.emplace(state_val, actions);
		line_idx++;
	}
	std::cout << line_idx << std::endl;
	return ;
}

std::unordered_map<uint32_t, std::vector<double>> const	&Agent::getQTable(void) const
{
	return this->_q_table;
}

double	Agent::getGreedFactor(void)
{
	return this->_greed_factor;
}

void	Agent::setGreedFactor(double val)
{
	this->_greed_factor = val;
}