#include"main.hpp"

class Parser
{
	private:
		std::unordered_map<std::string, std::vector<std::string> >	_data;
		std::unordered_map<std::string, std::string>				_types;
		enum class TYPE { INT, DOUBLE, STRING };
	public:
		Parser(void);
		~Parser();

		void														addArgToParse(std::string argname, std::string type);
		std::unordered_map<std::string, std::vector<std::string> >	const &parse(char **argv, int argc);

		std::unordered_map<std::string, std::vector<std::string> >	const &getParsedData(void) const;

		class TypeMissmatchException : public std::exception
		{
			protected:
				std::string _error;
			public:
				TypeMissmatchException(std::string arg, std::string expectedType, std::string word)
				{
					this->_error = "Error : TypeMissmatchException - \'" + word + "\' - type \'" + expectedType + "\' expected for \'" + arg + "\'.";
				};
				~TypeMissmatchException() = default;
				virtual const char *what() const throw()
				{
					return (this->_error.c_str());
				}
		};
		class TypeErrorException : public std::exception
		{
			protected:
				std::string _error;
			public:
				TypeErrorException(std::string type)
				{
					this->_error = "Error : TypeErrorException - \'" + type + "\' - incorrect, accepted type are 'int', 'double/float' and 'string'.";
				};
				~TypeErrorException() = default;
				virtual const char *what() const throw()
				{
					return (this->_error.c_str());
				}
		};
};