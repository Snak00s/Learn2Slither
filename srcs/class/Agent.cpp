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