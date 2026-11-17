#ifndef AGENT_HPP
# define AGENT_HPP

#include"main.hpp"

class Agent
{
	private:
		const double										_learning_rate;
		const double										_discount_factor;
		std::unordered_map<uint32_t, std::vector<double>>	_q_table;
		uint32_t											_actual_state;
		AgentAction											_action_taken;

		void												_bellmanEquation(const uint32_t state, const int reward);

	public:
	Agent(uint32_t starting_state, double learning_rate, double discount_factor);
	~Agent();

	AgentAction	takeAction(void);
	void		updateQTable(const uint32_t state, const int reward);

	std::unordered_map<uint32_t, std::vector<double>> const	&getQTable(void) const;
};

#endif