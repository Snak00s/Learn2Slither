#ifndef AGENT_HPP
# define AGENT_HPP

#include"main.hpp"

class Agent
{
	private:
		const double										_learning_rate;
		const double										_discount_factor;
		double												_greed_factor;
		std::unordered_map<uint32_t, std::vector<double>>	_q_table;
		uint32_t											_actual_state;
		AgentAction											_action_taken;

		void												_bellmanEquation(const uint32_t state, const int reward, GameEvent event);
		void												_pickRandomAction(void);
		void												_pickBestAction(void);

	public:
		Agent(uint32_t starting_state, double learning_rate, double discount_factor, double greed_factor);
		~Agent();

		AgentAction	takeAction(void);
		void		updateQTable(const uint32_t state, const int reward, GameEvent event);
		void		saveModel(std::string filename);
		void		loadModel(std::string model_filename);

		std::unordered_map<uint32_t, std::vector<double>> const	&getQTable(void) const;
		double													getGreedFactor(void);
		
		void													setGreedFactor(double val);


		class LineErrorException : public std::exception
		{
		protected:
			std::string _line_error;
		public:
			LineErrorException(size_t line_idx)
			{
				this->_line_error = "Error : LineErrorException at line " + std::to_string(line_idx) + '.';
			};
			~LineErrorException() = default;
			virtual const char *what() const throw()
			{
				return (this->_line_error.c_str());
			}
		};

		class InvalidFileException : public std::exception
		{
		protected:
			std::string _filename_error;
		public:
			InvalidFileException(std::string filename)
			{
				this->_filename_error = "Error : InvalidFileException \'" + filename + "\'.";
			};
			~InvalidFileException() = default;
			virtual const char *what() const throw()
			{
				return (this->_filename_error.c_str());
			}
		};
};

#endif